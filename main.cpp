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

void Render(void *incoming)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    guitar.Draw();
    bass.Draw();
    drum.Draw();
    keyboard.Draw();
    FsSwapBuffers();
}

int main(void){
    printf("24-780 Engineering Computation\n");
    FsChangeToProgramDir();
    windowW = 800;
    windowH = 600;
    FsOpenWindow(32,32,windowW,windowH,1);
    
    FsRegisterOnPaintCallBack(Render,nullptr);
    bool terminate=false;
    
    player.Start();
    int i=0;
    int iterations=50;
    
    while(terminate!=true)
    {
        auto key=FsInkey();
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
