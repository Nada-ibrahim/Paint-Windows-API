//
// Created by hp on 5/7/2018.
//

#include "HermiteCurve.h"

void HermiteCurve::hermiteCurve(HDC hdc) {
    double a0 = points[0].x;
    double a1 = points[1].x ;
    double a2 = -3*points[0].x - 2*points[1].x - points[2].x + 3* points[3].x;
    double a3 = 2*points[0].x - 2*points[3].x + points[2].x + points[1].x;
    double b0 = points[0].y;
    double b1 = points[1].y ;
    double b2 = -3*points[0].y - 2*points[1].y - points[2].y + 3* points[3].y;
    double b3 = 2*points[0].y - 2*points[3].y + points[2].y + points[1].y;

    for(double t = 0; t < 1; t = t + 0.001){
        double x = a0 + a1*t + a2*t*t + a3*t*t*t;
        double y = b0 + b1*t + b2*t*t + b3*t*t*t;
        SetPixel(hdc, x, y, c);
    }
}

bool HermiteCurve::addPoint(int x, int y) {
    if(points.size() == 3){
        points.push_back(MyPoint(x,y));
        return false;
    }
    points.push_back(MyPoint(x,y));
    return true;
}

void HermiteCurve::write(ofstream &out) {
    for(int i = 0; i < 4; ++i){
        int x = points[i].x;
        int y = points[i].y;
        out.write((char*)& x, sizeof(int));
        out.write((char*)& y, sizeof(int));
    }
    out.write((char*) &c, sizeof(c));
}

void HermiteCurve::read(ifstream &in) {
    for(int i = 0; i < 4; ++i){
        int x;
        int y;
        in.read((char*)& x, sizeof(int));
        in.read((char*)& y, sizeof(int));
        addPoint(x,y);
    }
    in.read((char*) &c, sizeof(c));
}

void HermiteCurve::draw(HDC hdc) {
    hermiteCurve(hdc);
}

HermiteCurve::HermiteCurve() {

}
