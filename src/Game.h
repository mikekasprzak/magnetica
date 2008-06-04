// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_H__
#define __Game_H__
// - ------------------------------------------------------------------------------------------ - //
#include <AllegroGraphics/Graphics.h>
#include <AllegroGraphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
#include <PolyMap/PolyMap.h>
#include <AdvancedGeometry/PointVsSphere2D.h>
#include <AdvancedGeometry/PointVsPairRect2D.h>
#include <AdvancedGeometry/PointVsShapeRect2D.h>
#include <AdvancedGeometry/PointVsRadiusRect2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include <AdvancedGeometry/PointVsPolygon2D.h>
#include <AdvancedGeometry/PointVsEdgedPolygon2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Inputs //
// '+' - Positive or Repel (increase distance)
// '-' - Negative or Attract (decrease distance)
// '0' - Neutral (Will follow whatever default behavior)
// '1' - Default Repel/Attract value (either + or -)
// - ------------------------------------------------------------------------------------------ - //
// Returns -1, 0, or +1, the polarity action to take //
inline const int SolvePolarity( const int a, const int b ) {
	// Determine the sign of the 'a' polarity //
	int a_sign = 0;
	if ( a > 0 )
		a_sign = 1;
	else if ( a < 0 )
		a_sign = -1;
	// Note the intensity of the 'a' polarity //
	//int a_intensity = abs(a);
	
	// Determine the sign of the 'b' polarity //
	int b_sign = 0;
	if ( b > 0 )
		b_sign = 1;
	else if ( b < 0 )
		b_sign = -1;
	// Note the intensity of the 'b' polarity //
	//int b_intensity = abs(b);
	
	// If signs are different //
	if ( a_sign != b_sign ) {
		// The special case if a is ever zero, do nothing //
		if ( a_sign == 0 ) {
			return 0;
		}
		// If b's sign is zero, follow the behavior of a's sign //
		else if ( b_sign == 0 ) {
			return a_sign;
		}
		// Default behavior is to Attract on sign difference //
		else {
			return -1;
		}
	}
	// Otherwise the signs are the same //
	else {
		// If the signs are both zero, it has no effect //
		if ( a_sign == 0 ) {
			return 0;
		}
		// Default Behavior is to Repel on sign equality //
		else {
			return +1;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cImpulse {
public:
	Vector2D Pos;
	
	Real InnerRadius;
	Real InnerForce;
	
	Real OuterRadius;
	Real OuterForce;
	
	
	// Cached Variables //
	Real ForceDiff;
	Real RadiusDiff;
	Real InvRadiusDiff;	
	
	Real OuterRadiusSquared;
	Real InnerRadiusSquared;
	
public:
	inline cImpulse(
		const Vector2D& _Pos,
		const Real& _InnerRadius, const Real& _InnerForce,
		const Real& _OuterRadius, const Real& _OuterForce
		) :
		Pos( _Pos ),
		InnerRadius( _InnerRadius ), InnerForce( _InnerForce ),
		OuterRadius( _OuterRadius ), OuterForce( _OuterForce ),
		ForceDiff( _InnerForce - _OuterForce ),
		RadiusDiff( _OuterRadius - _InnerRadius ),
		InvRadiusDiff( Real::One / RadiusDiff ),
		OuterRadiusSquared( _OuterRadius * _OuterRadius ),
		InnerRadiusSquared( _InnerRadius * _InnerRadius )
	{
	}

public:
	// Get the force on you, given your position //
	inline Vector2D GetForce( const Vector2D& _Pos ) const {
		Vector2D Line = _Pos - Pos;
		
		if ( Line.MagnitudeSquared() > OuterRadiusSquared ) {
			return Vector2D::Zero;
		}
		else if ( Line.MagnitudeSquared() <= InnerRadiusSquared ) {
			Vector2D LineNormal = Line.Normal();

			return (LineNormal * InnerForce);
		}
		else {
			// Linear Impulses //
			Real Mag = Line.NormalizeRet();
			Real ForceScalar = (RadiusDiff - ( Mag - InnerRadius )) * InvRadiusDiff;
			return (Line * (ForceDiff * ForceScalar));
			
			// Exponential Impulses //
//			Real Mag = Line.NormalizeRet();
//			Mag -= InnerRadius;
//			Real ForceScalar = Mag*Mag / (RadiusDiff*RadiusDiff); // * InvRadiusDiff;
//			return Line * (ForceDiff * (Real::One - ForceScalar));
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cParticle {
public:
	Vector2D Pos, Old;
	Real Radius;
	
	Vector2D Force;

	
	int Polarity;

public:
	cParticle( const Vector2D& _StartPos, const Vector2D& _Direction, const int _Polarity = 0 ) :
		Pos( _StartPos ),
		Old( _StartPos - _Direction ),
		Radius( 4 ),
		Polarity( _Polarity )
	{
	}
	
	// TODO: Add constructor that takes a PolyMapElement or Generator, and does the random calculation //

public:
	inline const Vector2D Velocity() {
		return (Pos - Old);
	}
	
	inline void AddForce( const Vector2D& _Force ) {
		Force += _Force;
	}
	
	inline void ApplyReflection( const Vector2D& _ContactNormal ) {
		// Calculate the Reflection //
		Real ReflectionStrength = (Velocity() * _ContactNormal) * Real(2);
		
		// Reflect only if you oppose the direction of the Contact Normal //
		if ( ReflectionStrength > Real::Zero ) {
			// Apply the reflection to Old Position //
			Old += ReflectionStrength * _ContactNormal;
		}
	}
public:	
	inline void Step() {
		Vector2D Temp = Pos;
		Vector2D NewVelocity = (Velocity() * Real(0.98)) + Force;
		//Vector2D NewVelocity = Velocity() + Force;
		Real Speed = NewVelocity.NormalizeRet();
		if ( Speed < Real(0.4) )
			Speed = Real(0.4);
		
		Pos += NewVelocity * Speed;
		Old = Temp;
		
		// Clear Collected Forces //
		Force = Vector2D(0,0);
	}
	
	inline void Draw() { 
		gfxDrawCircle( Pos, Radius, RGB_PURPLE );
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cGenerator {
public:
	Vector2D Pos;
	Real Radius;
	
	Vector2D Direction;
	
	int Count;
public:
	// Clock/Generation Mechanisms //
	bool Enabled;
	int Ticks;
	int TicksUntilNextSpawn;
	
	inline bool StepClock() {
		if ( Enabled ) {
			Ticks++;
			if ( TicksUntilNextSpawn == Ticks ) {
				if ( Count > 0 ) {
					Count--;
					
					Ticks = 0;
					return true;	
				}
			}
		}
		return false;
	}


public:
	inline cGenerator( const Vector2D& _Pos, const Real _Radius, const int _Count ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Direction( Vector2D( 0, -1 ) ),
		Count( _Count ),
		
		Enabled( true ),
		Ticks( 0 ),
		TicksUntilNextSpawn( 60 )
	{
	}
	
	inline cGenerator( const cPolyMapElement& Element ) :
		Pos( Element.Center ),
		Radius( 12 ),
		Direction( Vector2D( -1, -2 ).Normal() ),
		Count( 30 ),
//		Radius( Element.Data[0].f ),
//		Direction( Vector2D( 0, -1 ) ),
//		Count( Element.Data[1].i ),
		
		Enabled( true ),
		Ticks( 0 ),
		TicksUntilNextSpawn( 60 )
	{
	}

public:
	inline void Step() {
		
	}
	
	inline void Draw() { 
		if ( Enabled && Count ) {
			gfxDrawCircle( Pos, ((Ticks>>2) == 0) ? Radius - Real(2) : Radius, RGB_SKY );
		}
		else {
			gfxDrawCircle( Pos, Radius, RGB_BLUE );			
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cCollector { 
public:
	Vector2D Pos;
	Real Radius;
	
	int Count;
	int Quota;
public:
	inline cCollector( const Vector2D& _Pos, const Real _Radius, const int _Quota ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Count( 0 ),
		Quota( _Quota )
	{
	}
	
//	inline cCollector( const cPolyMapElement& Element ) :
//		Pos( Element.Center ),
//		Radius( Element.Data[0].f ),
//		Count( 0 ),
//		Quota( Element.Data[1].i )
//	{
//	}
	
	inline cCollector( const cPolyMapElement& Element ) :
		Pos( Element.Center ),
		Radius( 16 ),
		Count( 0 ),
		Quota( 30 )
	{
	}
	
public:
	inline void Step() {
		
	}
	
	inline void Draw() { 
		if ( Count >= Quota )
			gfxDrawCircle( Pos, Radius, RGB_YELLOW );
		else
			gfxDrawCircle( Pos, Radius, RGB_GREEN );
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cMagnet {
public:
	Vector2D Pos;
	Real Radius;
	
	int Polarity;
public:
	inline cMagnet( const Vector2D& _Pos, const Real _Radius, const int _Polarity ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Polarity( _Polarity )
	{
	}
	
	inline cMagnet( const cPolyMapElement& Element ) :
		Pos( Element.Center ),
		Radius( 12 ),
		Polarity( 1 )
//		Radius( Element.Data[0].f ),
//		Polarity( Element.Data[1].i )
	{
	}	

public:
	inline void Step() {
		
	}
	
	inline void Draw() { 
		gfxDrawCircle( Pos, Radius, RGB_ORANGE );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cGame {
public:
	cPolyMap Map;

	std::vector<cImpulse> Impulse;
	std::vector<cParticle> Particle;
		
	std::vector<cGenerator> Generator;
	std::vector<cCollector> Collector;
	std::vector<cMagnet> Magnet;
	
	// Note all the collision Polygons //
	std::vector<cPolyMapElement*> Collision;
	

public:
	int BoundsIndex;
	
	inline const cPolyMapElement& GetBounds() {
		// TODO: Make this instead give a rectangle, or some identifyable value for none //
		return Map.Element[BoundsIndex];
	}
	
public:
	inline cGame() :
		Map( "TestMap.txt" ),
		BoundsIndex( 0 )
	{
		printf( "- Game Init -\n" );
		// Hacked in Elements //
//		Generator.push_back( cGenerator( Vector2D( 0, 0 ), 12, 30 ) );
//		Collector.push_back( cCollector( Vector2D( 0, -200 ), 16, 20 ) );
//
//		Magnet.push_back( cMagnet( Vector2D( 70, -100 ), 12, -1 ) );
		
		
		// Find the bounds rectangle //
		for ( size_t idx = 0; idx < Map.Element.size(); idx++ ) {
			if ( Map.Element[idx].Type == PME_RECT ) {
				switch (Map.Element[idx].Id) {
					case 1: {
						printf(" + Bounding Rectangle Set\n");
						BoundsIndex = idx;
						break;
					}
				};
			}
			else if ( Map.Element[idx].Type == PME_SPHERE ) {
				// What type of Sphere is it? //
				switch (Map.Element[idx].Id) {
					case 1: {
						// Generator //
						Generator.push_back( cGenerator(Map.Element[idx]) );
						printf(" + Added Generator\n");
						break;
					}
					case 11: {
						// Collector //
						Collector.push_back( cCollector(Map.Element[idx]) );
						printf(" + Added Collector\n");
						break;
					}
					case 21: {
						// Magnet //
						Magnet.push_back( cMagnet(Map.Element[idx]) );
						printf(" + Added Magnet\n");
						break;
					}
				};
			}
			else if ( Map.Element[idx].Type == PME_POLY ) {
				// For now, asume all polygons are collision //
				Collision.push_back( &Map.Element[idx] );
				printf(" + Added Collision Polygon\n");
			}
		}		
	}
	
	inline void Step() {
		// Magnet Moving Hack //
		if ( mouse_b == 1 )
			Magnet[0].Pos = Camera.Mouse;
		
		
		// Step all Generators //
		for ( size_t idx = 0; idx < Generator.size(); idx++ ) {
			Generator[idx].Step();
			if ( Generator[idx].StepClock() ) {
				Vector2D Offset = 
					Generator[idx].Direction.Tangent() * 
					(((Real::Random() * Real(2)) - Real::One) * Generator[idx].Radius );
				Particle.push_back( cParticle( Generator[idx].Pos + Offset, Generator[idx].Direction ) );
			}
		}
		// Step all Collectors //
		for ( size_t idx = 0; idx < Collector.size(); idx++ ) {
			Collector[idx].Step();
			// TODO: Add Impulse 
			Impulse.push_back( 
				cImpulse(
					Collector[idx].Pos,
					0, -0.01,
					48, 0
					)
				);
		}
		// Step all Magnets //
		for ( size_t idx = 0; idx < Magnet.size(); idx++ ) {
			Magnet[idx].Step();
			// TODO: Add Impulse //
			Impulse.push_back( 
				cImpulse(
					Magnet[idx].Pos,
					0, -0.02,
					128, 0
					)
				);
		}


		// Step all Particles //
		for ( size_t idx = 0; idx < Particle.size(); idx++ ) {
			Particle[idx].Step();

			// Apply Impulses //
			for ( size_t idx2 = 0; idx2 < Impulse.size(); idx2++ ) {
				Particle[idx].AddForce( Impulse[idx2].GetForce( Particle[idx].Pos ) );
			}
			
			// Test for Collisions Vs. Polygons //
			for ( size_t idx2 = 0; idx2 < Collision.size(); idx2++ ) {
				if ( TestPointVsPolygon2D( Particle[idx].Pos, &Collision[idx2]->Vertex[0], Collision[idx2]->Vertex.size() ) ) {
					// Reflect off the surface //
					Particle[idx].ApplyReflection( 
						NearestEdgeNormalOfPolygon2D( 
							Particle[idx].Pos,
							&Collision[idx2]->Vertex[0],
							Collision[idx2]->Vertex.size()
							)
						);
				}
			}
		
			// Test for Collisions Vs. Collectors //
			for ( size_t idx2 = 0; idx2 < Collector.size(); idx2++ ) {
				if ( TestPointVsSphere2D( Particle[idx].Pos, Collector[idx2].Pos, Collector[idx2].Radius ) ) {
					Collector[idx2].Count++;
					
					// Kill Particle //
					Particle.erase( Particle.begin() + idx );
					idx--;
					break;
				}
			}
			
			
		}

		// Remove all Impulses //
		Impulse.clear();
	}
	
	
	inline void Draw() {
		// Draw all Generators //
		for ( size_t idx = 0; idx < Generator.size(); idx++ ) {
			Generator[idx].Draw();
		}
		// Draw all Collectors //
		for ( size_t idx = 0; idx < Collector.size(); idx++ ) {
			Collector[idx].Draw();
		}
		// Draw all Magnets //
		for ( size_t idx = 0; idx < Magnet.size(); idx++ ) {
			Magnet[idx].Draw();
		}

		// Draw all Particles //
		for ( size_t idx = 0; idx < Particle.size(); idx++ ) {
			Particle[idx].Draw();
		}
		
		
		// Draw Elements //
		for ( size_t idx = 0; idx < Map.Element.size(); idx++ ) {
			// What kind of element is it? //
			if ( Map.Element[idx].Type == PME_POLY ) {
				// What type of Polygon is it? //
				switch (Map.Element[idx].Id) {
					default: 
					case 1: {
						gfxDrawClosedPolygonWithNormals( &Map.Element[idx].Vertex[0], Map.Element[idx].Vertex.size(), RGB_PUKE );
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
						break;
					}
				};
			}
			
			else if ( Map.Element[idx].Type == PME_SPHERE ) {
				// What type of Sphere is it? //
				switch (Map.Element[idx].Id) {
					default: 
					case 1: {
						gfxDrawCircle( Map.Element[idx].Center, Map.Element[idx].Data[0].f);
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
						break;
					}
				};
			}

			else if ( Map.Element[idx].Type == PME_NODE ) {
				// What type of Node is it? //
				switch (Map.Element[idx].Id) {
					default: 
					case 1: {
						gfxDrawRadiusBox( Map.Element[idx].Center, 3 );
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
						break;
					}
				};
			}

			else if ( Map.Element[idx].Type == PME_RECT ) {
				// What type of Rectangle is it? //
				switch (Map.Element[idx].Id) {
					default: 
					case 1: {
						gfxDrawRect( Map.Element[idx].Vertex[0], Map.Element[idx].Vertex[1] );
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
						break;
					}
				};
			}
		}
		
		// Draw Links //
		for ( size_t idx = 0; idx < Map.Link.size(); idx++ ) {
			// What type of link is it? //
			//if ( Map.Link.Type == 1 )
			{
				gfxDrawLine( Map.Element[ Map.Link[idx].a ].Center, Map.Element[ Map.Link[idx].b ].Center );
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_H__ //
// - ------------------------------------------------------------------------------------------ - //
