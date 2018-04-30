//
// Created by hp on 4/24/2018.
//

#ifndef UNTITLED1_CLIPPING_H
#define UNTITLED1_CLIPPING_H

#include "MyPoint.h"
#include "EndpointsBuffer.h"

union outcode{
    unsigned all:4;
    struct {
        unsigned top:1;
        unsigned bottom:1;
        unsigned left:1;
        unsigned right:1;
    };
    outcode(){all = 0;}
};
class Clipping {
public:
    int xl;
    int xr;
    int yt;
    int yb;
    void clip(MyPoint d1, MyPoint d2, EndpointsBuffer &lines, HDC hdc, COLORREF c);
    pair<outcode , outcode> getOutCode(MyPoint ps, MyPoint pe);
};


#endif //UNTITLED1_CLIPPING_H
