//
// Created by hp on 3/27/2018.
//

#ifndef UNTITLED1_LINE_H
#define UNTITLED1_LINE_H

#include <windows.h>
#include "Shape.h"
class Line : public Shape{
public:
    int xs, xe, ys, ye;
    COLORREF c;

    Line(){}
    Line(int xs, int xe, int ys, int ye, COLORREF c);
    void drawLineMidpoint(HDC hdc);
    void drawLineCartesian(HDC hdc);
    void drawLineDDA(HDC hdc);
    void draw(HDC hdc);
    void write(ofstream &out);
    void read(ifstream &in);

};


#endif //UNTITLED1_LINE_H
