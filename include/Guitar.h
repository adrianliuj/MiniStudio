#ifndef GUITAR_H_NOT_INCLUDED
#define GUITAR_H_NOT_INCLUDED

#include "Instrument.h"
class GuitarChordBlock{
public:
    bool isPlaying=false;
    void DrawChordBlock(int chordNum);
    
private:
    double wid=24,hei=140,widActive=26,heiActive=140;
    int colorR=153,colorG=153,colorB=255;
    int colorActiveR=77,colorActiveG=255,colorActiveB=77;
//    int numIter=0;
    int windowW = 400;
    int windowH = 300;
};

class Guitar:public Instrument{
public:
    void Load();
    void Play();
    void Draw();
    void setKey(int keyVal);
    Guitar();
    //    ~Guitar();
    
private:
    void DrawGuitarBackground() const;
    void StopAll();
    GuitarChordBlock blkEm,blkAm,blkF,blkC,blkD,blkG,blkDm;
    YsSoundPlayer::SoundData Em,Am,F,C,D,G,Dm;
    int key;
    int windowW = 400;
    int windowH = 300;
};

#endif /* Guitar_h */
