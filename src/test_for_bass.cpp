#include "stdio.h"
#include "Bass.h"

//global variable player
YsSoundPlayer player;

extern int windowW = 800;
extern int windowH = 600;

int main(void) {

	Bass bass;

	FsOpenWindow(16, 16, windowW, windowH, 1);

	player.Start();

	int stop = 0;
	while (stop == 0) {

		FsPollDevice();
		auto key = FsInkey();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// search for input
		switch (key) {
		case FSKEY_ESC:
			stop = 1;
			break;
		default:
			bass.setKey(key);
			bass.play();
			bass.draw();
			break;
		}
		FsSwapBuffers();
		FsSleep(25);
	}
}