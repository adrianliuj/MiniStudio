#include "../include/Drum.h"

/* Realize Drum Class */
Drum::Drum()
{
	key_ = 0;
	hit_cycle1 = 0;
	hit_cycle2 = 0;
	hit_cycle3 = 0;
	//init parameters for drawing
	Load();
}

void Drum::Load() {

	if (YSOK != hihat.LoadWav("../../MiniStudio/resource/drum/pearlkit-hihat.wav")) {
		printf("Failed to read hihat\n");
	}

	if (YSOK != hitom.LoadWav("../../MiniStudio/resource/drum/pearlkit-hitom1.wav")) {
		printf("Failed to read hitom1\n");
	}

	if (YSOK != kick.LoadWav("../../MiniStudio/resource/drum/pearlkit-kick.wav")) {
		printf("Failed to read kick\n");
	}

	if (YSOK != lowtom.LoadWav("../../MiniStudio/resource/drum/pearlkit-lowtom1.wav")) {
		printf("Failed to read lowtom1\n");
	}

	if (YSOK != ride.LoadWav("../../MiniStudio/resource/drum/pearlkit-ride1.wav")) {
		printf("Failed to read ride1\n");
	}

	if (YSOK != ridebell.LoadWav("../../MiniStudio/resource/drum/pearlkit-ridebell.wav")) {
		printf("Failed to read ridebell\n");
	}

	if (YSOK != ridecrash.LoadWav("../../MiniStudio/resource/drum/pearlkit-ridecrash.wav")) {
		printf("Failed to read ridecrash\n");
	}

	if (YSOK != snare.LoadWav("../../MiniStudio/resource/drum/pearlkit-snare1.wav")) {
		printf("Failed to read snare1\n");
	}

	if (YSOK != snareroll.LoadWav("../../MiniStudio/resource/drum/pearlkit-snareroll.wav")) {
		printf("Failed to read snareroll\n");
	}

}

void Drum::setKey(int key) {
	key_ = key;
}

void Drum::Play() {
	switch (key_) {
	case FSKEY_Q:
		player.Stop(hihat);
		player.PlayOneShot(hihat);
		break;
	case FSKEY_W:
		player.Stop(ridebell);
		player.PlayOneShot(ridebell);
		break;
	case FSKEY_S:
		player.Stop(hitom);
		player.PlayOneShot(hitom);
		break;
	case FSKEY_A:
		player.Stop(ridecrash);
		player.PlayOneShot(ridecrash);
		break;
	case FSKEY_X:
		player.Stop(kick);
		player.PlayOneShot(kick);
		break;
	case FSKEY_D:
		player.Stop(lowtom);
		player.PlayOneShot(lowtom);
		break;
	case FSKEY_Z:
		player.Stop(snare);
		player.PlayOneShot(snare);
		break;
	case FSKEY_E:
		player.Stop(ride);
		player.PlayOneShot(ride);
		break;
	case FSKEY_C:
		player.Stop(snareroll);
		player.PlayOneShot(snareroll);
		break;
    case FSKEY_T:
        player.Stop(snareroll);
        player.Stop(ride);
        player.Stop(snare);
        player.Stop(lowtom);
        player.Stop(kick);
        player.Stop(ridecrash);
        player.Stop(hitom);
        player.Stop(ridebell);
        player.Stop(hihat);
        break;
	}

}

