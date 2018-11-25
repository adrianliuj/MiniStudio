#ifndef BASS_H_NOT_INCLUDED
#define BASS_H_NOT_INCLUDED

//#include "Instrument.h"
#include "yspng.h"

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

	void Load();
	void Play();
	void Draw();
	void setKey(int keyVal);

private:
	// position and size of bass section in the window 
	int xC = 400, yC = 300, xW = 400, yW = 300;
	int key;
	void drawBass();
	void StopAll();
	void resetState();
	void squareTextureMap(YsRawPngDecoder &png, int x1, int y1, int x2, int y2,
		int x3, int y3, int x4, int y4);

	YsRawPngDecoder png1, png2, png3;
	chord chords[7];
	YsSoundPlayer::SoundData wav[8]; 

};
#endif
