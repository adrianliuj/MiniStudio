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
	chords[0].setXY(xW / 2 - 165 + xC, 60 + yC);
	for (int i = 0; i < 6; i++) {
		chords[i + 1].setXY(chords[i].getX() + 60, chords[i].getY() - 4);
	}
}

void Bass::load() {
	// load corresponding sound profile
	wav[1].LoadWav("../BassSoundProfile/Am.wav");
	wav[2].LoadWav("../BassSoundProfile/Dm.wav");
	wav[3].LoadWav("../BassSoundProfile/Em.wav");
	wav[4].LoadWav("../BassSoundProfile/G.wav");
	wav[5].LoadWav("../BassSoundProfile/Am.wav");
	wav[6].LoadWav("../BassSoundProfile/Dm.wav");
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

	resetState();

	// input keys for different Bass chord are set as UIOPKL
	switch (key) {
	case FSKEY_U:
		StopAll();
		// start playing sound
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
	case FSKEY_K:
		StopAll();
		chords[4].setState(1);
		player.PlayOneShot(wav[5]);
		break;
	case FSKEY_L:
		StopAll();
		chords[5].setState(1);
		player.PlayOneShot(wav[6]);
		break;
	case FSKEY_T:
		StopAll();
		break;
	default:
		break;
	}


	//player.End();
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
	glVertex2d(xC + xW, yC);
	glVertex2d(xC + xW, yC + yW);
	glVertex2d(xC, yC + yW);
	glEnd();
	int inc = 30;
	glBegin(GL_QUADS);
	glColor3ub(149, 79, 29);
	glVertex2d(xC, yC+inc);
	glVertex2d(xC+xW, yC);
	glVertex2d(xC+xW, yC+yW-inc);
	glVertex2d(xC, yC+yW);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2d(xC, yC+20+inc);
	glColor3ub(0, 0, 0);
	glVertex2d(xC + xW, yC + 20);
	glColor3ub(130, 60, 10);
	glVertex2d(xC + xW, yC + yW/2-10);
	glColor3ub(130, 60, 10);
	glVertex2d(xC, yC + yW/2-10 + inc);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(130, 60, 10);
	glVertex2d(xC, yC + yW/2-10 + inc);
	glColor3ub(130, 60, 10);
	glVertex2d(xC + xW, yC + yW/2-10);
	glColor3ub(0, 0, 0);
	glVertex2d(xC + xW, yC + yW-20 - inc);
	glColor3ub(0, 0, 0);
	glVertex2d(xC, yC + yW-20);
	glEnd();
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
	for (int i = 1; i < 7; i++) {
		player.Stop(wav[i]);
	}
}

void Bass::resetState() {
	for (int i = 1; i < 7; i++) {
		if (player.IsPlaying(wav[i]) == 1) {
			chords[i - 1].setState(1);
		}
		else {
			chords[i - 1].setState(0);
		}
	}
}

