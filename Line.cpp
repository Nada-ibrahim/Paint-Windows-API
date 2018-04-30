//
// Created by hp on 3/27/2018.
//

#include "Line.h"
#include <algorithm>
using std::swap;

void Line::drawLineMidpoint(HDC hdc, COLORREF c, int xs, int xe, int ys, int ye) {
    int counter = 1;
    int dx = xe - xs;
    int dy = ye - ys;
    if (abs(dy) > abs(dx)) {
        if (ye < ys) {
            swap(xs, xe);
            swap(ys, ye);
            dx = -dx;
            dy = -dy;
        }
        if(dx < 0){
            dx = -dx;
            counter = -1;
        }

        int x = xs;
        int y = ys;
        SetPixel(hdc, x, y, c);
        int d = dy - 2 * dx;
        int ch1 = -2 * dx;
        int ch2 = 2 * (dy - dx);
        while (y <= ye) {
            if (d > 0) {
                d = d + ch1;
            } else {
                d = d + ch2;
                x = x + counter;
            }
            y = y + 1;
            SetPixel(hdc, x, y, c);
        }
    } else {
        if (xe < xs) {
            swap(xs, xe);
            swap(ys, ye);
            dx = -dx;
            dy = -dy;
        }
        if(dy < 0){
            dy = -dy;
            counter = -1;
        }
        int x = xs;
        int y = ys;
        SetPixel(hdc, x, y, c);
        int d = dx - 2 * dy;
        int ch1 = -2 * dy;
        int ch2 = 2 * (dx - dy);
        while (x <= xe) {
            if (d > 0) {
                d = d + ch1;
            } else {
                d = d + ch2;
                y = y + counter;
            }
            x = x + 1;
            SetPixel(hdc, x, y, c);
        }
    }

}

void Line::drawLineCartesian(HDC hdc, COLORREF c, int xs, int xe, int ys, int ye) {
    int dy = ye - ys;
    int dx = xe - xs;
    if(dy == 0 && dx == 0){
        SetPixel(hdc, xs, ys, c);
    }
    else if(abs(dy) < abs(dx)){
        if(xe < xs) {
            swap(xs, xe);
            swap(ys, ye);
            dx = -dx;
            dy = -dy;
        }
        double m = dy/(double)dx;
        int y;
        for (int x = xs; x < xe; ++x) {
            y = (int)round(ys + (x - xs)*m);
            SetPixel(hdc, x,y, c);
        }
    }else{
        if(ye < ys) {
            swap(xs, xe);
            swap(ys, ye);
            dx = -dx;
            dy = -dy;
        }
        double m = dx/(double)dy;
        int x;
        for (int y = ys; y < ye; ++y) {
            x = (int)round(xs + (y - ys)*m);
            SetPixel(hdc, x,y, c);
        }

    }
}

void Line::drawLineDDA(HDC hdc, COLORREF c, int xs, int xe, int ys, int ye) {
    int dx = xe - xs;
    int dy = ye - ys;
    if(xe == xs && ye == ys){
        SetPixel(hdc, xs, ys, c);
    }

    if(abs(dy) > abs(dx)){
        if(ye < ys){
            swap(xs, xe);
            swap(ys, ye);
        }
        float x = xs;
        int y = ys;
        float m = dx/(float)dy;
        while(y < ye) {
            SetPixel(hdc, (int)round(x), y, c);
            y = y + 1;
            x = x + m;
        }
    }else{
        if(xe < xs){
            swap(xs, xe);
            swap(ys, ye);
        }
        int x = xs;
        float y = ys;
        float m = dy/(float)dx;
        while(x < xe) {
            SetPixel(hdc, x, (int)round(y), c);
            x = x + 1;
            y = y + m;
        }
    }
}
