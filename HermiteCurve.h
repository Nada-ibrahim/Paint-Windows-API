//
// Created by hp on 5/7/2018.
//

#ifndef UNTITLED1_HERMITECURVE_H
#define UNTITLED1_HERMITECURVE_H


#include "MyPoint.h"
#include "Shape.h"
#include <vector>
using namespace std;
class HermiteCurve : public Shape {
    vector<MyPoint> points;
    COLORREF c;
public:
    HermiteCurve(COLORREF c):c(c){}
    void hermiteCurve(HDC hdc);

    bool addPoint(int x, int y);
    void write(ofstream &out);
    void read(ifstream &in);
    void draw(HDC hdc);

    HermiteCurve();
};


#endif //UNTITLED1_HERMITECURVE_H
