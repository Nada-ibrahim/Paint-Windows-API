//
// Created by hp on 3/27/2018.
//

#ifndef UNTITLED1_LINE_H
#define UNTITLED1_LINE_H

#include <windows.h>
class Line {
public:
    void drawLineMidpoint(HDC hdc, COLORREF c, int xs, int xe, int ys, int ye);
    void drawLineCartesian(HDC hdc, COLORREF c, int xs, int xe, int ys, int ye);
    void drawLineDDA(HDC hdc, COLORREF c, int xs, int xe, int ys, int ye);
};


#endif //UNTITLED1_LINE_H
