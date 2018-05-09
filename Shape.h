//
// Created by hp on 5/7/2018.
//

#ifndef UNTITLED1_SHAPE_H
#define UNTITLED1_SHAPE_H


#include <afxres.h>
#include <fstream>
using namespace std;

class Shape {
public:
    virtual void draw(HDC hdc) = 0;
    virtual void write(ofstream & out ) {};
    virtual void read(ifstream &in) {};

};


#endif //UNTITLED1_SHAPE_H
