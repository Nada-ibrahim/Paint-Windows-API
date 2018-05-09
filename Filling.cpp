//
// Created by hp on 4/10/2018.
//

#include "Filling.h"
#include "MyPoint.h"
#include <stack>
using namespace std;
void Filling::fillSeed(HDC hdc) {
     stack<MyPoint> points;
    points.push(MyPoint(xc,yc));
    while(!points.empty()){
        MyPoint p = points.top();
        points.pop();
        COLORREF c = GetPixel(hdc, p.x, p.y);
        if(c == backColor){
            SetPixel(hdc, p.x, p.y, fillColor);
            points.push(MyPoint(p.x+1, p.y));
            points.push(MyPoint(p.x, p.y+1));
            points.push(MyPoint(p.x-1, p.y));
            points.push(MyPoint(p.x, p.y-1));
        }
    }
}

Filling::Filling(int xc, int yc, COLORREF backColor, COLORREF fillColor) : xc(xc), yc(yc),
                                                       backColor(backColor), fillColor(fillColor){

}

void Filling::draw(HDC hdc) {
    fillSeed(hdc);

}

void Filling::write(ofstream &out) {
    out.write((char*)& xc, sizeof(int));
    out.write((char*) &yc, sizeof(int));
    out.write((char*) &fillColor, sizeof(fillColor));
    out.write((char*) &backColor, sizeof(backColor));

}

void Filling::read(ifstream &in) {
    in.read((char*)& xc, sizeof(int));
    in.read((char*) &yc, sizeof(int));
    in.read((char*) &fillColor, sizeof(fillColor));
    in.read((char*) &backColor, sizeof(backColor));
}

Filling::Filling() {

}
