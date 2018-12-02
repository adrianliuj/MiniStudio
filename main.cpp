#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "include\Bass.h"
#include "include\Keyboard.h"
#include "include\Guitar.h"
#include "include\Drum.h"
#include <fstream>


YsSoundPlayer player;

int windowW,windowH;
Guitar guitar;
Keyboard keyboard;
Bass bass;
Drum drum;
double PI = 3.14159265;
YsRawPngDecoder wood;
bool record = 0;
bool playback = 0;
int True_Bass = 0;
int True_Drum = 0;
GLuint textID;
GLuint textID_B;
// ------------------------------------------------------------------


void mouseInputConv(int x, int y, int &key) {
	// Bass section
	if (x > 420 && x < 450 && y > 300 && y < 600) {
		key = FSKEY_U;
	}
	else if (x > 476 && x < 506 && y > 300 && y < 600) {
		key = FSKEY_I;
	}
	else if (x > 531 && x < 561 && y > 300 && y < 600) {
		key = FSKEY_O;
	}
	else if (x > 585 && x < 615 && y > 300 && y < 600) {
		key = FSKEY_P;
	}
	else if (x > 641 && x < 671 && y > 300 && y < 600) {
		key = FSKEY_J;
	}
	else if (x > 696 && x < 726 && y > 300 && y < 600) {
		key = FSKEY_K;
	}
	else if (x > 751 && x < 781 && y > 300 && y < 600) {
		key = FSKEY_L;
	}
	// Keyboard section
	else if (x > 0 + 23 && x < 36 + 23 && y > 110 && y < 300) {
		key = FSKEY_1;
	}
	else if (x > 36 + 23 && x < 72 + 23 && y > 110 && y < 300) {
		key = FSKEY_2;
	}
	else if (x > 72 + 23 && x < 108 + 23 && y > 110 && y < 300) {
		key = FSKEY_3;
	}
	else if (x > 108 + 23 && x < 144 + 23 && y > 110 && y < 300) {
		key = FSKEY_4;
	}
	else if (x > 144 + 23 && x < 180 + 23 && y > 110 && y < 300) {
		key = FSKEY_5;
	}
	else if (x > 180 + 23 && x < 216 + 23 && y > 110 && y < 300) {
		key = FSKEY_6;
	}
	else if (x > 216 + 23 && x < 252 + 23 && y > 110 && y < 300) {
		key = FSKEY_7;
	}
	else if (x > 252 + 23 && x < 288 + 23 && y > 110 && y < 300) {
		key = FSKEY_8;
	}
	else if (x > 288 + 23 && x < 324 + 23 && y > 110 && y < 300) {
		key = FSKEY_9;
	}
	else if (x > 324 + 23 && x < 360 + 23 && y > 110 && y < 300) {
		key = FSKEY_0;
	}
	// Guitar section
	if (x > 420 && x < 460 && y > 0 && y < 300) {
		key = FSKEY_G;
	}
	else if (x > 460 && x < 500 && y > 0 && y < 300) {
		key = FSKEY_V;
	}
	else if (x > 500 && x < 540 && y > 0 && y < 300) {
		key = FSKEY_B;
	}
	else if (x > 540 && x < 580 && y > 0 && y < 300) {
		key = FSKEY_M;
	}
	else if (x > 580 && x < 620 && y > 0 && y < 300) {
		key = FSKEY_F;
	}
	else if (x > 620 && x < 660 && y > 0 && y < 300) {
		key = FSKEY_H;
	}
	else if (x > 660 && x < 700 && y > 0 && y < 300) {
		key = FSKEY_N;
	}
	// Drum section (WIP)
	else if (x > 0 && x < 150 && y > 300 && y < 600) {
		key = FSKEY_S;
	}
	else if (x > 150 && x < 250 && y > 300 && y < 600) {
		key = FSKEY_X;
	}
	else if (x > 250 && x < 400 && y > 300 && y < 600) {
		key = FSKEY_Q;
	}
	// Tool pannel
	else if (x > 0 && x < 200 && y > 600 && y < 650) {
		key = FSKEY_ESC;
	}
	else if (x > 200 && x < 400 && y > 600 && y < 650) {
		key = FSKEY_T;
	}
	else if (x > 400 && x < 600 && y > 600 && y < 650) {
		key = FSKEY_SPACE;
	}
	else if (x > 600 && x < 800 && y > 600 && y < 650) {
		key = FSKEY_ALT;
	}
}

