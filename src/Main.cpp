
#include <AllegroGraphics/Graphics.h>
#include <AllegroGraphics/GraphicsDraw.h>
#include <AllegroGraphics/GraphicsDraw3D.h>

#include <PolyMap/PolyMap.h>
#include <AdvancedGeometry/PointVsSphere2D.h>
#include <AdvancedGeometry/PointVsPairRect2D.h>
#include <AdvancedGeometry/PointVsShapeRect2D.h>
#include <AdvancedGeometry/PointVsRadiusRect2D.h>

#include <AdvancedGeometry/PointVsPolygon2D.h>
#include <AdvancedGeometry/PointVsEdgedPolygon2D.h>


//using namespace std;

class cGame {
public:
	cPolyMap Map;
	
public:
	inline cGame() :
		Map( "TestMap.txt" )
	{
	}
	
	inline void Step() {
		
	}
	
	
	inline void Draw() {
		// Draw Elements //
		for ( size_t idx = 0; idx < Map.Element.size(); idx++ ) {
			// What kind of element is it? //
			if ( Map.Element[idx].Type == PME_POLY ) {
				// What type of Polygon is it? //
				switch (Map.Element[idx].Type) {
					default: 
					case 1: {
						gfxDrawClosedPolygonWithNormals( &Map.Element[idx].Vertex[0], Map.Element[idx].Vertex.size() );
									
						break;
					}
				};
			}
			
			else if ( Map.Element[idx].Type == PME_SPHERE ) {
				// What type of Sphere is it? //
				switch (Map.Element[idx].Type) {
					default: 
					case 1: {
						gfxDrawCircle( Map.Element[idx].Center, Map.Element[idx].Data[0].f);
									
						break;
					}
				};
			}

			else if ( Map.Element[idx].Type == PME_NODE ) {
				// What type of Node is it? //
				switch (Map.Element[idx].Type) {
					default: 
					case 1: {
						gfxDrawRadiusBox( Map.Element[idx].Center, 3 );
									
						break;
					}
				};
			}

			else if ( Map.Element[idx].Type == PME_RECT ) {
				// What type of Node is it? //
				switch (Map.Element[idx].Type) {
					default: 
					case 1: {
						gfxDrawRect( Map.Element[idx].Vertex[0], Map.Element[idx].Vertex[1] );
									
						break;
					}
				};
			}
		}
		
		
	}
};




int main( int argc, char* argv[] ) {
	gfxInit( 480, 320, false, 2 );
	
	cGame Game;


	while( !gfxShutdown() ) {
		gfxClearBuffer( RGB(70,0,0) );
		
		// Note the cursor position //
		Vector2D Mouse(mouse_x / ScreenScalar, mouse_y / ScreenScalar);
		
		
		Game.Draw();
		
	
	
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
