#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "fssimplewindow.h"
#include "Instrument.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"

using namespace std;
class Instrument {
public:
	Instrument() :samples(vector<string>()), key_(0) {}
	virtual void Load() = 0;
	virtual void Play() = 0;
	virtual void Draw() = 0;
	virtual void setKey(int key) = 0;
protected:
	//load all the sound data
	vector<string> samples;
	//receive key stroke
	int key_;
};