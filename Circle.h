//
// Created by hp on 3/27/2018.
//

#ifndef UNTITLED1_CIRCLE_H
#define UNTITLED1_CIRCLE_H

#include <windows.h>
#include "Shape.h"
class Circle: public Shape {
    int xc, yc, xr, yr;
    COLORREF c;
public:
    Circle(int xc, int yc, int xr, int yr, COLORREF c);
    void drawCircleMidpoint(HDC hdc);
    void drawCircleCartesian(HDC hdc);
    void drawCirclePolar(HDC hdc);
    void draw8Points(HDC hdc, int x, int y);
    void draw(HDC hdc);
    void write(ofstream& out);
    void read(ifstream &in);

    Circle();
};


#endif //UNTITLED1_CIRCLE_H
