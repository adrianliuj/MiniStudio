#include "../include/Guitar.h"

void GuitarChordBlock::DrawChordBlock(int chordNum){
    
    double margin=15;
    double x,y;
    
    
    x=(windowW-85)-(8-chordNum)*(margin+wid)+400;
    y=windowH/2;
    
    if (isPlaying==false){
        // Draw shape with colorR, colorG and colorB & dimensions wid, hei.
        glBegin(GL_QUADS);
        glColor3ub(colorR,colorG,colorB);
        glVertex2d(x-wid/2,y-hei/2);
        glColor3ub(colorR,colorG,colorB);
        glVertex2d(x+wid/2,y-hei/2);
        glColor3ub(255,255,255);
        glVertex2d(x+wid/2,y+hei/2);
        glColor3ub(255,255,255);
        glVertex2d(x-wid/2,y+hei/2);
        glEnd();
    }
    else{
        // Draw shape with colorActiveR, colorActiveG and colorActiveB & dimensions widActive, heiActive.
        glBegin(GL_QUADS);
        glColor3ub(colorActiveR,colorActiveG,colorActiveB);
        glVertex2d(x-widActive/2,y-heiActive/2);
        glColor3ub(colorActiveR,colorActiveG,colorActiveB);
        glVertex2d(x+widActive/2,y-heiActive/2);
        glColor3ub(255,255,255);
        glVertex2d(x+widActive/2,y+heiActive/2);
        glColor3ub(255,255,255);
        glVertex2d(x-widActive/2,y+heiActive/2);
        glEnd();
    }
  
    // label chord names
    glColor3f(0,0,0);
    switch (chordNum) {
        case 5:
            glRasterPos2d(x-9,y-40);
            YsGlDrawFontBitmap10x14("Em");
            glColor3ub(255,0,0);
            glRasterPos2d(x-5,y+60);
            YsGlDrawFontBitmap8x12("F");
            break;
        case 1:
            glRasterPos2d(x-9,y-40);
            YsGlDrawFontBitmap10x14("Am");
            glColor3ub(255,0,0);
            glRasterPos2d(x-5,y+60);
            YsGlDrawFontBitmap8x12("G");
            break;
        case 6:
            glRasterPos2d(x-5,y-40);
            YsGlDrawFontBitmap10x14("F");
            glColor3ub(255,0,0);
            glRasterPos2d(x-5,y+60);
            YsGlDrawFontBitmap8x12("H");
            break;
        case 2:
            glRasterPos2d(x-5,y-40);
            YsGlDrawFontBitmap10x14("C");
            glColor3ub(255,0,0);
            glRasterPos2d(x-5,y+60);
            YsGlDrawFontBitmap8x12("V");
            break;
        case 3:
            glRasterPos2d(x-5,y-40);
            YsGlDrawFontBitmap10x14("D");
            glColor3ub(255,0,0);
            glRasterPos2d(x-5,y+60);
            YsGlDrawFontBitmap8x12("B");
            break;
        case 7:
            glRasterPos2d(x-5,y-40);
            YsGlDrawFontBitmap10x14("G");
            glColor3ub(255,0,0);
            glRasterPos2d(x-5,y+60);
            YsGlDrawFontBitmap8x12("N");
            break;
        case 4:
            glRasterPos2d(x-9,y-40);
            YsGlDrawFontBitmap10x14("Dm");
            glColor3ub(255,0,0);
            glRasterPos2d(x-5,y+60);
            YsGlDrawFontBitmap8x12("M");
            break;
    }
}

void Guitar::Load(){
}

Guitar::Guitar(){
    Load();
}

void Guitar::setKey(int keyVal){
    key=keyVal;
}

void Guitar::StopAll(){
    player.Stop(Em);
    player.Stop(Am);
    player.Stop(F);
    player.Stop(C);
    player.Stop(D);
    player.Stop(G);
    player.Stop(Dm);
    
    blkEm.isPlaying=false;
    blkAm.isPlaying=false;
    blkF.isPlaying=false;
    blkC.isPlaying=false;
    blkD.isPlaying=false;
    blkG.isPlaying=false;
    blkDm.isPlaying=false;
}

