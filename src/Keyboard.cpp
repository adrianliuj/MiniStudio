#include "..\include\Instrument.h"
#include "..\include\Keyboard.h"

Keyboard::Keyboard(){
	//key_ = -1 because legal input is from 0 - 9
	key_ = -1;
	load();
}
void Keyboard::load() {
	// this is a naive implementation
	// just manually add absolute path
	// We cannot use vector<Sounddata> because of memory allocation problems
	// path to source file subject to change
	samples.push_back("..\\..\\resource\\keyboard\\deal.wav");
	samples.push_back("..\\..\\resource\\keyboard\\beep.wav");
	samples.push_back("..\\..\\resource\\keyboard\\A#2.wav");
	samples.push_back("..\\..\\resource\\keyboard\\A#3.wav");
	samples.push_back("..\\..\\resource\\keyboard\\A#4.wav");
	samples.push_back("..\\..\\resource\\keyboard\\A#5.wav");
	samples.push_back("..\\..\\resource\\keyboard\\A#6.wav");
	samples.push_back("..\\..\\resource\\keyboard\\A#7.wav");
	samples.push_back("..\\..\\resource\\keyboard\\A0.wav");
	samples.push_back("..\\..\\resource\\keyboard\\A1.wav");
	return;
}
void Keyboard::draw() {
	return;
}
void Keyboard::play() {
	if (key_ < 0 || key_ > 9) return;
	// create player and sounddata
	//YsSoundPlayer player;
	//YsSoundPlayer::SoundData sounddata;
	//auto res = sounddata.LoadWav(samples[key_].c_str());
	//player.Start();
	// Subject to change
	if (key_ == 0) {
		data0.LoadWav("..\\..\\resource\\keyboard\\deal.wav");
		player.PlayOneShot(data0);
	}
	else if (key_ == 1) {
		data1.LoadWav("..\\..\\resource\\keyboard\\deal.wav");
		player.PlayOneShot(data1);
	}
	//data2.LoadWav("..\\..\\resource\\keyboard\\beep.wav");
	//while (player.IsPlaying(sounddata)) {
	//	player.KeepPlaying();
	//}
	//player.End();
}
void Keyboard::setKey(int key) {
	//lets save the range of key is from 0 - 9
	if (key - FSKEY_0 > 9 || key - FSKEY_0 < 0) return;
	key_ = key - FSKEY_0;
	return;
}