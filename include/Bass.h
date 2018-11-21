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
	// state of chord
	int state = 0;
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
	// position and size of bass section in the window 
	int xC = 300, yC = 400, xW = 400, yW = 300;
	int key;
	void drawBass() const;
	void StopAll();
	void resetState();

	chord chords[7];
	YsSoundPlayer::SoundData wav[8]; 

};
#endif
