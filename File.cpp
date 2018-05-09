//
// Created by hp on 5/7/2018.
//

#include "File.h"
#include "windows.h"
#include "ShapeBuffer.h"
#include "Line.h"
#include "Circle.h"
#include "BezierCurve.h"
#include "Filling.h"
#include "Poly.h"
#include "HermiteCurve.h"
#include <fstream>
using namespace std;

void File::save(HWND hwnd, HDC hdc, ShapeBuffer buffer) {
    OPENFILENAME ofn;       // common dialog box structure
    char szFile[260];       // buffer for file name
    HANDLE hf;              // file handle

// Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
// Set lpstrFile[0] to '\0' so that GetOpenFileName does not
// use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;

// Display the Open dialog box.

    if (GetSaveFileName(&ofn)==TRUE) {

//        hf = CreateFile(ofn.lpstrFile,
//                        GENERIC_WRITE,
//                        0,
//                        (LPSECURITY_ATTRIBUTES) NULL,
//                        CREATE_ALWAYS,
//                        FILE_ATTRIBUTE_NORMAL,
//                        (HANDLE) NULL);
        writeImg(hwnd,ofn.lpstrFile, hdc, buffer);

    }
}
void File::load(HWND hwnd, HDC hdc) {
    OPENFILENAME ofn;       // common dialog box structure
    char szFile[260];       // buffer for file name
    HANDLE hf;              // file handle

// Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
// Set lpstrFile[0] to '\0' so that GetOpenFileName does not
// use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

// Display the Open dialog box.

    if (GetOpenFileName(&ofn)==TRUE) {

//        hf = CreateFile(ofn.lpstrFile,
//                        GENERIC_WRITE,
//                        0,
//                        (LPSECURITY_ATTRIBUTES) NULL,
//                        CREATE_ALWAYS,
//                        FILE_ATTRIBUTE_NORMAL,
//                        (HANDLE) NULL);
        readImg(hwnd,ofn.lpstrFile, hdc);

    }
}

void File::writeImg(HWND hwnd, LPSTR path, HDC hdc, ShapeBuffer buffer) {
    string filePath = path;
    ofstream out;
    out.open(path, ios::out|ios::trunc);
    RECT rect;
    GetClientRect(hwnd, &rect);

    int totalWidth = rect.right + 16;
    int totalHeight = rect.bottom + 58;
    int sz = buffer.shapes.size();
    out.write((char *) &totalWidth, sizeof(rect.right));
    out.write((char *) &totalHeight, sizeof(rect.right));
    out.write((char *) &sz, sizeof(sz) );
    for(int i = 0; i < buffer.shapes.size(); ++i){
        if(dynamic_cast<Line*> (buffer.shapes[i]) != nullptr){
            char ch = 'l';
            out.write((char *) &ch, sizeof(char));
        }else if(dynamic_cast<Circle*> (buffer.shapes[i]) != nullptr){
            char ch = 'c';
            out.write((char *) &ch, sizeof(char));
        }else if(dynamic_cast<BezierCurve*> (buffer.shapes[i]) != nullptr){
            char ch = 'v';
            out.write((char *) &ch, sizeof(char));
        }else if(dynamic_cast<HermiteCurve*> (buffer.shapes[i]) != nullptr){
            char ch = 'h';
            out.write((char *) &ch, sizeof(char));
        }else if(dynamic_cast<Filling*> (buffer.shapes[i]) != nullptr){
            char ch = 'f';
            out.write((char *) &ch, sizeof(char));
        }else if(dynamic_cast<Poly*> (buffer.shapes[i]) != nullptr){
            char ch = 'p';
            out.write((char *) &ch, sizeof(char));
        }
        buffer.shapes[i]->write(out);
    }
//    for(int i = 0; i < totalWidth; ++i){
//        for(int j = 0; j < totalHeight; ++j){
//            COLORREF c = GetPixel(hdc, i, j);
//            BYTE R = GetRValue(c);
//            BYTE G = GetGValue(c);
//            BYTE B = GetBValue(c);
//            out.write((char *) &R, sizeof(GetRValue(c)));
//            out.write((char *) &G, sizeof(GetGValue(c)));
//            out.write((char *) &B, sizeof(GetBValue(c)));
//        }
//    }
    out.close();
}
void File::readImg(HWND hwnd, LPSTR path, HDC hdc) {
    string filePath = path;
    ifstream in;
    in.open(path, ios::in);
    RECT rect;
    GetClientRect(hwnd, &rect);
    int totalWidth;
    int totalHeight;
    int sz;
    in.read((char *) &totalWidth, sizeof(totalWidth));
    in.read((char *) &totalHeight, sizeof(totalHeight));
    in.read((char *) &sz, sizeof(sz));
    SetWindowPos(hwnd, HWND_TOP, 0, 0, totalWidth, totalHeight, SWP_NOMOVE);

    ShapeBuffer newBuffer;
    for(int i = 0; i < sz; ++i){
        char ch;
        in.read((char *) &ch, sizeof(ch));
        Shape *sh;
        if(ch == 'l'){
            sh = new Line;
        }else if(ch == 'c'){
            sh = new Circle;
        }else if(ch == 'v'){
            sh = new BezierCurve;
        }else if(ch == 'h'){
            sh = new HermiteCurve;
        }else if(ch == 'f'){
            sh = new Filling;
        }else if(ch == 'p'){
            sh = new Poly;
        }

        sh->read(in);
        newBuffer.addShape(sh);
        sh->draw(hdc);
    }
//    for(int i = 0; i < totalWidth; ++i){
//        for(int j = 0; j < totalHeight; ++j){
//            BYTE R, G, B;
//            in.read((char *) &R, sizeof(R));
//            in.read((char *) &G, sizeof(G));
//            in.read((char *) &B, sizeof(B));
//            COLORREF c = RGB(R, G, B);
//            SetPixel(hdc, i, j, c);
//        }
//    }
    in.close();
}


