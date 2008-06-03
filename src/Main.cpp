// - ------------------------------------------------------------------------------------------ - //
#include <AllegroGraphics/Graphics.h>
#include <AllegroGraphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //


// Generator //

// Collector //

// Particle //

// Magnet //


// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	gfxInit( 480, 320, false, 2 );
	
	do {
		cGame Game;
	
		while( !gfxShutdown() ) {	
			gfxClearBuffer( RGB(70,0,0) );
			
			Mouse.Update();
			Camera.Update();

			// Reset Hack //
			if ( key[KEY_TAB] )
				break;
			
			if ( mouse_b == 2 ) {
				gfxAddCameraPos( -(Mouse.Diff() * gfxGetCameraScale()) );
			}
			gfxConstrainCamera( Game.GetBounds().Vertex[0], Game.GetBounds().Vertex[1] );			
			
			if ( Mouse.WheelDiff() ) {
				gfxAddCameraScale( Real(Mouse.WheelDiff()) * Real(0.1) );
				gfxConstrainCameraScale( Real::One, Real(4) );
			}
			
			
			// Step the game //
			Game.Step();
			Game.Step();
//			Game.Step();
//			Game.Step();
//
//			Game.Step();
//			Game.Step();
//			Game.Step();
//			Game.Step();
			
			// Prior to drawing, set the current matrix to suit drawing relative to the camera //
			gfxSetCameraMatrix();
			// Draw the game //
			Game.Draw();
					
			// Draw center cross //
			gfxDrawCross( gfxGetCameraCenter(), 4 );

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
	while( key[KEY_TAB] );
	
	gfxExit();
	return 0;
}
END_OF_MAIN();
// - ------------------------------------------------------------------------------------------ - //
