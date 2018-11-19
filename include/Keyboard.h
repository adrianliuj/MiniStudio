#pragma once
#include "Instrument.h"
extern YsSoundPlayer player;

class Keyboard : public Instrument{
public:
	Keyboard();
	void Load();
	void Draw();
	void Play();
	void setKey(int key);
private:
	//YsSoundPlayer::SoundData data0, data1, data2;
	vector<shared_ptr<YsSoundPlayer::SoundData>> sounddataList_;
	int top_, left_, keyW_, keyH_;
};