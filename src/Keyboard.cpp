//#include "Instrument.h"
#include "Keyboard.h"

Keyboard::Keyboard(){
	//key_ = -1 because legal input is from 0 - 9
	key_ = -1;
	// top_ and left_ are coordinate of top left corner
	top_ = 110;
	left_ = 20;
	keyW_ = 36;
	keyH_ = 180;
	blackkeyW_ = 24;
	blackkeyH_ = 100;
	radius_ = 3;
	// piano body shape
	redH_ = 5;
	blackH_ = 40;
	// book shape
	bookUp_ = 100;
	bookDown_ = 10;
	bookW_ = 80;
	//initial alpha = 0.3;
	alpha_ = 0.3;
	blackpos_ = { 1,2,4,5,6,8,9 };
	Load();
	for (int i = 0; i < 10; ++i) {
		sounddataList_.push_back(shared_ptr<YsSoundPlayer::SoundData>(new YsSoundPlayer::SoundData));
	}
}
void Keyboard::Load() {
	samples.push_back("00.wav");
	samples.push_back("01.wav");
	samples.push_back("02.wav");
	samples.push_back("03.wav");
	samples.push_back("04.wav");
	samples.push_back("05.wav");
	samples.push_back("06.wav");
	samples.push_back("07.wav");
	samples.push_back("08.wav");
	samples.push_back("09.wav");
	return;
}
void Keyboard::Draw() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//draw piano body
	glBegin(GL_QUADS);
	glColor3f(255., 0., 0.);
	glVertex2i(left_, top_ - redH_);
	glVertex2i(left_ + 10 * keyW_, top_ - redH_);
	glVertex2i(left_ + 10 * keyW_, top_);
	glVertex2i(left_, top_);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0., 0., 0.);
	glVertex2i(left_, top_ - blackH_);
	glVertex2i(left_ + 10 * keyW_, top_ - blackH_);
	glVertex2i(left_ + 10 * keyW_, top_ - redH_);
	glVertex2i(left_, top_ - redH_);
	glEnd();
	//draw reference book
	glColor3f(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2i(left_ + 5 * keyW_ - bookW_, top_ - bookUp_);
	glVertex2i(left_ + 5 * keyW_, top_ - bookUp_);
	glVertex2i(left_ + 5 * keyW_, top_ - bookDown_);
	glVertex2i(left_ + 5 * keyW_ - bookW_, top_ - bookDown_);
	glEnd();

	glColor3f(255, 255, 255);
	glBegin(GL_QUADS);
	// middle line is left_ + 5 * keyW_;
	glVertex2i(left_ + 5 * keyW_ + bookW_, top_ - bookUp_);
	glVertex2i(left_ + 5 * keyW_, top_ - bookUp_);
	glVertex2i(left_ + 5 * keyW_, top_ - bookDown_);
	glVertex2i(left_ + 5 * keyW_ + bookW_, top_ - bookDown_);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(left_ + 5 * keyW_ - bookW_, top_ - bookUp_);
	glVertex2i(left_ + 5 * keyW_, top_ - bookUp_);
	glVertex2i(left_ + 5 * keyW_, top_ - bookDown_);
	glVertex2i(left_ + 5 * keyW_ - bookW_, top_ - bookDown_);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(left_ + 5 * keyW_ + bookW_, top_ - bookUp_);
	glVertex2i(left_ + 5 * keyW_, top_ - bookUp_);
	glVertex2i(left_ + 5 * keyW_, top_ - bookDown_);
	glVertex2i(left_ + 5 * keyW_ + bookW_, top_ - bookDown_);
	glEnd();



	for (int i = 0; i < 10; ++i) {
		// draw pressed key
		if (key_ == i + 1 ||(key_ == 0 && i == 9)) {
			glColor4f(0, 0, 0, alpha_);
//            cout << "alpha = " << alpha_ << endl;
			glBegin(GL_QUADS);
			glVertex2i(left_ + i * keyW_, top_);
			glVertex2i(left_ + (i + 1) * keyW_, top_);
			glVertex2i(left_ + (i + 1) * keyW_, top_ + keyH_);
			glVertex2i(left_ + i * keyW_, top_ + keyH_);
			glEnd();
		}
		// draw boundary
		glColor3f(0.,0.,0.);
		glBegin(GL_LINE_LOOP);
		glVertex2i(left_ + i * keyW_, top_);
		glVertex2i(left_ + (i + 1) * keyW_, top_);
		glVertex2i(left_ + (i + 1) * keyW_, top_ + keyH_ - radius_);
		glVertex2i(left_ + (i + 1) * keyW_ - radius_, top_ + keyH_);
		glVertex2i(left_ + i * keyW_ + radius_, top_ + keyH_);
		glVertex2i(left_ + i * keyW_, top_ + keyH_ - radius_);
		glEnd();
        
        // draw character
        glRasterPos2d(left_ + i * keyW_ + keyW_ / 2 - 4, top_ + 140);
        glColor3ub(255, 0, 0);
        if (i != 9)
            YsGlDrawFontBitmap10x14(to_string(i + 1).c_str());
        else
            YsGlDrawFontBitmap10x14(to_string(0).c_str());
        
	}
	// draw black chord
	for (int i : blackpos_) {
		glColor3f(0., 0., 0.);
		glBegin(GL_POLYGON);
		glVertex2i(left_ + i * keyW_ - blackkeyW_ / 2, top_);
		glVertex2i(left_ + i * keyW_ + blackkeyW_ / 2, top_);
		glVertex2i(left_ + i * keyW_ + blackkeyW_ / 2, top_ + blackkeyH_ - radius_);
		glVertex2i(left_ + i * keyW_ + blackkeyW_ / 2 - radius_, top_ + blackkeyH_);
		glVertex2i(left_ + i * keyW_ - blackkeyW_ / 2 + radius_, top_ + blackkeyH_);
		glVertex2i(left_ + i * keyW_ - blackkeyW_ / 2, top_ + blackkeyH_ - radius_);
		glEnd();
	}
	return;
}
void Keyboard::Play() {
	cout << "key:" << key_ << endl;
	if (key_ >= 0 && key_ <= 9) {
		auto res = sounddataList_[key_] -> LoadWav(samples[key_].c_str());
		player.PlayOneShot(*(sounddataList_[key_]));
		//auto status = player.IsPlaying(*(sounddataList_[key_]));
		//if (YSTRUE != status) {
		//	cout << "end" << endl;
		//	key_ = -1;
		//}
	}
	return;
}
void Keyboard::setKey(int key) {
	//lets save the range of key is from 0 - 9
	if (key - FSKEY_0 <= 9 || key - FSKEY_0 >= 0) {
		key_ = key - FSKEY_0;
	} 
	else key_ = -1;
	return;
}

void Keyboard::setAlpha(float alpha) {
	alpha_ = alpha * 0.3;
	return;
}
