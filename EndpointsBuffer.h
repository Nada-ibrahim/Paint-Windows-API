//
// Created by hp on 4/24/2018.
//

#ifndef UNTITLED1_ENDPOINTSBUFFER_H
#define UNTITLED1_ENDPOINTSBUFFER_H

#include <vector>
#include <windows.h>
#include "MyPoint.h"

using namespace std;
class EndpointsBuffer {

public:
    vector<pair<MyPoint, MyPoint>> endPoints;
    void addLine(MyPoint ps, MyPoint pe);
    void drawAllLines(HDC hdc, COLORREF c);
};


#endif //UNTITLED1_ENDPOINTSBUFFER_H
