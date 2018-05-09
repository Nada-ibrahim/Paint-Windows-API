//
// Created by hp on 3/27/2018.
//

#include "Circle.h"

#include <math.h>
void Circle::drawCircleMidpoint(HDC hdc) {
    int r = (int)sqrt(pow(xr-xc, 2) + pow(yr-yc, 2));
    int y = r;
    int x = 0;
    draw8Points(hdc, x,y);
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
        draw8Points(hdc, x, y);
    }
}

void Circle::draw8Points(HDC hdc, int x, int y) {
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc + y, yc + x, c);
    SetPixel(hdc, xc + y, yc - x, c);
    SetPixel(hdc, xc - y, yc - x, c);
    SetPixel(hdc, xc - y, yc + x, c);
}

void Circle::drawCircleCartesian(HDC hdc) {
    int r = (int)sqrt(pow(xr-xc, 2) + pow(yr-yc, 2));
    int y = r;
    int x = 0;
    draw8Points(hdc, x,y);
    while(x < y){
        x++;
        y = (int)round(sqrt(pow(r,2) - pow(x,2)));
        draw8Points(hdc, x, y);
    }
}

void Circle::drawCirclePolar(HDC hdc) {
    double r = sqrt(pow(xr-xc, 2) + pow(yr-yc, 2));
    double x = r;
    double y = 0;
    draw8Points(hdc, x, y);
    double dtheta = 1/r;
    double cosine = cos(dtheta);
    double sine = sin(dtheta);

    while(x > y){
        double x1 = x*cosine - y*sine;
        y = x*sine + y*cosine;
        x = x1;
        draw8Points(hdc, round(x), round(y));
    }

}

Circle::Circle(int xc, int yc, int xr, int yr, COLORREF c):xc(xc), yc(yc), xr(xr), yr(yr), c(c) {}

void Circle::draw(HDC hdc) {
    drawCircleMidpoint(hdc);

}

void Circle::write(ofstream &out) {
    out.write((char*)& xc, sizeof(xc));
    out.write((char*) &yc, sizeof(yc));
    out.write((char*) &xr, sizeof(xr));
    out.write((char*) &yr, sizeof(yr));
    out.write((char*) &c, sizeof(c));
}

void Circle::read(ifstream &in) {
    in.read((char*)& xc, sizeof(xc));
    in.read((char*) &yc, sizeof(yc));
    in.read((char*) &xr, sizeof(xr));
    in.read((char*) &yr, sizeof(yr));
    in.read((char*) &c, sizeof(c));
}

Circle::Circle() {

}
