//
// Created by hp on 3/27/2018.
//

#include "Circle.h"

#include <math.h>
void Circle::drawCircleMidpoint(HDC hdc, COLORREF c, int xc, int yc, int xr, int yr) {
    int r = (int)sqrt(pow(xr-xc, 2) + pow(yr-yc, 2));
    int y = r;
    int x = 0;
    draw8Points(hdc, x,y, xc, yc, c);
    int d = 1-r;
    int ch1;
    int ch2;
    while(x < y){
        ch1 = 2*x + 3;
        ch2 = 2*(x-y) + 5;
        if(d < 0){
            d += ch1;
        }else{
            d += ch2;
            y--;
        }
        x++;
        draw8Points(hdc, x, y, xc, yc, c);
    }
}

void Circle::draw8Points(HDC hdc, int x, int y, int xc, int yc, COLORREF c) {
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc + y, yc + x, c);
    SetPixel(hdc, xc + y, yc - x, c);
    SetPixel(hdc, xc - y, yc - x, c);
    SetPixel(hdc, xc - y, yc + x, c);
}

void Circle::drawCircleCartesian(HDC hdc, COLORREF c, int xc, int yc, int xr, int yr) {
    int r = (int)sqrt(pow(xr-xc, 2) + pow(yr-yc, 2));
    int y = r;
    int x = 0;
    draw8Points(hdc, x,y, xc, yc, c);
    while(x < y){
        x++;
        y = (int)round(sqrt(pow(r,2) - pow(x,2)));
        draw8Points(hdc, x, y, xc, yc, c);
    }
}
