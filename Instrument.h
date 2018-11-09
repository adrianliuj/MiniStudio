#pragma once
#include <vector>
#include <string>
#include "fssimplewindow.h"
#include "Instrument.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"

using namespace std;
class Instrument {
	virtual void load(string path) = 0;
	virtual void play() = 0;
	virtual void draw() = 0;
	virtual void setKey(int key) = 0;
protected:
	//load all the sound data
	vector<YsSoundPlayer::SoundData> samples;
	//receive key stroke
	int key;
};