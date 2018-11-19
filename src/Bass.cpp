#include "..\Group Project\Instrument.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "Bass.h"
#include "ysglfontdata.h"

chord::chord() {
	state = 0;
	x = 0, y = 0;
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
	glColor3f(0, 0, 0);
	glRasterPos2d(getX()+10, getY()+110);
	// will change name later, don't know the names
	switch (i) {
	case 0:
		YsGlDrawFontBitmap16x20("1");
		break;
	case 1:
		YsGlDrawFontBitmap16x20("2");
		break;
	case 2:
		YsGlDrawFontBitmap16x20("3");
		break;
	case 3:
		YsGlDrawFontBitmap16x20("4");
		break;
	case 4:
		YsGlDrawFontBitmap16x20("5");
		break;
	case 5:
		YsGlDrawFontBitmap16x20("6");
	break;
	}
}

Bass::Bass() {
	// load different Bass Sound Profiles
	load();
	// set up chords XY
	chords[0].setXY(windowW / 2 - 165, 60);
	for (int i = 0; i < 6; i++) {
		chords[i + 1].setXY(chords[i].getX() + 60, chords[i].getY() - 4);
	}
}

void Bass::load() {
	// load corresponding sound profile
	wav[0].LoadWav("../BassSoundProfile/a.wav");
	wav[1].LoadWav("../BassSoundProfile/b.wav");
	wav[2].LoadWav("../BassSoundProfile/c.wav");
	wav[3].LoadWav("../BassSoundProfile/d.wav");
	wav[4].LoadWav("../BassSoundProfile/e.wav");
	wav[5].LoadWav("../BassSoundProfile/f.wav");
}

void Bass::draw() {
	// draw Bass
	drawBass();
	
	// draw six chord
	for (int i = 0; i < 6; i++) {
		chords[i].drawChord(i);
	}
}

void Bass::play() {
	//re-initialize chord state
	if (chords[0].getState() == 1 || chords[1].getState() == 1 ||
		chords[2].getState() == 1 || chords[3].getState() == 1 ||
		chords[4].getState() == 1 || chords[5].getState() == 1) {
		chords[0].setState(0);
		chords[1].setState(0);
		chords[2].setState(0);
		chords[3].setState(0);
		chords[4].setState(0);
		chords[5].setState(0);
	}

	// input keys for different Bass chord are set as UIOPKL
	switch (key) {
	case FSKEY_U:
		// start playing sound
		chords[0].setState(1);
		player.PlayOneShot(wav[0]);
		break;
	case FSKEY_I:
		chords[1].setState(1);
		player.PlayOneShot(wav[1]);
		break;
	case FSKEY_O:
		chords[2].setState(1);
		player.PlayOneShot(wav[2]);
		break;
	case FSKEY_P:
		chords[3].setState(1);
		player.PlayOneShot(wav[3]);
		break;
	case FSKEY_K:
		chords[4].setState(1);
		player.PlayOneShot(wav[4]);
		break;
	case FSKEY_L:
		chords[5].setState(1);
		player.PlayOneShot(wav[5]);
		break;
	default:
		key = 0;
		player.End();
		printf("Default\n");
		break;
	}
	printf("%d\n", key);
	player.End();
}

void Bass::setKey(int keyVal) {
	// assuming user input UIOPKL (subject to change)
	key = keyVal;
}

void Bass::drawBass() const {
	// draw Bass
	// inc is incline for bass
	glBegin(GL_QUADS);
	glColor3ub(180, 180, 180);
	glVertex2d(xC, yC);
	glVertex2d(xC + windowW, yC);
	glVertex2d(xC + windowW, yC + windowH);
	glVertex2d(xC, yC + windowH);
	glEnd();
	int inc = 30;
	glBegin(GL_QUADS);
	glColor3ub(149, 79, 29);
	glVertex2d(xC, yC+inc);
	glVertex2d(xC+windowW, yC);
	glVertex2d(xC+windowW, yC+windowH-inc);
	glVertex2d(xC, yC+windowH);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2d(xC, yC+20+inc);
	glColor3ub(0, 0, 0);
	glVertex2d(xC + windowW, yC + 20);
	glColor3ub(130, 60, 10);
	glVertex2d(xC + windowW, yC + windowH/2-10);
	glColor3ub(130, 60, 10);
	glVertex2d(xC, yC + windowH/2-10 + inc);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(130, 60, 10);
	glVertex2d(xC, yC + windowH/2-10 + inc);
	glColor3ub(130, 60, 10);
	glVertex2d(xC + windowW, yC + windowH/2-10);
	glColor3ub(0, 0, 0);
	glVertex2d(xC + windowW, yC + windowH-20 - inc);
	glColor3ub(0, 0, 0);
	glVertex2d(xC, yC + windowH-20);
	glEnd();
	// draw strings
	int y1;
	for (int i = 0; i < 6; i++) {
		y1 = (i + 1) * 35 + 13;
		glLineWidth(4.0f);
		glBegin(GL_LINES);
		glColor3ub(210, 210, 210);
		glVertex2d(xC, y1+inc);
		glVertex2d(xC + windowW, y1);
		glEnd();
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3ub(150, 150, 150);
		glVertex2d(xC, y1 + inc+3);
		glVertex2d(xC + windowW, y1+3);
		glEnd();
	}
	glFlush();
}


