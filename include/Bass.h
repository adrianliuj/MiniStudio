#ifndef BASS_H_NOT_INCLUDED
#define BASS_H_NOT_INCLUDED

#include "Instrument.h"

extern YsSoundPlayer player;
extern int windowW;
extern int windowH;

class chord {
public:
	int getState();
	void setState(int s);
	int getX();
	int getY();
	void setXY(int X, int Y);

	chord();
	// draw Chord
	void drawChord(int i);

private:
	// state of string
	int state = 0;
	int R, G, B;
	int x, y;
};

class Bass : public Instrument {
public:
	Bass();

	void load();
	void play();
	void draw();
	void setKey(int keyVal);

private:
	// position of bass section in the window 
	int xC = 0, yC = 0;
	int key;
	void drawBass() const;

	chord chords[6];
	YsSoundPlayer::SoundData wav[6]; 
};
#endif
