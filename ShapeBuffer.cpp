//
// Created by hp on 4/24/2018.
//

#include "ShapeBuffer.h"
#include "Line.h"


void ShapeBuffer::addShape(Shape* shape) {
    shapes.push_back(shape);
}

void ShapeBuffer::drawAll(HDC hdc) {
    for(int i = 0; i < shapes.size(); ++i){
            shapes[i]->draw(hdc);
    }

}
