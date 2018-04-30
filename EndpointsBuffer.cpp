//
// Created by hp on 4/24/2018.
//

#include "EndpointsBuffer.h"
#include "Line.h"


void EndpointsBuffer::addLine(MyPoint ps, MyPoint pe) {
    pair<MyPoint, MyPoint> p(ps, pe);
    endPoints.push_back(p);
}

void EndpointsBuffer::drawAllLines(HDC hdc, COLORREF c) {

    for(int i = 0; i < endPoints.size(); ++i){
        if(endPoints[i].first.x  < 0 )
            continue;
        Line l;
        l.drawLineMidpoint(hdc, c, endPoints[i].first.x, endPoints[i].second.x,
                           endPoints[i].first.y, endPoints[i].second.y);
    }

}
