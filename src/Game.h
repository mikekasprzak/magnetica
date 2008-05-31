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
public:
	
};
// - ------------------------------------------------------------------------------------------ - //
class cParticle {
public:
	Vector2D Pos, Old;
	Real Radius;
	
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
};
// - ------------------------------------------------------------------------------------------ - //
class cGenerator {
public:
	Vector2D Pos;
	Real Radius;
	
	Vector2D Direction;
	
	int Count;

public:
	inline cGenerator( const Vector2D& _Pos, const Real _Radius, const int _Count ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Direction( Vector2D( 0, 1 ) ),
		Count( _Count )
	{
	}
	
	inline cGenerator( const cPolyMapElement& Element ) :
		Pos( Element.Center ),
		Radius( Element.Data[0].f ),
		Count( Element.Info )
	{
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
	
	inline cCollector( const cPolyMapElement& Element ) :
		Pos( Element.Center ),
		Radius( Element.Data[0].f ),
		Count( 0 ),
		Quota( Element.Info )
	{
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
		Radius( Element.Data[0].f ),
		Polarity( Element.Info )
	{
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
	

public:
	int BoundsIndex;
	
	inline const cPolyMapElement& GetBounds() {
		return Map.Element[BoundsIndex];
	}
	
public:
	inline cGame() :
		Map( "TestMap.txt" ),
		BoundsIndex( 0 )
	{
		// Find the bounds rectangle //
		for ( size_t idx = 0; idx < Map.Element.size(); idx++ ) {
			if ( Map.Element[idx].Type == PME_RECT ) {
				if ( Map.Element[idx].Id == 1 ) {
					BoundsIndex = idx;
					break;
				}
			}
			else if ( Map.Element[idx].Type == PME_SPHERE ) {
				// What type of Sphere is it? //
				switch (Map.Element[idx].Id) {
					case 1: {
						// Generator //
						Generator.push_back( cGenerator(Map.Element[idx]) );
						break;
					}
					case 11: {
						// Collector //
						Collector.push_back( cCollector(Map.Element[idx]) );
						break;
					}
					case 21: {
						// Magnet //
						Magnet.push_back( cMagnet(Map.Element[idx]) );
						break;
					}
				};
			}
		}		
	}
	
	inline void Step() {
//		// Step Elements //
//		for ( size_t idx = 0; idx < Map.Element.size(); idx++ ) {
//
//		}
	}
	
	
	inline void Draw() {
		// Draw Elements //
		for ( size_t idx = 0; idx < Map.Element.size(); idx++ ) {
			// What kind of element is it? //
			if ( Map.Element[idx].Type == PME_POLY ) {
				// What type of Polygon is it? //
				switch (Map.Element[idx].Id) {
					default: 
					case 1: {
						gfxDrawClosedPolygonWithNormals( &Map.Element[idx].Vertex[0], Map.Element[idx].Vertex.size() );
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