void DrawToolBar() {
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(0,600);
	glVertex2d(800,600);
	glVertex2d(800,650);
	glVertex2d(0,650);
	glEnd();
	
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(224, 224, 224);
	glVertex2d(0+5, 600+5);
	glColor3ub(224, 224, 224);
	glVertex2d(200-5, 600+5);
	glColor3ub(96, 96, 96);
	glVertex2d(200-5, 650-5);
	glColor3ub(96, 96, 96);
	glVertex2d(0+5, 650-5);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(224, 224, 224);
	glVertex2d(200 + 5, 600 + 5);
	glColor3ub(224, 224, 224);
	glVertex2d(400 - 5, 600 + 5);
	glColor3ub(96, 96, 96);
	glVertex2d(400 - 5, 650 - 5);
	glColor3ub(96, 96, 96);
	glVertex2d(200 + 5, 650 - 5);
	glEnd();

	int R1, G1, B1, R2, G2, B2;
	if (record) {
		R1 = 255, G1 = 153, B1 = 153;
		R2 = 204, G2 = 0, B2 = 0;
	}
	else {
		R1 = 224, G1 = 224, B1 = 224;
		R2 = 96, G2 = 96, B2 = 96;
	}
	int R3, G3, B3, R4, G4, B4;
	if (playback) {
		R3 = 153, G3 = 255, B3 = 204;
		R4 = 0, G4 = 204, B4 = 102;
	}
	else {
		R3 = 224, G3 = 224, B3 = 224;
		R4 = 96, G4 = 96, B4 = 96;
	}
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(R1, G1, B1);
	glVertex2d(400 + 5, 600 + 5);
	glColor3ub(R1, G1, B1);
	glVertex2d(600 - 5, 600 + 5);
	glColor3ub(R2, G2, B2);
	glVertex2d(600 - 5, 650 - 5);
	glColor3ub(R2, G2, B2);
	glVertex2d(400 + 5, 650 - 5);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(R3, G3, B3);
	glVertex2d(600 + 5, 600 + 5);
	glColor3ub(R3, G3, B3);
	glVertex2d(800 - 5, 600 + 5);
	glColor3ub(R4, G4, B4);
	glVertex2d(800 - 5, 650 - 5);
	glColor3ub(R4, G4, B4);
	glVertex2d(600 + 5, 650 - 5);
	glEnd();
}

void DrawStopButton() {

	glColor3ub(0, 0, 0);
	glRasterPos2d(70, 635);
	YsGlDrawFontBitmap16x20("CLOSE");
	glRasterPos2d(265, 635);
	YsGlDrawFontBitmap16x20("STOP");
	glRasterPos2d(450, 635);
	YsGlDrawFontBitmap16x20("RECORD");
	glRasterPos2d(640, 635);
	YsGlDrawFontBitmap16x20("PLAYBACK");
}

void Render(void *incoming)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    guitar.Draw();
    bass.Draw();
    drum.Draw();
    keyboard.Draw();

	DrawToolBar();
	DrawStopButton();

	FsSwapBuffers();

}

int main(void){

	double dt = 0.0;

	int playKey;
	unsigned long playTime;
	ofstream myfile;
	ifstream readfile;
	string line;
	{
		wood.Decode("../../MiniStudio/resource/img/bass1.png");
		wood.Flip();
		if (wood.wid == 0) {
			printf("Load unsuccessful.\n");
		}
		else {
			printf("wood.png loaded, width is %d, height is %d\n", wood.wid, wood.hei);
		}
	}

    printf("24-780 Engineering Computation\n");
    FsChangeToProgramDir();
    windowW = 800;
    windowH = 650;
    FsOpenWindow(32,32,windowW,windowH,1);
    
    FsRegisterOnPaintCallBack(Render,nullptr);
    bool terminate=false;
    
    player.Start();
    int i=0;
    int iterations=50;
    
    while(terminate!=true)
    {
        auto key=FsInkey();

		int lb, mb, rb, mx, my;
		FsGetMouseEvent(lb, mb, rb, mx, my);
		if (lb == 1) {
			mouseInputConv(mx, my, key);
		}

        if(FSKEY_ESC==key)
        {
            terminate=true;
        }
		else if (FSKEY_SPACE == key && !playback)
		{
			record = !record;
			if (record) {
				myfile.open("recording.txt");
				printf("File opened to record");
				dt = 0.0;
				FsPassedTime();
			}
			else {
				myfile.close();
				printf("File closed\n");
			}
		}
		else if (FSKEY_ALT == key && !record)
		{
			playback = !playback;
			if (playback) {
				readfile.open("recording.txt");
				if (readfile.is_open())
				{
					if (readfile.good())
					{
						getline(readfile, line, '\t');
						if (line != "\0") { playKey = stoi(line); }
						getline(readfile, line, '\t');
						if (line != "\0") { playTime = stoi(line); }
						dt = 0.0;
						FsPassedTime();
					}
					else {
						readfile.close();
						cout << "File closed" << endl;
						playback = false;
					}
				}
				else
				{
					playback = false;
					cout << "Unable to open file" << endl;
				}
			}
			else {
				if (readfile.is_open()) readfile.close();
			}
		}

		if (NULL != key && record) {
			dt += FsPassedTime();
			myfile << key << "\t" << dt << "\t";
		}

		if (playback) {
			if (readfile.good())
			{
				dt += FsPassedTime();
				if (dt > playTime && key == NULL) {
					key = playKey;
					getline(readfile, line, '\t');
					if (line != "\0") { playKey = stoi(line); }
					getline(readfile, line, '\t');
					if (line != "\0") { playTime = stoi(line); }
				}
			}
			else {
				readfile.close();
				playback = false;
				cout << "File closed" << endl;
			}
		}

        guitar.setKey(key);
        guitar.Play();
        
        bass.setKey(key);
        bass.Play();
        
        drum.setKey(key);
        drum.Play();

        if (key >= FSKEY_0 && key <= FSKEY_9) {
            keyboard.setKey(key);
            keyboard.Play();
            i = 0;
        }
        else if (i >= iterations) {
            keyboard.setKey(key);
        }
        else {
            keyboard.setAlpha(1. - float(i) / float(iterations));
        }
        ++i;
        
        
        FsPollDevice();
        FsPushOnPaintEvent();
        FsSleep(1);
    }
    return 0;
}