#include <stdio.h>
#include <stdlib.h>
#include "yssimplesound.h"
#include "fssimplewindow.h"
#include <math.h>

class Drum_Claas//:public Instrument
{
private:
    int key;
    const double PI=3.1415926;
    const double Height1 = 50;
    const double DrumR1=50;
    const double Theta1 = PI/3;
    const double Rotation1 = -PI/24;
    const double Drum1_X = 200;
    const double Drum1_Y = 200;
    YsSoundPlayer::SoundData hihat, hihatO, hitom1, hitom2, kick,
    lowtom1, lowtom2, ride1, ride2, ridebell,
    ridecrash, snare1, snare2, snareroll;
    //parameters for drawing
    int x, y, z;
public:
    Drum_Claas();
    void Load();
    void Setkey(int KeyVal);
    void Play(YsSoundPlayer &player);
    void Draw();
    
};
void Draw_Drum(double x, double y, double DrumR, double Height, double Theta, double Rotation);

Drum_Claas::Drum_Claas()
{
    key = 0;
    //init parameters for drawing
    Load();
}

void Drum_Claas::Load(){
    
    if(YSOK!=hihat.LoadWav("../Drum/pearlkit-hihat.wav")){
        printf("Failed to read hihat\n");
    }
    
    if(YSOK!=hihatO.LoadWav("../Drum/pearlkit-hihatO.wav")){
        printf("Failed to read hihat0\n");
    }
    
    if(YSOK!=hitom1.LoadWav("../Drum/pearlkit-hitom1.wav")){
        printf("Failed to read hitom1\n");
    }
    
    if(YSOK!= hitom2.LoadWav("../Drum/pearlkit-hitom2.wav")){
        printf("Failed to read hitom2\n");
    }
    
    if(YSOK!=kick.LoadWav("../Drum/pearlkit-kick.wav")){
        printf("Failed to read kick\n");
    }
    
    if(YSOK!=lowtom1.LoadWav("../Drum/pearlkit-lowtom1.wav")){
        printf("Failed to read lowtom1\n");
    }
    
    if(YSOK!=lowtom2.LoadWav("../Drum/pearlkit-lowtom2.wav")){
        printf("Failed to read lowtom2\n");
    }
    
    if(YSOK!=ride1.LoadWav("../Drum/pearlkit-ride1.wav")){
        printf("Failed to read ride1\n");
    }
    
    if(YSOK!= ride2.LoadWav("../Drum/pearlkit-ride2.wav")){
        printf("Failed to read ride2\n");
    }
    
    if(YSOK!=ridebell.LoadWav("../Drum/pearlkit-ridebell.wav")){
        printf("Failed to read ridebell\n");
    }
    
    if(YSOK!=ridecrash.LoadWav("../Drum/pearlkit-ridecrash.wav")){
        printf("Failed to read ridecrash\n");
    }
    
    if(YSOK!=snare1.LoadWav("../Drum/pearlkit-snare1.wav")){
        printf("Failed to read snare1\n");
    }
    if(YSOK!=snare2.LoadWav("../Drum/pearlkit-snare2.wav")){
        printf("Failed to read snare2\n");
    }
    if(YSOK!=snareroll.LoadWav("../Drum/pearlkit-snareroll.wav")){
        printf("Failed to read snareroll\n");
    }
    
}

void Drum_Claas::Setkey(int keyVal){
    if(keyVal >0 && keyVal<=14)//the range is TBD
    {
        key=keyVal;
    }
}

void Drum_Claas::Play(YsSoundPlayer &player){
    switch (key) {
        case 1:
            player.PlayOneShot(hihat);//the specific realization is TBD
            break;
        case 2:
            player.PlayOneShot(hihatO);
            break;
        case 3:
            player.PlayOneShot(hitom1);
            break;
        case 4:
            player.PlayOneShot(hitom2);
            break;
        case 5:
            player.PlayOneShot(kick);
            break;
        case 6:
            player.PlayOneShot(lowtom1);
            break;
        case 7:
            player.PlayOneShot(lowtom2);
            break;
        case 8:
            player.PlayOneShot(ride1);
            break;
        case 9:
            player.PlayOneShot(ride2);
            break;
        case 10:
            player.PlayOneShot(ridebell);
            break;
        case 11:
            player.PlayOneShot(ridecrash);
            break;
        case 12:
            player.PlayOneShot(snare1);
            break;
        case 13:
            player.PlayOneShot(snare2);
            break;
        case 14:
            player.PlayOneShot(snareroll);
            break;
    }
    
}

