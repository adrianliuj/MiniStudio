#ifndef INSTRUMENT_H_NOT_INCLUDED
#define INSTRUMENT_H_NOT_INCLUDED
#include <vector>
#include <string>
#include <iostream>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspng.h"
extern YsSoundPlayer player;

using namespace std;
class Instrument {
public:
    virtual void Load() = 0;
    virtual void Play() = 0;
    virtual void Draw() = 0;
    virtual void setKey(int key) = 0;
protected:
    int key;
};
#endif