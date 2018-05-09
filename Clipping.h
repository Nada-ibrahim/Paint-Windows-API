//
// Created by hp on 4/24/2018.
//

#ifndef UNTITLED1_CLIPPING_H
#define UNTITLED1_CLIPPING_H

#include "MyPoint.h"
#include "ShapeBuffer.h"
#include "Poly.h"

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
    void clip(MyPoint d1, MyPoint d2, ShapeBuffer &buffer, HDC hdc);
    pair<outcode , outcode> getOutCode(MyPoint ps, MyPoint pe);

    Poly clipLeft(Poly, HDC hdc);

    Poly clipRight(Poly pin, HDC hdc);

    Poly clipTop(Poly pin, HDC hdc);

    Poly clipBottom(Poly pin, HDC hdc);

    void polygonClip(MyPoint d1, MyPoint d2, ShapeBuffer &buffer, HDC hdc);
};


#endif //UNTITLED1_CLIPPING_H
