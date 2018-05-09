//
// Created by hp on 4/10/2018.
//

#ifndef UNTITLED1_FILLING_H
#define UNTITLED1_FILLING_H


#include <afxres.h>
#include "Shape.h"
class Filling: public Shape{
    int xc, yc;
    COLORREF backColor, fillColor;
public:
    Filling(int xc, int yc, COLORREF backColor, COLORREF fillColor);
    void fillSeed(HDC hdc);
    void draw(HDC hdc);
    void write(ofstream& out);
    void read(ifstream &in);

    Filling();
};


#endif //UNTITLED1_FILLING_H
