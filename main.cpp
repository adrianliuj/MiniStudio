//  project.cpp
//  MiniStudioProject
//
//  Created by Kelly Zhang on 11/5/18.
//  Copyright © 2018 Kelly Zhang. All rights reserved.
//
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define PI 3.14159265
#include <cstdlib>
#include <string>
#include <vector>
#include "include\Bass.h"
#include "include\Keyboard.h"
#include "include\Guitar.h"
#include "include\Drum.h"


YsSoundPlayer player;
int windowW,windowH;
Guitar guitar;
Keyboard keyboard;
Bass bass;
Drum drum;

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
	else if (x > 0 && x < 200 && y > 300 && y < 600) {
		key = FSKEY_Q;
	}
	else if (x > 100 && x < 300 && y > 300 && y < 600) {
		key = FSKEY_S;
	}
	else if (x > 200 && x < 400 && y > 300 && y < 600) {
		key = FSKEY_Z;
	}
	else if (x > 0 && x < 800 && y > 600 && y < 650) {
		key = FSKEY_T;
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

	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(0+5, 600+5);
	glVertex2d(800-5, 600+5);
	glVertex2d(800-5, 650-5);
	glVertex2d(0+5, 650-5);
	glEnd();
}

void DrawStopButton() {
	
	double wid = 100;
	double hei = 40;
	double centerX = 400;
	double centerY = 625;
	/*glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(centerX-wid/2, centerY-hei/2);
	glVertex2d(centerX+wid / 2, centerY-hei / 2);
	glVertex2d(centerX+wid / 2, centerY+hei / 2);
	glVertex2d(centerX-wid / 2, centerY+ hei / 2);
	glEnd();*/

	glColor3ub(0, 0, 0);
	glRasterPos2d(centerX-wid/2+20, centerY+hei/2-10);
	YsGlDrawFontBitmap16x20("STOP");
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
			printf("%d %d %d %d\n", lb, mx, my, key);
		}

        if(FSKEY_ESC==key)
        {
            terminate=true;
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
