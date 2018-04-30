//
// Created by hp on 4/24/2018.
//

#include <cmath>
#include "Clipping.h"

void Clipping::clip(MyPoint d1, MyPoint d2, EndpointsBuffer &lines, HDC hdc, COLORREF c) {
    xl = d1.x;
    xr = d2.x;
    yt = d1.y;
    yb = d2.y;
    for(int i = 0; i < lines.endPoints.size(); ++i){
        MyPoint p1 = lines.endPoints[i].first,  p2 = lines.endPoints[i].second;

        while(true){
            pair<outcode, outcode> o = getOutCode(p1, p2);
            int a = o.first.all & o.second.all;
            if(o.first.all == 0 && o.second.all == 0){
                lines.endPoints[i].first = p1;
                lines.endPoints[i].second = p2;
                break;
            }else if(a != 0){
                lines.endPoints[i].first.x = -1;
                break;
            } else {
                if (o.first.top) {
                    p1.x = round(p1.x + (((yt - p1.y) * (p2.x - p1.x))/ (p2.y - p1.y)));
                    p1.y = yt;
                } else if (o.first.bottom) {
                    p1.x = round(p1.x + ((yb - p1.y) * (p2.x - p1.x)/ (p2.y - p1.y)));
                    p1.y = yb;
                } else if (o.first.left) {
                    p1.y = round(p1.y + (((p2.y - p1.y)* (xl - p1.x))/ (p2.x - p1.x)));
                    p1.x = xl;
                } else if (o.first.right) {
                    p1.y = round(p1.y + (((p2.y - p1.y)* (xr - p1.x))/ (p2.x - p1.x)));
                    p1.x = xr;
                }

                if (o.second.top) {
                    p2.x = round(p1.x + (((yt - p1.y) * (p2.x - p1.x))/ (p2.y - p1.y)));
                    p2.y = yt;
                } else if (o.second.bottom) {
                    p2.x = round(p1.x + ((yb - p1.y) * (p2.x - p1.x)/ (p2.y - p1.y)));
                    p2.y = yb;
                } else if (o.second.left) {
                    p2.y = round(p1.y + (((p2.y - p1.y)* (xl - p1.x))/ (p2.x - p1.x)));
                    p2.x = xl;
                } else if (o.second.right) {
                    p2.y = round(p1.y + (((p2.y - p1.y)* (xr - p1.x))/ (p2.x - p1.x)));
                    p2.x = xr;
                }

            }
        }

    }
    lines.drawAllLines(hdc, c);

}

pair<outcode, outcode> Clipping::getOutCode(MyPoint ps, MyPoint pe) {
    outcode o1;
    if(ps.x < xl){
        o1.left = 1;
    }if(ps.x > xr){
        o1.right = 1;
    }if(ps.y < yt){
        o1.top = 1;
    }if(ps.y > yb){
        o1.bottom = 1;
    }
    outcode o2;
    if(pe.x < xl){
        o2.left = 1;
    }if(pe.x > xr){
        o2.right = 1;
    }if(pe.y < yt){
        o2.top = 1;
    }if(pe.y > yb){
        o2.bottom = 1;
    }
    return pair<outcode, outcode>(o1, o2);
}
