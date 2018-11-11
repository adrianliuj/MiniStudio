#pragma once
#include "Instrument.h"

class Keyboard : public Instrument{
public:
	Keyboard();
	void load();
	void draw();
	void play();
	void setKey(int key);
};