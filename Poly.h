//
// Created by hp on 5/7/2018.
//

#ifndef UNTITLED1_POLYGON_H
#define UNTITLED1_POLYGON_H

#include "Shape.h"
#include "MyPoint.h"
#include <vector>
using namespace std;
class Poly : public Shape {

    COLORREF c;
public:
    vector<MyPoint> polygonPoints;
    Poly(COLORREF c);
    void addPointToPolygon(HDC hdc, int x, int y);
    void finishPolygon(HDC hdc);
    void draw(HDC hdc);
    void write(ofstream &out);
    void read(ifstream &in);

    Poly();
};


#endif //UNTITLED1_POLYGON_H
