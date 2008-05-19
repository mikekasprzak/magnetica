
#include <AllegroGraphics/Graphics.h>
#include <AllegroGraphics/GraphicsDraw.h>

#include <PolyMap/PolyMap.h>
#include <AdvancedGeometry/PointVsSphere2D.h>
#include <AdvancedGeometry/PointVsPairRect2D.h>
#include <AdvancedGeometry/PointVsShapeRect2D.h>
#include <AdvancedGeometry/PointVsRadiusRect2D.h>

#include <AdvancedGeometry/PointVsPolygon2D.h>
#include <AdvancedGeometry/PointVsEdgedPolygon2D.h>


using namespace std;



int main( int argc, char* argv[] ) {
	gfxInit( 480, 320, false, 2 );


	while( !gfxShutdown() ) {
		gfxClearBuffer( RGB(70,0,0) );
		
		// Note the cursor position //
		Vector2D Mouse(mouse_x / ScreenScalar, mouse_y / ScreenScalar);
		
	
	
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
