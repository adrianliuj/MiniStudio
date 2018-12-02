#ifndef DRUM_H_NOT_INCLUDED
#define DRUM_H_NOT_INCLUDED

#include "Instrument.h"


double CoordX(double x);
double CoordY(double y);
void glVertex2dC(double x, double y);

void DrawCircleProj(double x, double y, double R, double Theta, double Rotation, int r, int g, int b);
void Draw_Drum_Face(double x, double y, double DrumR, double Theta, double Rotation);
//void Draw_Drum_Body(double x, double y, double DrumR, double Height, double Theta, double Rotation);
void Draw_Drum1(double x, double y, double DrumR, double Height, double Theta, double Rotation);
void Draw_Drum2(double x, double y, double DrumR, double Height, double Theta, double Rotation);
void Draw_ride(double x, double y, double R, double Theta, double Rotation, double Height);
void Draw_Hit(double x, double y, double R, double Theta, double Rotation);

class Drum :public Instrument
{
private:
	int key_;
	int hit_cycle1;
	int hit_cycle2;
	int hit_cycle3;
	YsSoundPlayer::SoundData hihat, hitom, kick,
		lowtom, ride, ridebell,
		ridecrash, snare, snareroll;
	YsRawPngDecoder png;

	//parameters for drawing
	const double Height1 = 40;
	const double DrumR1 = 60;
	const double Theta1 = PI / 3;
	const double Rotation1 = 0;
	const double Drum1_X = 220;
	const double Drum1_Y = 150;

	const double Height2 = 45;
	const double DrumR2 = 90;
	const double Theta2 = PI / 6;
	const double Rotation2 = 0;
	const double Drum2_X = 100;
	const double Drum2_Y = 120;

	const double Height3 = 160;
	const double DrumR3 = 60;
	const double Theta3 = PI / 3;
	const double Rotation3 = 0;
	const double Drum3_X = 325;
	const double Drum3_Y = 220;

public:
	Drum();
	void Load();
	void setKey(int key);
	void Play();
	void Draw();

};
#endif /* Drum_h */
