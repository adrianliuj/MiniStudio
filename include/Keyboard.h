#pragma once
#include "Instrument.h"
extern YsSoundPlayer player;
class Keyboard : public Instrument{
public:
	Keyboard();
	void load();
	void draw();
	void play();
	void setKey(int key);
private:
	YsSoundPlayer::SoundData data0, data1, data2;
};