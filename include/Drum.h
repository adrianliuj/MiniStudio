#ifndef DRUM_H_NOT_INCLUDED
#define DRUM_H_NOT_INCLUDED

#include "Instrument.h"

double CoordX(double x){
    double Coordx = x;
    return Coordx;
}
double CoordY(double y){
    double Coordy = 300 - y;
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

class Drum_Class:public Instrument
{
private:
    int key_;
    int hit_cycle1;
    int hit_cycle2;
    YsSoundPlayer::SoundData hihat, hitom, kick,
    lowtom, ride, ridebell,
    ridecrash, snare, snareroll;
    //parameters for drawing
//    int x, y, z;
public:
    Drum_Class();
    void load();
    void setKey(int key);
    void play();
    void draw();
    
};
#endif /* Drum_h */