void Drum_Claas::Draw(){
    Draw_Drum(Drum1_X, Drum1_Y, DrumR1, Height1, Theta1, Rotation1);
    key = 0;    //reset the key because it`s in render, later than Player()
}

void DrawCircleProj(double x, double y, double R, double Theta, double Rotation, int r, int g, int b){
    glColor3ub( r, g, b);
    for(int i=0;i<65;i++){
        double angle=(double)i*PI/32;
        double xp=x + cos(angle)*R * cos(Rotation)-sin(angle)*R * cos(Theta)* sin(Rotation);
        double yp=y + sin(angle)*R * cos(Theta) * cos(Rotation)+cos(angle)*R * sin(Rotation);
        glVertex2d(xp, yp);
    }
}
void Draw_Drum_Face(double x, double y, double DrumR, double Theta, double Rotation){
    
    double r = DrumR;
    glBegin(GL_POLYGON);
    DrawCircleProj(x, y, r, Theta, Rotation, 0, 0, 0);
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
    //Draw the Body upper side
    glColor3ub( 255, 0, 0);
    if(i_max>32){
        glBegin(GL_POLYGON);
        for(int i=i_min;i<i_max+1;i++){
            double angle=(double)i*PI/32;
            double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
            double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) + 0.5 * Height;
            glVertex2d(xp, yp);
        }
    }
    else if(i_max<32){
        glBegin(GL_POLYGON);
        for(int i=i_min;i<65;i++){
            double angle=(double)i*PI/32;
            double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
            double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) + 0.5 * Height;
            glVertex2d(xp, yp);
        }
        for(int i=0;i<i_max+1;i++){
            double angle=(double)i*PI/32;
            double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
            double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) + 0.5 * Height;
            glVertex2d(xp, yp);
        }
    }
    //Draw the Body right side
    {
        double angle=(double)i_max*PI/32;
        double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
        double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - 0.5 * Height;
        glVertex2d(xp, yp);
        printf("right: %f, %f", xp, yp);
    }
    //Draw the Body lower side
    if(i_max>32){
        for(int i=i_max;i>i_min-1;i--){
            double angle=(double)i*PI/32;
            double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
            double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - 0.5 * Height;
            glVertex2d(xp, yp);
        }
    }
    else if(i_max<32){
        glBegin(GL_POLYGON);
        for(int i=i_max;i>0;i--){
            double angle=(double)i*PI/32;
            double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
            double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - 0.5 * Height;
            glVertex2d(xp, yp);
        }
        for(int i=64;i>i_min-1;i--){
            double angle=(double)i*PI/32;
            double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
            double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - 0.5 * Height;
            glVertex2d(xp, yp);
        }
    }
    //Draw the left side of the body
    {
        double angle=(double)i_min*PI/32;
        double xp=x + cos(angle)*DrumR * cos(Rotation)-sin(angle)*DrumR * cos(Theta)* sin(Rotation);
        double yp=y + sin(angle)*DrumR * cos(Theta) * cos(Rotation)+cos(angle)*DrumR * sin(Rotation) - 0.5 * Height;
        glVertex2d(xp, yp);
        printf("left: %f, %f", xp, yp);
    }
    glEnd();
    
}
void Draw_Drum(double x, double y, double DrumR, double Height, double Theta, double Rotation){
    Draw_Drum_Body(x, y, DrumR, Height, Theta, Rotation);
    Draw_Drum_Face(x, y, DrumR, Theta, Rotation);
}

//int main(void){
//    int keyVal = 0;
//    YsSoundPlayer player;
//    Drum_Claas Drum;
//
//
//    player.Start();
//
//
//    while( keyVal!=FSKEY_ESC ){
//
//        FsPollDevice();
//        keyVal = FsInkey() - FSKEY_0;
//        Drum.Setkey( keyVal );
//        Drum.Play(player);
//        FsSleep(25);
//    }
//
//    player.End();
//}
