#include "Instrument.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "Bass.h"
#include "ysglfontdata.h"

chord::chord() {
	state = 0;
    x = 0;
    y = 0;
}

int chord::getState() {
	return state;
}

void chord::setState(int s) {
	state = s;
}

int chord::getX() {
	return x;
}

int chord::getY() {
	return y;
}

void chord::setXY(int X, int Y) {
	this->x = X;
	this->y = Y;
}

void chord::drawChord(int i) {
	// enabling blend (in case not enabled in main)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	if(this->getState()==1) {
		glColor4ub(135, 200, 240, 150);
		glBegin(GL_QUADS);
		glVertex2i(x-10, y-10);
		glVertex2i(x+40, y-10);
		glVertex2i(x+40, y+210);
		glVertex2i(x-10, y+210);
		glEnd();
	}
	else {
		glColor4ub(200, 200, 200, 150);
		glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x+30, y);
		glVertex2i(x+30, y + 200);
		glVertex2i(x, y + 200);
		glEnd();
	}
	glColor3ub(50, 0, 0);
	glRasterPos2d(getX()+5, getY()+110);
	// will change name later, don't know the names
	switch (i) {
	case 0:
		YsGlDrawFontBitmap16x20("Am");
		break;
	case 1:
		YsGlDrawFontBitmap16x20("C");
		break;
	case 2:
		YsGlDrawFontBitmap16x20("D");
		break;
	case 3:
		YsGlDrawFontBitmap16x20("Dm");
		break;
	case 4:
		YsGlDrawFontBitmap16x20("Em");
		break;
	case 5:
		YsGlDrawFontBitmap16x20("F");
		break;
	case 6:
		YsGlDrawFontBitmap16x20("G");
		break;
	default:
		break;
	}
}

Bass::Bass() {
	// load different Bass Sound Profiles
	Load();
	// set up chords XY
	chords[0].setXY(xW / 2 - 180 + xC, 60 + yC);
	for (int i = 0; i < 7; i++) {
		chords[i + 1].setXY(chords[i].getX() + 55, chords[i].getY() - 4);
	}
}

void Bass::Load() {
	// load corresponding sound profile
    FsChangeToProgramDir();
	wav[1].LoadWav("Am.wav");
	wav[2].LoadWav("C.wav");
	wav[3].LoadWav("D.wav");
	wav[4].LoadWav("Dm.wav");
	wav[5].LoadWav("Em.wav");
	wav[6].LoadWav("F.wav");
	wav[7].LoadWav("G.wav");

	png1.Decode("bass1.png");
	png1.Flip();
	printf("rawpixel-brown-wood.png loaded, width is %d, height is %d\n", png1.wid, png1.hei);

	png2.Decode("bass3.png");
	png2.Flip();
	printf("yann-allegre-dark-wood.png loaded, width is %d, height is %d\n", png2.wid, png2.hei);

	png3.Decode("bass2.png");
	png3.Flip();
	printf("ruvim-noga-backgroud.png loaded, width is %d, height is %d\n", png3.wid, png3.hei);
}

void Bass::Draw() {
	// draw Bass
	drawBass();
	
	// draw six chord
	for (int i = 0; i < 7; i++) {
		chords[i].drawChord(i);
	}
}

void Bass::Play() {

	resetState();

	// input keys for different Bass chord are set as UIOPKL
	switch (key) {
	// start playing sound based on keyboard input
	case FSKEY_U:
		StopAll();
		chords[0].setState(1);
		player.PlayOneShot(wav[1]);
		break;
	case FSKEY_I:
		StopAll();
		chords[1].setState(1);
		player.PlayOneShot(wav[2]);
		break;
	case FSKEY_O:
		StopAll();
		chords[2].setState(1);
		player.PlayOneShot(wav[3]);
		break;
	case FSKEY_P:
		StopAll();
		chords[3].setState(1);
		player.PlayOneShot(wav[4]);
		break;
	case FSKEY_J:
		StopAll();
		chords[4].setState(1);
		player.PlayOneShot(wav[5]);
		break;
	case FSKEY_K:
		StopAll();
		chords[5].setState(1);
		player.PlayOneShot(wav[6]);
		break;
	case FSKEY_L:
		StopAll();
		chords[6].setState(1);
		player.PlayOneShot(wav[7]);
		break;
	case FSKEY_T:
		StopAll();
		break;
	default:
		break;
	}
}

void Bass::setKey(int keyVal) {
	// assuming user input UIOPKL (subject to change)
	key = keyVal;
}

void Bass::squareTextureMap(YsRawPngDecoder &png, int x1, int y1, int x2, int y2,
	int x3, int y3, int x4, int y4) {

	GLuint textID;
	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textID);
	glBegin(GL_QUADS);
	glTexCoord2d(1.0, 1.0); glVertex2i(x1, y1);
	glTexCoord2d(0.0, 1.0); glVertex2i(x2, y2);
	glTexCoord2d(0.0, 0.0); glVertex2i(x3, y3);
	glTexCoord2d(1.0, 0.0); glVertex2i(x4, y4);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Bass::drawBass() {
	// draw Bass
	// inc is incline for bass
	squareTextureMap(png3, xC, yC, xC + xW, yC, xC + xW, yC + yW, xC, yC + yW);
	int inc = 30;
	squareTextureMap(png1, xC, yC + inc, xC + xW, yC, xC + xW, yC + yW - inc, xC, yC + yW);
	squareTextureMap(png2, xC, yC + inc + 20, xC + xW, yC + 20, xC + xW, yC + yW - 20 - inc, xC, yC + yW - 20);

	// draw strings
	int y1;
	for (int i = 0; i < 6; i++) {
		y1 = (i + 1) * 35 + 13 + yC;
		glLineWidth(4.0f);
		glBegin(GL_LINES);
		glColor3ub(210, 210, 210);
		glVertex2d(xC, y1+inc);
		glVertex2d(xC + xW, y1);
		glEnd();
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3ub(150, 150, 150);
		glVertex2d(xC, y1 + inc+3);
		glVertex2d(xC + xW, y1+3);
		glEnd();
	}
	glFlush();
}

void Bass::StopAll() {
	for (int i = 1; i < 8; i++) {
		player.Stop(wav[i]);
	}
}

void Bass::resetState() {
	for (int i = 1; i < 8; i++) {
		if (player.IsPlaying(wav[i]) == 1) {
			chords[i - 1].setState(1);
		}
		else {
			chords[i - 1].setState(0);
		}
	}
}