void Guitar::Play(){
    auto isActiveEm=player.IsPlaying(Em);
    auto isActiveAm=player.IsPlaying(Am);
    auto isActiveF=player.IsPlaying(F);
    auto isActiveC=player.IsPlaying(C);
    auto isActiveD=player.IsPlaying(D);
    auto isActiveG=player.IsPlaying(G);
    auto isActiveDm=player.IsPlaying(Dm);

    if(YSTRUE!=isActiveEm){
        blkEm.isPlaying=false;
        if(YSTRUE!=isActiveAm){
            blkAm.isPlaying=false;
            if(YSTRUE!=isActiveF){
                blkF.isPlaying=false;
                if(YSTRUE!=isActiveC){
                    blkC.isPlaying=false;
                    if(YSTRUE!=isActiveD){
                        blkD.isPlaying=false;
                        if(YSTRUE!=isActiveG){
                            blkG.isPlaying=false;
                            if(YSTRUE!=isActiveDm){
                                blkDm.isPlaying=false;
                            }
                        }
                    }
                }
            }
        }
    }

    switch (key) {
        case FSKEY_F:
            StopAll();
            blkEm.isPlaying=true;
            Em.LoadWav("../../MiniStudio/resource/guitar/Em.wav");
            player.PlayOneShot(Em);
            break;
        case FSKEY_G:
            StopAll();
            blkAm.isPlaying=true;
            Am.LoadWav("../../MiniStudio/resource/guitar/Am.wav");
            player.PlayOneShot(Am);
            break;
        case FSKEY_H:
            StopAll();
            blkF.isPlaying=true;
            F.LoadWav("../../MiniStudio/resource/guitar/F.wav");
            player.PlayOneShot(F);
            break;
        case FSKEY_V:
            StopAll();
            blkC.isPlaying=true;
            C.LoadWav("../../MiniStudio/resource/guitar/C.wav");
            player.PlayOneShot(C);
            break;
        case FSKEY_B:
            StopAll();
            blkD.isPlaying=true;
            D.LoadWav("../../MiniStudio/resource/guitar/D.wav");
            player.PlayOneShot(D);
            break;
        case FSKEY_N:
            StopAll();
            blkG.isPlaying=true;
            G.LoadWav("../../MiniStudio/resource/guitar/G.wav");
            player.PlayOneShot(G);
            break;
        case FSKEY_M:
            StopAll();
            blkDm.isPlaying=true;
            Dm.LoadWav("../../MiniStudio/resource/guitar/Dm.wav");
            player.PlayOneShot(Dm);
            break;
        case FSKEY_T:
            StopAll();
            break;
    }
}

