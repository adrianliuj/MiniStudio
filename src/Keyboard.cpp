#include "..\include\Instrument.h"
#include "..\include\Keyboard.h"

Keyboard::Keyboard(){
	//key_ = -1 because legal input is from 0 - 9
	key_ = -1;
	top_ = 50;
	left_ = 50;
	keyW_ = 30;
	keyH_ = 200;
	Load();
	for (int i = 0; i < 10; ++i) {
		sounddataList_.push_back(shared_ptr<YsSoundPlayer::SoundData>(new YsSoundPlayer::SoundData));
	}
}
void Keyboard::Load() {
	// this is a naive implementation
	// just manually add absolute path
	// We cannot use vector<Sounddata> because of memory allocation problems
	// path to source file subject to change
	samples.push_back("..\\..\\resource\\keyboard\\00.wav");
	samples.push_back("..\\..\\resource\\keyboard\\01.wav");
	samples.push_back("..\\..\\resource\\keyboard\\02.wav");
	samples.push_back("..\\..\\resource\\keyboard\\03.wav");
	samples.push_back("..\\..\\resource\\keyboard\\04.wav");
	samples.push_back("..\\..\\resource\\keyboard\\05.wav");
	samples.push_back("..\\..\\resource\\keyboard\\06.wav");
	samples.push_back("..\\..\\resource\\keyboard\\07.wav");
	samples.push_back("..\\..\\resource\\keyboard\\08.wav");
	samples.push_back("..\\..\\resource\\keyboard\\09.wav");
	return;
}
void Keyboard::Draw() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	for (int i = 0; i < 10; ++i) {
		// draw keys
		if (key_ == i) {
			glColor3f(0., 0., 0.);
		}
		else glColor3f(255., 255., 255.);
		glBegin(GL_QUADS);
		glVertex2i(left_ + i * keyW_, top_);
		glVertex2i(left_ + (i + 1) * keyW_, top_);
		glVertex2i(left_ + (i + 1) * keyW_, top_ + keyH_);
		glVertex2i(left_ + i * keyW_, top_ + keyH_);
		glEnd();
		// draw boundary
		glColor3f(0.,0.,0.);
		glBegin(GL_LINE_LOOP);
		glVertex2i(left_ + i * keyW_, top_);
		glVertex2i(left_ + (i + 1) * keyW_, top_);
		glVertex2i(left_ + (i + 1) * keyW_, top_ + keyH_);
		glVertex2i(left_ + i * keyW_, top_ + keyH_);
		glEnd();
	}
	return;
}
void Keyboard::Play() {
	if (key_ < 0 || key_ > 9) return;
	auto res = sounddataList_[key_] -> LoadWav(samples[key_].c_str());
	player.PlayOneShot(*(sounddataList_[key_]));
	if (*player.playerStatePtr == YsSoundPlayer::STATE_ENDED) {
		cout << "end" << endl;
		key_ = -1;
	}
}
void Keyboard::setKey(int key) {
	//lets save the range of key is from 0 - 9
	if (key - FSKEY_0 > 9 || key - FSKEY_0 < 0) return;
	key_ = key - FSKEY_0;
	return;
}