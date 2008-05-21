
#include <Geometry/Rect.h>

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
		}		
	}
	
	inline void Step() {
		
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




int main( int argc, char* argv[] ) {
	gfxInit( 480, 320, false, 2 );
	
	{
		cGame Game;
	
		while( !gfxShutdown() ) {
			gfxClearBuffer( RGB(70,0,0) );
			
			Mouse.Update();
			Camera.Update();

			
			if ( mouse_b == 2 ) {
				gfxSetCameraPos( gfxGetCameraPos() - (Mouse.Diff() * gfxGetCameraScale()) );
			}
			gfxConstrainCamera( Game.GetBounds().Vertex[0], Game.GetBounds().Vertex[1] );			
			
			if ( Mouse.WheelDiff() ) {
				gfxAddCameraScale( Real(Mouse.WheelDiff()) * Real(0.1) );
				gfxConstrainCameraScale( Real::One, Real(4) );
			}
			
			
			// Step the game //
			Game.Step();
			
			// Prior to drawing, set the current matrix to suit drawing relative to the camera //
			gfxSetCameraMatrix();
			// Draw the game //
			Game.Draw();
					
			// Draw center cross //
			gfxDrawCross( (Vector2D::Zero - gfxGetCameraPos()), 4 );

			// Draw the cursor (last, so it's on top of everything) //
//			gfxDrawCircle( Camera.Mouse, 2, RGB_YELLOW );
		
			
			// Draw cursors and hud stuffs in screen space, as opposed to camera space //
			gfxSetScreenMatrix();
			// Draw the cursor (last, so it's on top of everything) //
			gfxDrawCircle( Mouse.Pos, 2, RGB_WHITE );
	
			while( key[KEY_SPACE] ) {}
	
			// Swap display buffer to screen //
			gfxSwapBuffer();
		}
	}
	
	gfxExit();
	return 0;
}
END_OF_MAIN();
