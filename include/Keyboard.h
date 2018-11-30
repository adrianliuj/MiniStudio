#ifndef KEYBORAD_H_NOT_INCLUDED
#define KEYBORAD_H_NOT_INCLUDED
#include "Instrument.h"
class Keyboard : public Instrument{
public:
	Keyboard();
	void Load();
	void Draw();
	void Play();
	void setKey(int key);
	void setAlpha(float alpha);
private:
	//YsSoundPlayer::SoundData data0, data1, data2;
	vector<shared_ptr<YsSoundPlayer::SoundData>> sounddataList_;
	YsSoundPlayer::SoundData tmp;
	int top_, left_;
	int keyW_, keyH_, blackkeyW_, blackkeyH_;
	int radius_;
	int redH_, blackH_;
	int bookUp_, bookDown_, bookW_;
	float alpha_;
	vector<int> blackpos_;
    vector<string> samples;
    int key_;
};
#endif
