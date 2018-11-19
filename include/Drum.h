#ifndef Drum_h
#define Drum_h

#include "Instrument.h"

extern YsSoundPlayer player;

void DrawCircleProj(double x, double y, double R, double Theta, double Rotation, int r, int g, int b)
void Draw_Drum_Face(double x, double y, double DrumR, double Theta, double Rotation)
void Draw_Drum_Body(double x, double y, double DrumR, double Height, double Theta, double Rotation)
void Draw_Drum(double x, double y, double DrumR, double Height, double Theta, double Rotation)

class Drum_Class//:public Instrument
{
private:
    int key;
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
#endif /* Drum_h */
