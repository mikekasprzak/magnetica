
#include <iostream>

#include <allegro.h>

#include "PolyMap.h"
#include "AdvancedGeometry/PointVsSphere2D.h"
#include "AdvancedGeometry/PointVsPairRect2D.h"
#include "AdvancedGeometry/PointVsShapeRect2D.h"
#include "AdvancedGeometry/PointVsRadiusRect2D.h"

#include "AdvancedGeometry/PointVsPolygon2D.h"
#include "AdvancedGeometry/PointVsEdgedPolygon2D.h"

using namespace std;

BITMAP* Buffer;

int main( int argc, char* argv[] ) {
//	if ( argc == 1 ) {
//		cout << "No Args" << endl;
//		return -1;
//	}
	
//	cout << "Args" << endl;
	
//	cPolyMap Map( argv[1] );
//	Map.Save( "Wheater.txt" );


	allegro_init();
	install_keyboard();
	install_mouse();
	
	set_color_depth( 16 );
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 );
	Buffer = create_bitmap( 800, 600 );
	
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
		clear_to_color( Buffer, makecol(35,0,0) );
		
		Vector2D Mouse(mouse_x, mouse_y);
		circle( Buffer, mouse_x, mouse_y, 2, makecol( 255, 255, 255 ) );
		
		// Circle Tests //
		{
			int Color = makecol( 255, 0, 0 );
			
			// If inside the sphere //
			if ( TestPointVsSphere2D( Mouse, DummySphere, DummySphereRadius ) ) {
				Color = makecol( 255, 255, 0 );
			}

			// Draw the Circle //
			circle( Buffer, (int)DummySphere.x, (int)DummySphere.y, (int)DummySphereRadius, Color );
			
			// Nearest point on Circle //
			Vector2D Point = NearestPointOnSphere2D( Mouse, DummySphere, DummySphereRadius );
			circle( Buffer, (int)Point.x, (int)Point.y, 3, makecol( 0, 255, 0 ) );
			
			// Nearest point on the edge of the circle //
			Vector2D EdgePoint = NearestPointOnEdgeOfSphere2D( Mouse, DummySphere, DummySphereRadius );
			circle( Buffer, (int)EdgePoint.x, (int)EdgePoint.y, 5, makecol( 0, 255, 0 ) );
		}
		
		// PairRect Tests //
		{
			int Color = makecol( 255, 0, 0 );
			
			// If inside the Rect //
			if ( TestPointVsPairRect2D( Mouse, PairP1, PairP2 ) ) {
				Color = makecol( 255, 255, 0 );
			}
			
			// Draw the Rect //
			rect( Buffer, (int)PairP1.x, (int)PairP1.y, (int)PairP2.x, (int)PairP2.y, Color );
			
			
			// Nearest point on Rect //
			Vector2D Point = NearestPointOnPairRect2D( Mouse, PairP1, PairP2 );
			circle( Buffer, (int)Point.x, (int)Point.y, 3, makecol( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Rect //
			Vector2D EdgePoint = NearestPointOnEdgeOfPairRect2D( Mouse, PairP1, PairP2 );
			circle( Buffer, (int)EdgePoint.x, (int)EdgePoint.y, 5, makecol( 0, 255, 0 ) );

			// Nearest point on the edge of the Rect //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfPairRect2D( Mouse, PairP1, PairP2 );
			circle( Buffer, (int)CornerPoint.x, (int)CornerPoint.y, 7, makecol( 255, 255, 0 ) );
		}
		
		// ShapeRect Tests //
		{
			int Color = makecol( 255, 0, 0 );
			
			// If inside the Rect //
			if ( TestPointVsShapeRect2D( Mouse, ShapeP1, ShapeShape ) ) {
				Color = makecol( 255, 255, 0 );
			}
			
			// Draw the Rect //
			rect( Buffer, (int)ShapeP1.x, (int)ShapeP1.y, (int)ShapeP1.x + ShapeShape.x, (int)ShapeP1.y + ShapeShape.y, Color );
			
			
			// Nearest point on Rect //
			Vector2D Point = NearestPointOnShapeRect2D( Mouse, ShapeP1, ShapeShape );
			circle( Buffer, (int)Point.x, (int)Point.y, 3, makecol( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Rect //
			Vector2D EdgePoint = NearestPointOnEdgeOfShapeRect2D( Mouse, ShapeP1, ShapeShape );
			circle( Buffer, (int)EdgePoint.x, (int)EdgePoint.y, 5, makecol( 0, 255, 0 ) );

			// Nearest point on the edge of the Rect //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfShapeRect2D( Mouse, ShapeP1, ShapeShape );
			circle( Buffer, (int)CornerPoint.x, (int)CornerPoint.y, 7, makecol( 255, 255, 0 ) );
		}
		
		// RadiusRect Tests //
		{
			int Color = makecol( 255, 0, 0 );
			
			// If inside the Rect //
			if ( TestPointVsRadiusRect2D( Mouse, RadiusCenter, RadiusRadius ) ) {
				Color = makecol( 255, 255, 0 );
			}
			
			// Draw the Rect //
			rect( Buffer, (int)RadiusCenter.x - RadiusRadius.x, (int)RadiusCenter.y - RadiusRadius.y, (int)RadiusCenter.x + RadiusRadius.x, (int)RadiusCenter.y + RadiusRadius.y, Color );
			
			
			// Nearest point on Rect //
			Vector2D Point = NearestPointOnRadiusRect2D( Mouse, RadiusCenter, RadiusRadius );
			circle( Buffer, (int)Point.x, (int)Point.y, 3, makecol( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Rect //
			Vector2D EdgePoint = NearestPointOnEdgeOfRadiusRect2D( Mouse, RadiusCenter, RadiusRadius );
			circle( Buffer, (int)EdgePoint.x, (int)EdgePoint.y, 5, makecol( 0, 255, 0 ) );

			// Nearest point on the edge of the Rect //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfRadiusRect2D( Mouse, RadiusCenter, RadiusRadius );
			circle( Buffer, (int)CornerPoint.x, (int)CornerPoint.y, 7, makecol( 255, 255, 0 ) );
		}

		// Polygon Tests //
		{
			// Draw the Polygon //
			int Color = makecol( 255, 0, 0 );
			
			// If inside the Polygon //
			if ( TestPointVsPolygon2D( Mouse, Poly, PolyCount ) ) {
				Color = makecol( 255, 255, 0 );
			}
			
			// Draw the Rect //
			for ( size_t idx = 0; idx < PolyCount-1; idx++ ) {
				line( Buffer, (int)Poly[idx].x, (int)Poly[idx].y, (int)Poly[idx+1].x, (int)Poly[idx+1].y, 
					(idx == NearestEdgeIndexOfPolygon2D( Mouse, Poly, PolyCount )) ? makecol(255, 255, 255) : Color
					);
			}
			if ( PolyCount-1 == NearestEdgeIndexOfPolygon2D( Mouse, Poly, PolyCount ) ) {
				Color = makecol(255, 255, 255);
			}
			line( Buffer, (int)Poly[PolyCount-1].x, (int)Poly[PolyCount-1].y, (int)Poly[0].x, (int)Poly[0].y, Color );
			
			// Nearest point on Polygon //
			Vector2D Point = NearestPointOnPolygon2D( Mouse, Poly, PolyCount );
			circle( Buffer, (int)Point.x, (int)Point.y, 3, makecol( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Polygon //
			Vector2D EdgePoint = NearestPointOnEdgeOfPolygon2D( Mouse, Poly, PolyCount );
			circle( Buffer, (int)EdgePoint.x, (int)EdgePoint.y, 5, makecol( 0, 255, 0 ) );

			// Nearest point on the edge of the Polygon //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfPolygon2D( Mouse, Poly, PolyCount );
			circle( Buffer, (int)CornerPoint.x, (int)CornerPoint.y, 7, makecol( 255, 255, 0 ) );
		}

		// Edged Polygon Tests //
		{
			// Draw the Polygon //
			int Color = makecol( 255, 0, 0 );
			
			// If inside the Polygon //
			if ( TestPointVsEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount ) ) {
				Color = makecol( 255, 255, 0 );
			}
			
			// Draw the Rect //
			for ( size_t idx = 0; idx < PoyCount-1; idx++ ) {
				if ( PoyOn[idx] )
					line( Buffer, (int)Poy[idx].x, (int)Poy[idx].y, (int)Poy[idx+1].x, (int)Poy[idx+1].y, 
						(idx == NearestEdgeIndexOfEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount )) ? makecol(255, 255, 255) : Color
						);
			}
			if ( PoyCount-1 == NearestEdgeIndexOfEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount ) ) {
				Color = makecol(255, 255, 255);
			}
			if ( PoyOn[PoyCount-1] )
				line( Buffer, (int)Poy[PoyCount-1].x, (int)Poy[PoyCount-1].y, (int)Poy[0].x, (int)Poy[0].y, Color );
			
			// Nearest point on Polygon //
			Vector2D Point = NearestPointOnEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount );
			circle( Buffer, (int)Point.x, (int)Point.y, 3, makecol( 0, 255, 0 ) );
			
			// Nearest point on the edge of the Polygon //
			Vector2D EdgePoint = NearestPointOnEdgeOfEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount );
			circle( Buffer, (int)EdgePoint.x, (int)EdgePoint.y, 5, makecol( 0, 255, 0 ) );

			// Nearest point on the edge of the Polygon //
			Vector2D CornerPoint = NearestCornerPointOnEdgeOfEdgedPolygon2D( Mouse, Poy, PoyOn, PoyCount );
			circle( Buffer, (int)CornerPoint.x, (int)CornerPoint.y, 7, makecol( 255, 255, 0 ) );
		}

		
		vsync();
		rest(0);
		
		blit( Buffer, screen, 0, 0, 0, 0, Buffer->w, Buffer->h );
	}
	
	allegro_exit();
	return 0;
}
END_OF_MAIN();
