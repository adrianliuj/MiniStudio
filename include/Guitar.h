//#ifndef Guitar_h
//#define Guitar_h
//
//
//#endif /* Guitar_h */

extern YsSoundPlayer player;
extern int windowW;
extern int windowH;

class GuitarChordBlock{
public:
    bool isPlaying=false;
    void DrawChordBlock(int chordNum);
    
private:
    double wid=24,hei=140,widActive=26,heiActive=140;
    int colorR=153,colorG=153,colorB=255;
    int colorActiveR=77,colorActiveG=255,colorActiveB=77;
    int key;
//    int numIter=0;
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
};
