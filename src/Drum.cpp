#include <math.h>
#include "../include/Drum.h"

const double PI=3.1415926;

const double Height1 = 30;//MOVE INTO the object in the future!!!
const double DrumR1=70;
const double Theta1 = PI/6;
const double Rotation1 = 0;
const double Drum1_X = 100;
const double Drum1_Y = 100;

const double Height2 = 30;
const double DrumR2=50;
const double Theta2 = PI/3;
const double Rotation2 = PI/24;
const double Drum2_X = 200;
const double Drum2_Y = 100;

//YsSoundPlayer player;

double CoordX(double x){
    double Coordx = x;
    return Coordx;
}
double CoordY(double y){
    double Coordy = 600 - y;
    return Coordy;
}
void glVertex2dC(double x, double y){
    glVertex2d(CoordX(x), CoordY(y));
}

void DrawCircleProj(double x, double y, double R, double Theta, double Rotation, int r, int g, int b);
void Draw_Drum_Face(double x, double y, double DrumR, double Theta, double Rotation);
void Draw_Drum_Body(double x, double y, double DrumR, double Height, double Theta, double Rotation);
void Draw_Drum(double x, double y, double DrumR, double Height, double Theta, double Rotation);
void Draw_Hit(double x, double y, double R, double Theta, double Rotation);


Drum::Drum()
{
    key = 0;
    hit_cycle1 = 0;
    hit_cycle2 = 0;
    //init parameters for drawing
    Load();
}

void Drum::Load(){
    
    if(YSOK!=hihat.LoadWav("pearlkit-hihat.wav")){
        printf("Failed to read hihat\n");
    }
    
    if(YSOK!=hitom.LoadWav("pearlkit-hitom1.wav")){
        printf("Failed to read hitom1\n");
    }
    
    if(YSOK!=kick.LoadWav("pearlkit-kick.wav")){
        printf("Failed to read kick\n");
    }
    
    if(YSOK!=lowtom.LoadWav("pearlkit-lowtom1.wav")){
        printf("Failed to read lowtom1\n");
    }
    
    if(YSOK!=ride.LoadWav("pearlkit-ride1.wav")){
        printf("Failed to read ride1\n");
    }
    
    if(YSOK!=ridebell.LoadWav("pearlkit-ridebell.wav")){
        printf("Failed to read ridebell\n");
    }
    
    if(YSOK!=ridecrash.LoadWav("pearlkit-ridecrash.wav")){
        printf("Failed to read ridecrash\n");
    }
    
    if(YSOK!=snare.LoadWav("pearlkit-snare1.wav")){
        printf("Failed to read snare1\n");
    }
    
    if(YSOK!=snareroll.LoadWav("../Drum/pearlkit-snareroll.wav")){
        printf("Failed to read snareroll\n");
    }
    
}

void Drum::setKey(int keyVal){
        key=keyVal;
}

void Drum::Play(){
    switch (key) {
        case FSKEY_Q:
            player.Stop(hihat);
            player.PlayOneShot(hihat);
            break;
        case FSKEY_W:
            player.Stop(ridebell);
            player.PlayOneShot(ridebell);
            break;
        case FSKEY_E:
            player.Stop(hitom);
            player.PlayOneShot(hitom);
            break;
        case FSKEY_A:
            player.Stop(ridecrash);
            player.PlayOneShot(ridecrash);
            break;
        case FSKEY_S:
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
        case FSKEY_X:
            player.Stop(ride);
            player.PlayOneShot(ride);
            break;
        case FSKEY_C:
            player.Stop(snareroll);
            player.PlayOneShot(snareroll);
            break;
    }
    
}