void Drum::Draw() {
	Draw_Drum2(Drum2_X, Drum2_Y, DrumR2, Height2, Theta2, Rotation2);
	{
		if (key_ == FSKEY_S || key_ == FSKEY_D) {
			hit_cycle2 = 1;
		}
		if (hit_cycle2 > 0) {
			if (hit_cycle2 > 5) {
				hit_cycle2 = 0;
			}
			else {
				hit_cycle2 += 1;
				Draw_Hit(Drum2_Y, Drum2_X, DrumR2, Theta2, PI / 2 - Rotation2);
			}
		}
	}   //check and draw hit
	Draw_ride(Drum3_X, Drum3_Y, DrumR3, Theta3, Rotation3, Height3);
	{
		if (key_ == FSKEY_Q || key_ == FSKEY_W || key_ == FSKEY_E || key_ == FSKEY_A) {
			hit_cycle3 = 1;
		}
		if (hit_cycle3 > 0) {
			if (hit_cycle3 > 5) {
				hit_cycle3 = 0;
			}
			else {
				hit_cycle3 += 1;
				Draw_Hit(Drum3_X, Drum3_Y, DrumR3, Theta3, Rotation3);
			}
		}
	}   //check and draw hit
	Draw_Drum1(Drum1_X, Drum1_Y, DrumR1, Height1, Theta1, Rotation1);
	{
		if (key_ == FSKEY_Z || key_ == FSKEY_X || key_ == FSKEY_C) {
			hit_cycle1 = 1;
		}
		if (hit_cycle1 > 0) {
			if (hit_cycle1 > 5) {
				hit_cycle1 = 0;
			}
			else {
				hit_cycle1 += 1;
				Draw_Hit(Drum1_X, Drum1_Y, DrumR1, Theta1, Rotation1);
			}
		}
	}   //check and draw hit
	key_ = 0;    //reset the key because it`s in render, later than Player()
}

/* Realize coordinates trasform */
double CoordX(double x) {
	double Coordx = x;
	return Coordx;
}
double CoordY(double y) {
	double Coordy = 600 - y;
	return Coordy;
}
void glVertex2dC(double x, double y) {
	glVertex2d(CoordX(x), CoordY(y));
}

/* Realize basic blocks for drawing */
void DrawCircleProj(double x, double y, double R, double Theta, double Rotation, int r, int g, int b) {
	glColor3ub(r, g, b);
	for (int i = 0; i < 65; i++) {
		double angle = (double)i*PI / 32;
		double xp = x + cos(angle)*R * cos(Rotation) - sin(angle)*R * cos(Theta)* sin(Rotation);
		double yp = y + sin(angle)*R * cos(Theta) * cos(Rotation) + cos(angle)*R * sin(Rotation);
		glVertex2dC(xp, yp);
	}
}
void Draw_Drum_Face(double x, double y, double DrumR, double Theta, double Rotation) {

	double r = DrumR;
	glBegin(GL_POLYGON);
	DrawCircleProj(x, y, r, Theta, Rotation, 174, 179, 186);
	glEnd();

	r = 0.95 * DrumR;
	glBegin(GL_POLYGON);
	DrawCircleProj(x, y, r, Theta, Rotation, 255, 250, 240);
	glEnd();

	glShadeModel(GL_SMOOTH);
	r = 0.01 * DrumR;
	glBegin(GL_POLYGON);
	DrawCircleProj(x, y, r, Theta, Rotation, 200, 200, 0);
	r = 0.5 * DrumR;
	DrawCircleProj(x, y, r, Theta, Rotation, 255, 250, 240);
	glEnd();

}
void Draw_Drum_Body1(double x, double y, double DrumR, double Height, double Theta, double Rotation) {

	//Find the max and min index
	double x_min = 0, x_max = 0;
	int i_min = 0, i_max = 0;

	for (int i = 0; i < 65; i++) {
		double angle = (double)i*PI / 32;
		double xp = cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
		if (xp > x_max) {
			x_max = xp;
			i_max = i;
		}
		if (xp < x_min) {
			x_min = xp;
			i_min = i;
		}
	}
	//Draw the fundation
	{
		glBegin(GL_QUADS);
		glColor3ub(0.5 * 174, 0.5 * 179, 0.5 * 186);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max - 2.5, y);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max + 2.5, y);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max + 2.5, y - 100);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max - 2.5, y - 100);
		glEnd();
		glBegin(GL_QUADS);
		glColor3ub(0.5 * 174, 0.5 * 179, 0.5 * 186);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max + 2.5, y - 100);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max - 2.5, y - 100);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max - 30, y - 140);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max - 30 + 2.5, y - 140);
		glEnd();
		glBegin(GL_QUADS);
		glColor3ub(0.5 * 174, 0.5 * 179, 0.5 * 186);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max + 2.5, y - 100);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max - 2.5, y - 100);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max + 30, y - 140);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max + 30 + 2.5, y - 140);
		glEnd();
		glBegin(GL_QUADS);
		glColor3ub(0.5 * 174, 0.5 * 179, 0.5 * 186);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max + 2.5, y - 100);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max - 2.5, y - 100);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max - 5, y - 125);
		glVertex2dC(x + 0.5 * x_min + 0.5 * x_max - 5 + 2.5, y - 125);
		glEnd();

	}

	//Draw Drum Body
	GLuint textID;
	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wood.wid, wood.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, wood.rgba);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textID);
	//Draw UpperLeft Corner
	glBegin(GL_POLYGON);
	{
		double angle = (double)i_min*PI / 32;
		double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
		double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation);
		glTexCoord2d(1.0, 1.0);
		glVertex2dC(xp, yp);
	}
	//Draw the Body upper side
	{
		double angle = (double)i_max*PI / 32;
		double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
		double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation);
		glTexCoord2d(1.0, 0);
		glVertex2dC(xp, yp);
	}
	//Draw the Body right side
	{
		double angle = (double)i_max*PI / 32;
		double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
		double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation) - Height;
		glTexCoord2d(0, 0);
		glVertex2dC(xp, yp);
	}
	//Draw the Body lower side
	if (i_max > 32) {
		for (int i = i_max; i > i_min - 1; i--) {
			double angle = (double)i*PI / 32;
			double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
			double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation) - Height;
			glTexCoord2d(0, (abs(i_max - i_min) - abs(i_max - i)) / abs(i_max - i_min));
			glVertex2dC(xp, yp);
		}
	}
	else if (i_max < 32) {
		for (int i = i_max; i > 0; i--) {
			double angle = (double)i*PI / 32;
			double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
			double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation) - Height;
			glTexCoord2d(0, ((64 + i_max - i_min) - abs(i_max - i)) / (64 + i_max - i_min));
			glVertex2dC(xp, yp);
		}
		for (int i = 64; i > i_min - 1; i--) {
			double angle = (double)i*PI / 32;
			double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
			double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation) - Height;
			glTexCoord2d(0, abs(-i_min + i) / (64 + i_max - i_min));
			glVertex2dC(xp, yp);
		}
	}
	//Draw the left side of the body