void Guitar::DrawGuitarBackground() const{
    // Draw guitar background elements
    // draw background color
//    glColor3ub(179,89,0);
    glLineWidth(1.0f);
    glColor3ub(230,153,0);
    glBegin(GL_QUADS);
    glVertex2i(400,0);
    glVertex2i(400+windowW,0);
    glVertex2i(400+windowW,windowH);
    glVertex2i(400,windowH);
    glEnd();
    
    // draw guitar body
    int cx = windowW/2+50+400;
    int cy = windowH/2;
    int num_segments=500;
    glShadeModel(GL_SMOOTH);
    
    int r0_1=220;
    glBegin(GL_TRIANGLE_FAN);
//    glColor3ub(255,230,102);
//    glColor3ub(230,153,0);
    glColor3ub(255,179,25);
    glVertex2f(cx, cy);
    for(int i=0;i<num_segments;i++)
    {
        double theta=2.0*3.14159265*double(i)/double(num_segments);
        double x=r0_1*cos(theta);
        double y=r0_1*sin(theta);
//        glColor3ub(230,153,0);
        glColor3ub(179,59,0);
        glVertex2f(x+cx, y+cy);
    }
    glEnd();
    
    cx = windowW/2+50+400;
    cy = windowH/2;
    
    // draw center hole
    int r1=95;
    glColor3ub(0,0,0);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0;i<num_segments;i++)
    {
        double theta=2.0*3.14159265*double(i)/double(num_segments);
        double x=r1*cos(theta);
        double y=r1*sin(theta);
        glVertex2f(x+cx, y+cy);
    }
    glEnd();
    
    // -------------------
    int r2=100;
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<num_segments;i++)
    {
        double theta=2.0*3.14159265*double(i)/double(num_segments);
        double x=r2*cos(theta);
        double y=r2*sin(theta);
        glVertex2f(x+cx, y+cy);
    }
    glEnd();
    
    int r3=110;
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<num_segments;i++)
    {
        double theta=2.0*3.14159265*double(i)/double(num_segments);
        double x=r3*cos(theta);
        double y=r3*sin(theta);
        glVertex2f(x+cx, y+cy);
    }
    glEnd();
    
    // ------------------------------
    int r4=55;
    double length=5;
    glBegin(GL_LINES);
    for(int i=0;i<100;i++)
    {
        double theta=2.0*3.14159265*double(i)/double(100);
        double x=r4*cos(theta);
        double y=r4*sin(theta);
        
        glColor3ub(0,0,0);
        glVertex2f(x+cx+r4*cos(theta), y+cy+r4*sin(theta));
        glVertex2f(x+cx+(r4+length)*cos(theta), y+cy+(r4+length)*sin(theta));
    }
    glEnd();
    
    // -------------------------------
    int r5=115;
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<num_segments;i++)
    {
        double theta=2.0*3.14159265*double(i)/double(num_segments);
        double x=r5*cos(theta);
        double y=r5*sin(theta);
        glVertex2f(x+cx, y+cy);
    }
    glEnd();
    
    // draw fretboard
    double fretX = windowW/2+400;
    double fretY = windowH/2;
    double fretW = windowW;
    double fretH = 120; // adjust fretboard half width
    double fretY1 = fretY+fretH/4;
    double fretY2 = fretY-fretH/4;

    glBegin(GL_QUADS);
    glColor3ub(102,34,0);
    glVertex2d(fretX-fretW/2,fretY1-fretH/4);
    glColor3ub(102,34,0);
    glVertex2d(fretX+fretW/2,fretY1-fretH/4);
    glColor3ub(0,0,0);
    glVertex2d(fretX+fretW/2,fretY1+fretH/4);
    glColor3ub(0,0,0);
    glVertex2d(fretX-fretW/2,fretY1+fretH/4);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(fretX-fretW/2,fretY2-fretH/4);
    glColor3ub(0,0,0);
    glVertex2d(fretX+fretW/2,fretY2-fretH/4);
    glColor3ub(102,34,0);
    glVertex2d(fretX+fretW/2,fretY2+fretH/4);
    glColor3ub(102,34,0);
    glVertex2d(fretX-fretW/2,fretY2+fretH/4);
    glEnd();
    
    // draw six uitar strings
    double stringX=windowW/2+400;
    double stringSpc=18;
    double stringY = windowH/2+45;
    double stringW = windowW;
    double stringH=6;
    
    for(int i=0;i<6;i++){
        double stringY1 = stringY+stringH/4;
        double stringY2 = stringY-stringH/4;
        
        glBegin(GL_QUADS);
        glColor3ub(255,255,255);
        glVertex2d(stringX-stringW/2,stringY1-i*stringSpc-stringH/4);
        glColor3ub(255,255,255);
        glVertex2d(stringX+stringW/2,stringY1-i*stringSpc-stringH/4);
        glColor3ub(0,0,0);
        glVertex2d(stringX+stringW/2,stringY1-i*stringSpc+stringH/4);
        glColor3ub(0,0,0);
        glVertex2d(stringX-stringW/2,stringY1-i*stringSpc+stringH/4);
        glEnd();
        
        glBegin(GL_QUADS);
        glColor3ub(0,0,0);
        glVertex2d(stringX-stringW/2,stringY2-i*stringSpc-stringH/4);
        glColor3ub(0,0,0);
        glVertex2d(stringX+stringW/2,stringY2-i*stringSpc-stringH/4);
        glColor3ub(255,255,255);
        glVertex2d(stringX+stringW/2,stringY2-i*stringSpc+stringH/4);
        glColor3ub(255,255,255);
        glVertex2d(stringX-stringW/2,stringY2-i*stringSpc+stringH/4);
        glEnd();
    }

    // COVER UP -- TEMPORARY FIX
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
    glVertex2i(400,300);
    glVertex2i(400+windowW,300);
    glVertex2i(400+windowW,windowH+300);
    glVertex2i(400,windowH+300);
    glEnd();
}

void Guitar::Draw(){
    DrawGuitarBackground();
    blkAm.DrawChordBlock(1);
    blkC.DrawChordBlock(2);
    blkD.DrawChordBlock(3);
    blkDm.DrawChordBlock(4);
    blkEm.DrawChordBlock(5);
    blkF.DrawChordBlock(6);
    blkG.DrawChordBlock(7);
}

