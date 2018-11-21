#include "stdio.h"
#include "Bass.h"

//global variable player
YsSoundPlayer player;

// external variable shared between different instruments
extern int windowW = 1000;
extern int windowH = 800;

// main excution
int main(void) {

	// initialize bass 
	Bass bass;
	// open Window
	FsOpenWindow(16, 16, windowW, windowH, 1);
	// start global player
	player.Start();

	// start while loop
	int stop = 0;
	while (stop == 0) {

		// search for key input
		FsPollDevice();
		auto key = FsInkey();

		// clear window
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// excution based on key input
		switch (key) {
		// stop immediately if ESC is pressed
		case FSKEY_ESC:
			stop = 1;
			break;
		// default excution
		default:
			// setKey, play, and draw
			bass.setKey(key);
			bass.play();
			bass.draw();
			break;
		}
		// swarp buffer and sleep
		FsSwapBuffers();
		FsSleep(25);
	}
}