//    {
//        double angle=(double)i_min*PI/32;
//        double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
//        double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - Height;
//        glTexCoord2d(0, 0);
//        glVertex2dC(xp, yp);
//    }
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void Draw_Drum_Body2(double x, double y, double DrumR, double Height, double Theta, double Rotation) {
	//Find the max and min index
	double x_min = 0, x_max = 0;
	int i_min = 0, i_max = 0;

	for (int i = 0; i < 65; i++) {
		double angle = (double)i*PI / 32;
		double xp = cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
		if (xp > x_max) {
			x_max = xp;
			i_max = i;
		}
		if (xp < x_min) {
			x_min = xp;
			i_min = i;
		}
	}
	//Draw Drum Body
	GLuint textID;
	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wood.wid, wood.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, wood.rgba);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textID);
	//Draw UpperLeft Corner
	glBegin(GL_POLYGON);
	{
		double angle = (double)i_min*PI / 32;
		double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
		double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation);
		glTexCoord2d(1.0, 1.0);
		std::swap(xp, yp);
		glVertex2dC(xp, yp);
	}
	//Draw the Body upper side
	{
		double angle = (double)i_max*PI / 32;
		double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
		double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation);
		glTexCoord2d(1.0, 0);
		std::swap(xp, yp);
		glVertex2dC(xp, yp);
	}
	//Draw the Body right side
	{
		double angle = (double)i_max*PI / 32;
		double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
		double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation) - Height;
		glTexCoord2d(0, 0);
		std::swap(xp, yp);
		glVertex2dC(xp, yp);
	}
	//Draw the Body lower side
	if (i_max > 32) {
		for (int i = i_max; i > i_min - 1; i--) {
			double angle = (double)i*PI / 32;
			double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
			double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation) - Height;
			glTexCoord2d(0, (abs(i_max - i_min) - abs(i_max - i)) / abs(i_max - i_min));
			std::swap(xp, yp);
			glVertex2dC(xp, yp);
		}
	}
	else if (i_max < 32) {
		for (int i = i_max; i > 0; i--) {
			double angle = (double)i*PI / 32;
			double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
			double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation) - Height;
			glTexCoord2d(0, ((64 + i_max - i_min) - abs(i_max - i)) / (64 + i_max - i_min));
			std::swap(xp, yp);
			glVertex2dC(xp, yp);
		}
		for (int i = 64; i > i_min - 1; i--) {
			double angle = (double)i*PI / 32;
			double xp = x + cos(angle)*DrumR * cos(Rotation) - sin(angle)*DrumR * cos(Theta)* sin(Rotation);
			double yp = y + sin(angle)*DrumR * cos(Theta) * cos(Rotation) + cos(angle)*DrumR * sin(Rotation) - Height;
			glTexCoord2d(0, abs(-i_min + i) / (64 + i_max - i_min));
			std::swap(xp, yp);
			glVertex2dC(xp, yp);
		}
	}
	//Draw the left side of the body
