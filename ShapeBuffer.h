//
// Created by hp on 4/24/2018.
//

#ifndef UNTITLED1_ENDPOINTSBUFFER_H
#define UNTITLED1_ENDPOINTSBUFFER_H

#include <vector>
#include <windows.h>
#include "MyPoint.h"
#include "Shape.h"

using namespace std;
class ShapeBuffer {

public:
    vector<Shape*> shapes;
    void addShape(Shape* sh);
    void drawAll(HDC hdc);
};


#endif //UNTITLED1_ENDPOINTSBUFFER_H
