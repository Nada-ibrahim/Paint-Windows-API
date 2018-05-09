//
// Created by hp on 5/7/2018.
//

#include "BezierCurve.h"

void BezierCurve::write(ofstream &out) {
    for(int i = 0; i < 4; ++i){
        int x = points[i].x;
        int y = points[i].y;
        out.write((char*)& x, sizeof(int));
        out.write((char*)& y, sizeof(int));
    }
    out.write((char*) &c, sizeof(c));
}

void BezierCurve::read(ifstream &in) {
    for(int i = 0; i < 4; ++i){
        int x;
        int y;
        in.read((char*)& x, sizeof(int));
        in.read((char*)& y, sizeof(int));
        addPoint(x,y);
    }
    in.read((char*) &c, sizeof(c));
}

void BezierCurve::draw(HDC hdc) {
    bezierCurve(hdc);
}

void BezierCurve::bezierCurve(HDC hdc) {
    int a0 = points[0].x;
    int a1 = 3*(points[1].x - points[0].x);
    int a2 = 3*points[0].x - 6*points[1].x + 3*points[2].x;
    int a3 = -1*points[0].x + 3*points[1].x -3*points[2].x+points[3].x;
    int b0 = points[0].y;
    int b1 = 3*(points[1].y - points[0].y);
    int b2 = 3*points[0].y - 6*points[1].y + 3*points[2].y;
    int b3 = -1*points[0].y + 3*points[1].y -3*points[2].y+points[3].y;
    for(double t = 0; t < 1; t = t + 0.001){
        int x = a0 + a1*t + a2*t*t + a3*t*t*t;
        int y = b0 + b1*t + b2*t*t + b3*t*t*t;
        SetPixel(hdc, x, y, c);
    }
}

bool BezierCurve::addPoint(int x, int y) {
    if(points.size() == 3){
        points.push_back(MyPoint(x,y));
        return false;
    }
    points.push_back(MyPoint(x,y));
    return true;
}

BezierCurve::BezierCurve() {

}
