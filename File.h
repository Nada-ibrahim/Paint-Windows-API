//
// Created by hp on 5/7/2018.
//

#ifndef UNTITLED1_FILE_H
#define UNTITLED1_FILE_H


#include <afxres.h>
#include "ShapeBuffer.h"

class File {
public:
    void save(HWND hwnd, HDC hdc, ShapeBuffer buffer);
    void writeImg(HWND hwnd, LPSTR path, HDC hdc, ShapeBuffer buffer);

    void readImg(HWND hwnd, LPSTR path, HDC hdc);

    void load(HWND hwnd, HDC hdc);
};


#endif //UNTITLED1_FILE_H
