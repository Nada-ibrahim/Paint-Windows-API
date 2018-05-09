//
// Created by hp on 5/7/2018.
//

#ifndef UNTITLED1_CURVE_H
#define UNTITLED1_CURVE_H

#include "Shape.h"
#include "MyPoint.h"
#include <vector>
using namespace std;
class BezierCurve : public Shape{
    vector<MyPoint> points;
    COLORREF c;
public:
    BezierCurve(COLORREF c):c(c){}
    void bezierCurve(HDC hdc);

    bool addPoint(int x, int y);
    void write(ofstream &out);
    void read(ifstream &in);
    void draw(HDC hdc);

    BezierCurve();
};


#endif //UNTITLED1_CURVE_H
