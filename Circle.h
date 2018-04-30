//
// Created by hp on 3/27/2018.
//

#ifndef UNTITLED1_CIRCLE_H
#define UNTITLED1_CIRCLE_H

#include <windows.h>

class Circle {
public:
    void drawCircleMidpoint(HDC hdc, COLORREF c, int xc, int yc, int xr, int yr);
    void drawCircleCartesian(HDC hdc, COLORREF c, int xc, int yc, int xr, int yr);
    void draw8Points(HDC hdc , int x, int y, int xc, int yc, COLORREF c);
};


#endif //UNTITLED1_CIRCLE_H
