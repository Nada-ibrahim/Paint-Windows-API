//
// Created by hp on 4/10/2018.
//

#include "Filling.h"
#include "MyPoint.h"
#include <stack>
using namespace std;
void Filling::fillSeed(COLORREF fillColor, COLORREF boundColor, HDC hdc, int xc, int yc) {
     stack<MyPoint> points;
    points.push(MyPoint(xc,yc));
    while(!points.empty()){
        MyPoint p = points.top();
        points.pop();
        COLORREF c = GetPixel(hdc, p.x, p.y);
        if(c != fillColor && c != boundColor){
            SetPixel(hdc, p.x, p.y, fillColor);
            points.push(MyPoint(p.x+1, p.y));
            points.push(MyPoint(p.x, p.y+1));
            points.push(MyPoint(p.x-1, p.y));
            points.push(MyPoint(p.x, p.y-1));
        }
    }
}
