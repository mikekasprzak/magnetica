
#include <iostream>

#include <allegro.h>

#include <PolyMap/PolyMap.h>
#include <AdvancedGeometry/PointVsSphere2D.h>
#include <AdvancedGeometry/PointVsPairRect2D.h>
#include <AdvancedGeometry/PointVsShapeRect2D.h>
#include <AdvancedGeometry/PointVsRadiusRect2D.h>

#include <AdvancedGeometry/PointVsPolygon2D.h>
#include <AdvancedGeometry/PointVsEdgedPolygon2D.h>

#include <AllegroGraphics/Graphics.h>
#include <AllegroGraphics/GraphicsDraw.h>

using namespace std;



int main( int argc, char* argv[] ) {
//	if ( argc == 1 ) {
//		cout << "No Args" << endl;
//		return -1;
//	}
	
//	cout << "Args" << endl;
	
//	cPolyMap Map( argv[1] );
//	Map.Save( "Wheater.txt" );

	gfxInit( 480, 320, false, 2 );

	// Sphere //
	Vector2D DummySphere( 100, 100 );
	Real DummySphereRadius = 32;
	
	// Pair Rectangle //
	Vector2D PairP1( 200, 200 );
	Vector2D PairP2( 400, 300 );
	
	// Shape Rectangle //
	Vector2D ShapeP1( 200, 400 );
	Vector2D ShapeShape( 100, 100 );
	
	// Radius Rectangle //
	Vector2D RadiusCenter( 500, 400 );
	Vector2D RadiusRadius( 20, 30 );
	
	// Polygon //
	Vector2D Poly[5];
	Poly[0] = Vector2D( 400, 100 );
	Poly[1] = Vector2D( 600, 120 );
	Poly[2] = Vector2D( 700, 200 );
	Poly[3] = Vector2D( 650, 300 );
	Poly[4] = Vector2D( 300, 200 );
	
	size_t PolyCount = 5;

	// Edged Polygon //
	Vector2D Poy[5];
	Poy[0] = Vector2D( 400, 300 );
	Poy[1] = Vector2D( 600, 320 );
	Poy[2] = Vector2D( 700, 400 );
	Poy[3] = Vector2D( 650, 500 );
	Poy[4] = Vector2D( 300, 400 );
	
	bool PoyOn[5];
	PoyOn[0] = true;
	PoyOn[1] = false;
	PoyOn[2] = true;
	PoyOn[3] = true;
	PoyOn[4] = true;
	
	size_t PoyCount = 5;
	
	
	while( !key[KEY_ESC] ) {
		gfxClearBuffer( RGB(70,0,0) );
		
		// Note the cursor position //
		Vector2D Mouse(mouse_x / ScreenScalar, mouse_y / ScreenScalar);
		
		// Circle Tests //
		{
			ColorType Color = RGB( 255, 0, 0 );
			
			// If inside the sphere //
			if ( TestPointVsSphere2D( Mouse, DummySphere, DummySphereRadius ) ) {
				Color = RGB( 255, 255, 0 );
			}

			// Draw the Circle //
			gfxDrawCircle( DummySphere, DummySphereRadius, Color );
			
			// Nearest point on Circle //
			Vector2D Point = NearestPointOnSphere2D( Mouse, DummySphere, DummySphereRadius );
			gfxDrawCircle( Point, 3, RGB( 0, 255, 0 ) );
			
			
			// Nearest point on the edge of the circle //
			Vector2D EdgePoint = NearestPointOnEdgeOfSphere2D( Mouse, DummySphere, DummySphereRadius );
			gfxDrawCircle( EdgePoint, 5, RGB( 0, 255, 0 ) );
		}
		
		// PairRect Tests //
		{
			ColorType Color = RGB( 255, 0, 0 );
			
			// If inside the Rect //
			if ( TestPointVsPairRect2D( Mouse, PairP1, PairP2 ) ) {
				Color = RGB( 255, 255, 0 );
			}
			
			// Draw the Rect //
			//rect( Buffer, (int)PairP1.x, (int)PairP1.y, (int)PairP2.x, (int)PairP2.y, Color );
			gfxDrawRectWithNormals( PairP1, PairP2, Color );
			
			
			// Nearest point on Rect //
			Vector2D Point = NearestPointOnPairRect2D( Mouse, PairP1, PairP2 );
			gfxDrawCircle( Point, 3, RGB( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Rect //
			Vector2D EdgePoint = NearestPointOnEdgeOfPairRect2D( Mouse, PairP1, PairP2 );
			gfxDrawCircle( EdgePoint, 5, RGB( 0, 255, 0 ) );

			// Nearest point on the edge of the Rect //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfPairRect2D( Mouse, PairP1, PairP2 );
			gfxDrawRadiusBox( CornerPoint, 7, RGB( 255, 255, 0 ) );
		}
		
		// ShapeRect Tests //
		{
			ColorType Color = RGB( 255, 0, 0 );
			
			// If inside the Rect //
			if ( TestPointVsShapeRect2D( Mouse, ShapeP1, ShapeShape ) ) {
				Color = RGB( 255, 255, 0 );
			}
			
			// Draw the Rect //
			gfxDrawRectWithNormals( ShapeP1, ShapeP1 + ShapeShape, Color );
			
			
			// Nearest point on Rect //
			Vector2D Point = NearestPointOnShapeRect2D( Mouse, ShapeP1, ShapeShape );
			gfxDrawCircle( Point, 3, RGB( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Rect //
			Vector2D EdgePoint = NearestPointOnEdgeOfShapeRect2D( Mouse, ShapeP1, ShapeShape );
			gfxDrawCircle( EdgePoint, 5, RGB( 0, 255, 0 ) );

			// Nearest point on the edge of the Rect //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfShapeRect2D( Mouse, ShapeP1, ShapeShape );
			gfxDrawRadiusBox( CornerPoint, 7, RGB( 255, 255, 0 ) );
		}
		
		// RadiusRect Tests //
		{
			ColorType Color = RGB( 255, 0, 0 );
			
			// If inside the Rect //
			if ( TestPointVsRadiusRect2D( Mouse, RadiusCenter, RadiusRadius ) ) {
				Color = RGB( 255, 255, 0 );
			}
			
			// Draw the Rect //
			gfxDrawRectWithNormals( RadiusCenter - RadiusRadius, RadiusCenter + RadiusRadius, Color );
			
			
			// Nearest point on Rect //
			Vector2D Point = NearestPointOnRadiusRect2D( Mouse, RadiusCenter, RadiusRadius );
			gfxDrawCircle( Point, 3, RGB( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Rect //
			Vector2D EdgePoint = NearestPointOnEdgeOfRadiusRect2D( Mouse, RadiusCenter, RadiusRadius );
			gfxDrawCircle(EdgePoint, 5, RGB( 0, 255, 0 ) );

			// Nearest point on the edge of the Rect //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfRadiusRect2D( Mouse, RadiusCenter, RadiusRadius );
			gfxDrawRadiusBox( CornerPoint, 7, RGB( 255, 255, 0 ) );
		}

		// Polygon Tests //
		{
			// Draw the Polygon //
			ColorType Color = RGB( 255, 0, 0 );
			
			// If inside the Polygon //
			if ( TestPointVsPolygon2D( Mouse, Poly, PolyCount ) ) {
				Color = RGB( 255, 255, 0 );
			}
			
			// Draw the Polygon //
			gfxDrawClosedPolygonWithNormals( Poly, PolyCount, Color );
			gfxDrawPolygonEdge( 
				NearestEdgeIndexOfPolygon2D( Mouse, Poly, PolyCount ),
				Poly,
				PolyCount,
				RGB_CYAN
				);
			
			// Nearest point on Polygon //
			Vector2D Point = NearestPointOnPolygon2D( Mouse, Poly, PolyCount );
			gfxDrawCircle( Point, 3, RGB( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Polygon //
			Vector2D EdgePoint = NearestPointOnEdgeOfPolygon2D( Mouse, Poly, PolyCount );
			gfxDrawCircle( EdgePoint, 5, RGB( 0, 255, 0 ) );

			// Nearest point on the edge of the Polygon //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfPolygon2D( Mouse, Poly, PolyCount );
			gfxDrawRadiusBox( CornerPoint, 7, RGB( 255, 255, 0 ) );
		}

		// Edged Polygon Tests //
		{
			// Draw the Polygon //
			ColorType Color = RGB( 255, 0, 0 );
			
			// If inside the Polygon //
			if ( TestPointVsEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount ) ) {
				Color = RGB( 255, 255, 0 );
			}
			
			// Draw the Polygon //
			gfxDrawEdgedPolygonWithNormals( Poy, PoyOn, PoyCount, Color );
			
			int Edge = NearestEdgeIndexOfEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount );
			if ( Edge != -1 ) {
				if ( PoyOn[Edge] ) {
					gfxDrawPolygonEdge( Edge, Poy, PoyCount, RGB_CYAN );
				}
			}
			
			// Nearest point on Polygon //
			Vector2D Point = NearestPointOnEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount );
			gfxDrawCircle( Point, 3, RGB( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Polygon //
			Vector2D EdgePoint = NearestPointOnEdgeOfEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount );
			gfxDrawCircle( EdgePoint, 5, RGB( 0, 255, 0 ) );

			// Nearest point on the edge of the Polygon //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount );
			gfxDrawRadiusBox( CornerPoint, 7, RGB( 255, 255, 0 ) );
		}
		
		// Testing the matrix stack //
		gfxPushMatrix();
		{
//			gfxTranslate( 100, 100 );
//			gfxScale(2);
			
//			static Real Orc;
//			Orc += 0.001;
//			gfxRotate( Orc );

//			gfxRotate( 0.01 );
			
			gfxDrawArrow2( Vector2D(400,300), Mouse, RGB_PUKE, Real(30) );
		}
		gfxPopMatrix();
	
		// Draw the cursor (so it's on top of everything //
		gfxDrawCircle( Mouse, 2, RGB_WHITE );

		while( key[KEY_SPACE] ) {}

		// Swap display buffer to screen //
		gfxSwapBuffer();		
	}
	
	gfxExit();
	return 0;
}
END_OF_MAIN();