//    {
//        double angle=(double)i_min*PI/32;
//        double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
//        double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - Height;
//        std::swap(xp, yp);
//        glVertex2dC(xp, yp);
//    }
	glEnd();
	glDisable(GL_TEXTURE_2D);

}
void Draw_Drum1(double x, double y, double DrumR, double Height, double Theta, double Rotation) {
	Draw_Drum_Body1(x, y, DrumR, Height, Theta, Rotation);
	Draw_Drum_Face(x, y, DrumR, Theta, Rotation);
}
void Draw_Drum2(double x, double y, double DrumR, double Height, double Theta, double Rotation) {
	Draw_Drum_Body2(x, y, DrumR, Height, Theta, Rotation);
	Draw_Drum_Face(y, x, DrumR, Theta, PI / 2 - Rotation);
}
void Draw_ride(double x, double y, double R, double Theta, double Rotation, double Height) {
	{
		glBegin(GL_QUADS);
		glColor3ub(0.5 * 174, 0.5 * 179, 0.5 * 186);
		glVertex2dC(x - 2.5, y);
		glVertex2dC(x + 2.5, y);
		glVertex2dC(x + 2.5, y - Height);
		glVertex2dC(x - 2.5, y - Height);
		glEnd();
		glBegin(GL_QUADS);
		glColor3ub(0.5 * 174, 0.5 * 179, 0.5 * 186);
		glVertex2dC(x + 2.5, y - Height);
		glVertex2dC(x - 2.5, y - Height);
		glVertex2dC(x - 30, y - Height - 40);
		glVertex2dC(x - 30 + 2.5, y - Height - 40);
		glEnd();
		glBegin(GL_QUADS);
		glColor3ub(0.5 * 174, 0.5 * 179, 0.5 * 186);
		glVertex2dC(x + 2.5, y - Height);
		glVertex2dC(x - 2.5, y - Height);
		glVertex2dC(x + 30, y - Height - 40);
		glVertex2dC(x + 30 + 2.5, y - Height - 40);
		glEnd();
		glBegin(GL_QUADS);
		glColor3ub(0.5 * 174, 0.5 * 179, 0.5 * 186);
		glVertex2dC(x + 2.5, y - Height);
		glVertex2dC(x - 2.5, y - Height);
		glVertex2dC(x - 5, y - Height - 40 + 15);
		glVertex2dC(x - 5 + 2.5, y - Height - 40 + 15);
		glEnd();

	}
	glBegin(GL_POLYGON);
	DrawCircleProj(x, y, R, Theta, Rotation, 255, 223, 0);
	glEnd();
}
void Draw_Hit(double x, double y, double R, double Theta, double Rotation) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(0, 0, 255, 70);   //alpha blending
	glBegin(GL_POLYGON);
	for (int i = 0; i < 65; i++) {
		double angle = (double)i*PI / 32;
		double xp = x + cos(angle)*R * cos(Rotation) - sin(angle)*R * cos(Theta)* sin(Rotation);
		double yp = y + sin(angle)*R * cos(Theta) * cos(Rotation) + cos(angle)*R * sin(Rotation);
		glVertex2dC(xp, yp);
	}
	glDisable(GL_BLEND);
	glEnd();
}
//
///* Testing Main Function */
//int main(void) {
//	int keyVal = 0;
//	Drum drum;
//
//	FsOpenWindow(16, 16, 800, 600, 1);
//	player.Start();
//
//	while (keyVal != FSKEY_ESC) {
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		FsPollDevice();
//		drum.setKey(FsInkey());
//		drum.Play();
//		drum.Draw();
//		FsSwapBuffers();
//		FsSleep(25);
//	}
//
//	player.End();
//}
