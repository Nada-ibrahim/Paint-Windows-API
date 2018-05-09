//
// Created by hp on 4/24/2018.
//

#include <cmath>
#include "Clipping.h"
#include "Line.h"

void Clipping::clip(MyPoint d1, MyPoint d2, ShapeBuffer &buffer, HDC hdc) {
    xl = d1.x;
    xr = d2.x;
    yt = d1.y;
    yb = d2.y;
    for(int i = 0; i < buffer.shapes.size(); ++i) {
        Line* l = dynamic_cast<Line *>(buffer.shapes[i]);

        if (l != nullptr) {
            MyPoint p1 = MyPoint(l->xs, l->ys), p2 = MyPoint(l->xe, l->ye);

            while (true) {
                pair<outcode, outcode> o = getOutCode(p1, p2);
                int a = o.first.all & o.second.all;
                if (o.first.all == 0 && o.second.all == 0) {
                    l->xs = p1.x;
                    l->ys = p1.y;
                    l->xe = p2.x;
                    l->ye = p2.y;
                    buffer.shapes[i]= l;
                    break;
                } else if (a != 0) {
                    l->xs = -1;
                    buffer.shapes[i] = l;
                    break;
                } else {
                    if (o.first.top) {
                        p1.x = round(p1.x + (((yt - p1.y) * (p2.x - p1.x)) / (p2.y - p1.y)));
                        p1.y = yt;
                    } else if (o.first.bottom) {
                        p1.x = round(p1.x + ((yb - p1.y) * (p2.x - p1.x) / (p2.y - p1.y)));
                        p1.y = yb;
                    } else if (o.first.left) {
                        p1.y = round(p1.y + (((p2.y - p1.y) * (xl - p1.x)) / (p2.x - p1.x)));
                        p1.x = xl;
                    } else if (o.first.right) {
                        p1.y = round(p1.y + (((p2.y - p1.y) * (xr - p1.x)) / (p2.x - p1.x)));
                        p1.x = xr;
                    }

                    if (o.second.top) {
                        p2.x = round(p1.x + (((yt - p1.y) * (p2.x - p1.x)) / (p2.y - p1.y)));
                        p2.y = yt;
                    } else if (o.second.bottom) {
                        p2.x = round(p1.x + ((yb - p1.y) * (p2.x - p1.x) / (p2.y - p1.y)));
                        p2.y = yb;
                    } else if (o.second.left) {
                        p2.y = round(p1.y + (((p2.y - p1.y) * (xl - p1.x)) / (p2.x - p1.x)));
                        p2.x = xl;
                    } else if (o.second.right) {
                        p2.y = round(p1.y + (((p2.y - p1.y) * (xr - p1.x)) / (p2.x - p1.x)));
                        p2.x = xr;
                    }

                }
            }

        }
    }
    buffer.drawAll(hdc);

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

void Clipping::polygonClip(MyPoint d1, MyPoint d2, ShapeBuffer &buffer, HDC hdc) {
    xl = d1.x;
    xr = d2.x;
    yt = d1.y;
    yb = d2.y;
    for (int i = 0; i < buffer.shapes.size(); ++i) {
        Poly *p = dynamic_cast<Poly *>(buffer.shapes[i]);
        if (p != nullptr) {
            Poly pout;
            pout = clipLeft(*p, hdc);
            pout = clipRight(pout, hdc);
            pout = clipTop(pout, hdc);
            pout = clipBottom(pout, hdc);
            p->polygonPoints = pout.polygonPoints;
            buffer.shapes[i] = p;
        }
    }
    buffer.drawAll(hdc);
}

Poly Clipping::clipLeft(Poly pin, HDC hdc) {
    Poly pout;
    if (!pin.polygonPoints.empty()) {
        MyPoint v1 = pin.polygonPoints[pin.polygonPoints.size() - 1];
        for (int i = 0; i < pin.polygonPoints.size(); ++i) {
            MyPoint v2 = pin.polygonPoints[i];
            if (v1.x > xl && v2.x > xl) {
                pout.polygonPoints.push_back(MyPoint(v2.x, v2.y));
            } else if (v1.x > xl) {
                int y = round(v1.y + (((v2.y - v1.y) * (xl - v1.x)) / (v2.x - v1.x)));
                int x = xl;
                pout.polygonPoints.push_back(MyPoint(x, y));
            } else if (v2.x > xl) {
                int y = round(v1.y + (((v2.y - v1.y) * (xl - v1.x)) / (v2.x - v1.x)));
                int x = xl;
                pout.polygonPoints.push_back(MyPoint(x, y));
                pout.polygonPoints.push_back(MyPoint(v2.x, v2.y));
            }
            v1 = v2;
        }
        return pout;
    }
}

Poly Clipping::clipRight(Poly pin, HDC hdc) {
    Poly pout;
    if (!pin.polygonPoints.empty()) {
        MyPoint v1 = pin.polygonPoints[pin.polygonPoints.size() - 1];
        for (int i = 0; i < pin.polygonPoints.size(); ++i) {
            MyPoint v2 = pin.polygonPoints[i];
            if (v1.x < xr && v2.x < xr) {
                pout.polygonPoints.push_back(MyPoint(v2.x, v2.y));
            } else if (v1.x < xr) {
                int y = round(v1.y + (((v2.y - v1.y) * (xr - v1.x)) / (v2.x - v1.x)));
                int x = xr;
                pout.polygonPoints.push_back(MyPoint(x, y));
            } else if (v2.x < xr) {
                int y = round(v1.y + (((v2.y - v1.y) * (xr - v1.x)) / (v2.x - v1.x)));
                int x = xr;
                pout.polygonPoints.push_back(MyPoint(x, y));
                pout.polygonPoints.push_back(MyPoint(v2.x, v2.y));
            }
            v1 = v2;
        }
        return pout;
    }
}

Poly Clipping::clipBottom(Poly pin, HDC hdc) {
    Poly pout;
    if (!pin.polygonPoints.empty()) {
        MyPoint v1 = pin.polygonPoints[pin.polygonPoints.size() - 1];
        for (int i = 0; i < pin.polygonPoints.size(); ++i) {
            MyPoint v2 = pin.polygonPoints[i];
            if (v1.y < yb && v2.y < yb) {
                pout.polygonPoints.push_back(MyPoint(v2.x, v2.y));
            } else if (v1.y < yb) {
                int x = round(v1.x + ((yb - v1.y) * (v2.x - v1.x) / (v2.y - v1.y)));
                int y = yb;
                pout.polygonPoints.push_back(MyPoint(x, y));
            } else if (v2.y < yb) {
                int x = round(v1.x + ((yb - v1.y) * (v2.x - v1.x) / (v2.y - v1.y)));
                int y = yb;
                pout.polygonPoints.push_back(MyPoint(x, y));
                pout.polygonPoints.push_back(MyPoint(v2.x, v2.y));
            }
            v1 = v2;
        }
        return pout;
    }
}

Poly Clipping::clipTop(Poly pin, HDC hdc) {
    Poly pout;
    if(!pin.polygonPoints.empty()) {
        MyPoint v1 = pin.polygonPoints[pin.polygonPoints.size() - 1];
        for (int i = 0; i < pin.polygonPoints.size(); ++i) {
            MyPoint v2 = pin.polygonPoints[i];
            if (v1.y > yt && v2.y > yt) {
                pout.polygonPoints.push_back(MyPoint(v2.x, v2.y));
            } else if (v1.y > yt) {
                int x = round(v1.x + ((yt - v1.y) * (v2.x - v1.x) / (v2.y - v1.y)));
                int y = yt;
                pout.polygonPoints.push_back(MyPoint(x, y));
            } else if (v2.y > yt) {
                int x = round(v1.x + ((yt - v1.y) * (v2.x - v1.x) / (v2.y - v1.y)));
                int y = yt;
                pout.polygonPoints.push_back(MyPoint(x, y));
                pout.polygonPoints.push_back(MyPoint(v2.x, v2.y));
            }
            v1 = v2;
        }
        return pout;
    }
}