void Drum::Draw(){
    Draw_Drum(Drum1_X, Drum1_Y, DrumR1, Height1, Theta1, Rotation1);
    {
    if(key==FSKEY_Q){
        hit_cycle1 = 1;
    }
    if(hit_cycle1>0){
        if(hit_cycle1>5){
            hit_cycle1 = 0;
        }
        else{
            hit_cycle1 += 1;
            Draw_Hit(Drum1_X, Drum1_Y, DrumR1, Theta1, Rotation1);
        }
    }
    }   //check and draw hit
    Draw_Drum(Drum2_X, Drum2_Y, DrumR2, Height2, Theta2, Rotation2);
    {
        if(key==FSKEY_W){
            hit_cycle2 = 1;
        }
        if(hit_cycle2>0){
            if(hit_cycle2>5){
                hit_cycle2 = 0;
            }
            else{
                hit_cycle2 += 1;
                Draw_Hit(Drum2_X, Drum2_Y, DrumR2, Theta2, Rotation2);
            }
        }
    }   //check and draw hit
    key = 0;    //reset the key because it`s in render, later than Player()
}

void DrawCircleProj(double x, double y, double R, double Theta, double Rotation, int r, int g, int b){
    glColor3ub( r, g, b);
    for(int i=0;i<65;i++){
        double angle=(double)i*PI/32;
        double xp=x + cos(angle)*R * cos(Rotation)-sin(angle)*R * cos(Theta)* sin(Rotation);
        double yp=y + sin(angle)*R * cos(Theta) * cos(Rotation)+cos(angle)*R * sin(Rotation);
        glVertex2dC(xp, yp);
    }
}
void Draw_Drum_Face(double x, double y, double DrumR, double Theta, double Rotation){
    
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
void Draw_Drum_Body(double x, double y, double DrumR, double Height, double Theta, double Rotation){
    //Find the max and min index
    double x_min=0, x_max=0;
    int i_min=0, i_max=0;
    
    for(int i=0;i<65;i++){
        double angle=(double)i*PI/32;
        double xp=cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
        if(xp>x_max){
            x_max = xp;
            i_max = i;
        }
        if(xp<x_min){
            x_min = xp;
            i_min = i;
        }
    }
    //Draw Drum Body
    glColor3ub( 130, 82, 1);
    //Draw UpperLeft Corner
    glBegin(GL_POLYGON);
    {
        double angle=(double)i_min*PI/32;
        double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
        double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation);
        glVertex2dC(xp, yp);
    }
    //Draw the Body upper side
    {
        double angle=(double)i_max*PI/32;
        double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
        double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation);
        glVertex2dC(xp, yp);
    }
    //Draw the Body right side
    {
        double angle=(double)i_max*PI/32;
        double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
        double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - Height;
        glVertex2dC(xp, yp);
    }
    //Draw the Body lower side
    if(i_max>32){
        for(int i=i_max;i>i_min-1;i--){
            double angle=(double)i*PI/32;
            double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
            double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - Height;
            glVertex2dC(xp, yp);
        }
    }
    else if(i_max<32){
        for(int i=i_max;i>0;i--){
            double angle=(double)i*PI/32;
            double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
            double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - Height;
            glVertex2dC(xp, yp);
        }
        for(int i=64;i>i_min-1;i--){
            double angle=(double)i*PI/32;
            double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
            double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - Height;
            glVertex2dC(xp, yp);
        }
    }
    //Draw the left side of the body
    {
        double angle=(double)i_min*PI/32;
        double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
        double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - Height;
        glVertex2dC(xp, yp);
    }
    glEnd();
    
}
void Draw_Drum(double x, double y, double DrumR, double Height, double Theta, double Rotation){
    Draw_Drum_Body(x, y, DrumR, Height, Theta, Rotation);
    Draw_Drum_Face(x, y, DrumR, Theta, Rotation);
}
void Draw_Hit(double x, double y, double R, double Theta, double Rotation){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4ub( 0, 0, 255, 70);   //alpha blending
    glBegin(GL_POLYGON);
    for(int i=0;i<65;i++){
        double angle=(double)i*PI/32;
        double xp=x + cos(angle)*R * cos(Rotation)-sin(angle)*R * cos(Theta)* sin(Rotation);
        double yp=y + sin(angle)*R * cos(Theta) * cos(Rotation)+cos(angle)*R * sin(Rotation);
        glVertex2dC(xp, yp);
    }
    glDisable(GL_BLEND);
    glEnd();
}
