//
// Created by hp on 5/7/2018.
//

#include "Poly.h"
#include "Line.h"
Poly::Poly(COLORREF c) :c(c){}

void Poly::addPointToPolygon(HDC hdc, int x, int y) {
    MyPoint p(x,y);
    polygonPoints.push_back(p);
    if(polygonPoints.size() > 1){
        Line l(polygonPoints[polygonPoints.size()-2].x, polygonPoints[polygonPoints.size()-1].x,
               polygonPoints[polygonPoints.size()-2].y,polygonPoints[polygonPoints.size()-1].y, c);
        l.draw(hdc);
    }
}

void Poly::finishPolygon(HDC hdc) {
    Line l(polygonPoints[polygonPoints.size()-1].x, polygonPoints[0].x,
           polygonPoints[polygonPoints.size()-1].y,polygonPoints[0].y, c);
    l.draw(hdc);
}

void Poly::draw(HDC hdc) {
    MyPoint p1(polygonPoints[polygonPoints.size()-1].x, polygonPoints[polygonPoints.size()-1].y);
    for(int i = 0; i<polygonPoints.size(); ++i){
        MyPoint p2(polygonPoints[i].x, polygonPoints[i].y);
        Line l(p1.x, p2.x, p1.y, p2.y, c);
        l.drawLineMidpoint(hdc);
        p1 = p2;
    }

}

void Poly::write(ofstream &out) {
    out.write((char*)& polygonPoints, sizeof(polygonPoints));
    out.write((char*) &c, sizeof(c));
}

void Poly::read(ifstream &in) {
    in.read((char*)& polygonPoints, sizeof(polygonPoints));
    in.read((char*) &c, sizeof(c));
}

Poly::Poly() {

}
