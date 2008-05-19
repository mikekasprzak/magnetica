
#include <AllegroGraphics/Graphics.h>
#include <AllegroGraphics/GraphicsDraw.h>

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
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
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
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
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
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
						break;
					}
				};
			}

			else if ( Map.Element[idx].Type == PME_RECT ) {
				// What type of Rectangle is it? //
				switch (Map.Element[idx].Type) {
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




int main( int argc, char* argv[] ) {
	gfxInit( 480, 320, false, 2 );
	
	{
		cGame Game;
	
		Vector2D MouseOld;
		Vector2D Mouse;
		
		int MouseOldZ = mouse_z;
		int MouseZ = mouse_z;
	
		while( !gfxShutdown() ) {
			gfxClearBuffer( RGB(70,0,0) );
			gfxSetMatrixToCamera();
			
			// Note the cursor position //
			MouseOld = Mouse;
			Mouse = Vector2D(mouse_x, mouse_y) / (ScreenScalar);
			
			Vector2D MouseWorld = (Mouse - CameraPos) / (CameraScale);
			
			MouseOldZ = MouseZ;
			MouseZ = mouse_z;
			
			
			if ( mouse_b == 2 ) {
				CameraPos -= MouseOld - Mouse;
			}
			
			if ( MouseZ != MouseOldZ ) {
				CameraScale += Real(MouseOldZ - MouseZ) * Real(0.1);
				if ( CameraScale < Real::One )
					CameraScale = Real::One;
			}
			
			Game.Step();
			
			Game.Draw();
		
		
			// Draw the cursor (so it's on top of everything //
			gfxDrawCircle( MouseWorld, 2, RGB_WHITE );
	
			while( key[KEY_SPACE] ) {}
	
			// Swap display buffer to screen //
			gfxSwapBuffer();		
		}
	}
	
	gfxExit();
	return 0;
}
END_OF_MAIN();
