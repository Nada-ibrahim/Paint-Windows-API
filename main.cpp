
#include <windows.h>
#include "Line.h"
#include "MyMenu.h"
#include "Circle.h"
#include "Filling.h"
#include "ShapeBuffer.h"
#include "Clipping.h"
#include "File.h"
#include "Poly.h"
#include "BezierCurve.h"
#include "HermiteCurve.h"

int xs, ys, xe, ye;
int counter = 0;
int whatToDo = NOTHING;
ShapeBuffer buffer;
Poly *poly = nullptr;
BezierCurve *cur = nullptr;
HermiteCurve *hcur = nullptr;
//wparam what i clicked on, file--> open
//lparam is related to the coordianes of the mouse

void addMenu(HWND hwnd){
    HMENU hmenu = CreateMenu();
    HMENU fileMenu = CreateMenu();
    HMENU lineMenu = CreateMenu();
    HMENU circleMenu = CreateMenu();
    HMENU fillMenu = CreateMenu();
    HMENU clipMenu = CreateMenu();
    HMENU curvesMenu = CreateMenu();
    HMENU polygonMenu = CreateMenu();

    AppendMenu(hmenu, MF_POPUP, (UINT)fileMenu , "&File");
    AppendMenu(hmenu, MF_POPUP, (UINT)lineMenu , "&Line");
    AppendMenu(hmenu, MF_POPUP, (UINT)circleMenu , "&Circle");
    AppendMenu(hmenu, MF_POPUP, (UINT)fillMenu , "f&ill");
    AppendMenu(hmenu, MF_POPUP, (UINT)clipMenu , "Cli&p");
    AppendMenu(hmenu, MF_POPUP, (UINT)curvesMenu , "Cur&ves");
    AppendMenu(hmenu, MF_POPUP, (UINT)polygonMenu , "Poly&gon");
    AppendMenu(fileMenu, MF_STRING, FILE_EXIT, "&Close");
    AppendMenu(fileMenu, MF_STRING, FILE_SAVE, "&Save");
    AppendMenu(fileMenu, MF_STRING, FILE_LOAD, "&Load");
    AppendMenu(lineMenu, MF_STRING, LINE_CARTESIAN, "&Cartesian Line");
    AppendMenu(lineMenu, MF_STRING, LINE_DDA, "&DDA Line");
    AppendMenu(lineMenu, MF_STRING, LINE_MIDPOINt, "&Midpoint Line");
    AppendMenu(circleMenu, MF_STRING, CIRCLE_MIDPOINT, "Midp&oint Circle");
    AppendMenu(circleMenu, MF_STRING, CIRCLE_CARTESIAN, "Cartesian Ci&rcle");
    AppendMenu(circleMenu, MF_STRING, CIRCLE_POLAR, "&Polar Circle");
    AppendMenu(fillMenu, MF_STRING, FILL_SEED, "Fill &Seed");
    AppendMenu(clipMenu, MF_STRING, CLIP_LINE, "Clip Line");
    AppendMenu(clipMenu, MF_STRING, CLIP_POLYGON, "Clip Polygon");
    AppendMenu(curvesMenu, MF_STRING, BEZIER_CURVE, "Bezeir BezierCurve");
    AppendMenu(curvesMenu, MF_STRING, HERMIT_CURVE, "Hermit BezierCurve");
    AppendMenu(polygonMenu, MF_STRING, POLYGON_START, "Start");
    AppendMenu(polygonMenu, MF_STRING, POLYGON_FINISH, "Finish");

    SetMenu(hwnd, hmenu);
}
LRESULT CALLBACK wndProc(HWND hwnd,  UINT message, WPARAM wp, LPARAM lp){
    COLORREF c;
    PAINTSTRUCT p;
    HDC hdc;
    switch(message){
        case WM_CREATE:
            addMenu(hwnd);
            break;
        case WM_COMMAND:
            switch(wp){
                case FILE_EXIT:
                    PostQuitMessage(0);
                    break;
                case LINE_CARTESIAN:
                    whatToDo = LINE_CARTESIAN;
                    break;
                case LINE_DDA:
                    whatToDo = LINE_DDA;
                    break;
                case LINE_MIDPOINt:
                    whatToDo = LINE_MIDPOINt;
                    break;
                case CIRCLE_MIDPOINT:
                    whatToDo = CIRCLE_MIDPOINT;
                    break;
                case CIRCLE_CARTESIAN:
                    whatToDo = CIRCLE_CARTESIAN;
                    break;
                case CIRCLE_POLAR:
                    whatToDo = CIRCLE_POLAR;
                    break;
                case FILL_SEED:
                    whatToDo = FILL_SEED;
                    break;
                case CLIP_LINE:
                    whatToDo = CLIP_LINE;
                    break;
                case CLIP_POLYGON:
                    whatToDo = CLIP_POLYGON;
                    break;
                case FILE_SAVE:
                    whatToDo = FILE_SAVE;
                    break;
                case FILE_LOAD:
                    whatToDo = FILE_LOAD;
                    break;
                case BEZIER_CURVE:
                    whatToDo = BEZIER_CURVE;
                    break;
                case HERMIT_CURVE:
                    whatToDo = HERMIT_CURVE;
                    break;
                case POLYGON_START:
                    whatToDo = POLYGON_START;
                    break;
                case POLYGON_FINISH:
                    whatToDo = POLYGON_FINISH;
                    break;
                default:break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_LBUTTONDOWN:
            if(counter == 0){
                xs = LOWORD(lp);
                ys = HIWORD(lp);
                ++counter;
            }else{
                xe = LOWORD(lp);
                ye = HIWORD(lp);
                ++counter;
            }
            //SetPixel(hdc, x, y, c);
            InvalidateRect(hwnd, NULL, FALSE);

            break;
        case WM_PAINT:
            //InvalidateRect(hwnd, NULL, TRUE);
            if(counter == 2) {
                if (whatToDo == LINE_DDA) {
                    hdc = BeginPaint(hwnd, &p);
                    c = RGB(255,0,0);
                    Line *l = new Line( xs, xe, ys, ye,c );
                    MyPoint ps(xs, ys);
                    MyPoint pe(xe, ye);
                    buffer.addShape(l);
                    l->drawLineDDA(hdc);
                    counter = 0;
                } else if (whatToDo == LINE_MIDPOINt) {
                    hdc = BeginPaint(hwnd, &p);
                    c = RGB(0,255,0);
                    Line *l = new Line( xs, xe, ys, ye,c );
                    MyPoint ps(xs, ys);
                    MyPoint pe(xe, ye);
                    buffer.addShape(l);
                    l->drawLineCartesian(hdc);
                    counter = 0;
                } else if (whatToDo == LINE_CARTESIAN) {
                    hdc = BeginPaint(hwnd, &p);
                    c = RGB(0,0,255);
                    Line *l = new Line( xs, xe, ys, ye,c );
                    MyPoint ps(xs, ys);
                    MyPoint pe(xe, ye);
                    buffer.addShape(l);
                    l->drawLineMidpoint(hdc);
                    counter = 0;
                }else if(whatToDo == CIRCLE_MIDPOINT){
                    hdc = BeginPaint(hwnd, &p);
                    c = RGB(255,0,0);
                    Circle *cir = new Circle(xs, ys, xe, ye, c);
                    buffer.addShape(cir);
                    cir->drawCircleMidpoint(hdc);
                    counter = 0;
                }else if(whatToDo == CIRCLE_CARTESIAN) {
                    hdc = BeginPaint(hwnd, &p);
                    c = RGB(0, 255, 0);
                    Circle *cir = new Circle(xs, ys, xe, ye, c);
                    buffer.addShape(cir);
                    cir->drawCircleCartesian(hdc);
                    counter = 0;
                }else if(whatToDo == CIRCLE_POLAR){
                    hdc = BeginPaint(hwnd, &p);
                    c = RGB(0, 0, 255);
                    Circle *cir = new Circle(xs, ys, xe, ye, c);
                    buffer.addShape(cir);
                    cir->drawCirclePolar(hdc);
                    counter = 0;
                }else if(whatToDo == CLIP_LINE){
                    InvalidateRect(hwnd, NULL, TRUE);
                    hdc = BeginPaint(hwnd, &p);
                    Clipping cl;
                    //InvalidateRect(hwnd, NULL, TRUE);
                    cl.clip(MyPoint(xs, ys), MyPoint(xe, ye), buffer, hdc);

                    counter = 0;
                }else if(whatToDo == CLIP_POLYGON){
                    InvalidateRect(hwnd, NULL, TRUE);
                    hdc = BeginPaint(hwnd, &p);
                    Clipping cl;
                    cl.polygonClip(MyPoint(xs, ys), MyPoint(xe, ye), buffer, hdc);
                    counter = 0;
                }

            }
            if(counter == 1){
                if(whatToDo == FILL_SEED) {
                    hdc = BeginPaint(hwnd, &p);
                    COLORREF cfill = RGB(255,255,0);
                    c = GetPixel(hdc, xs, ys);
                    Filling *f = new Filling(xs, ys,c,cfill);
                    buffer.addShape(f);
                    f->fillSeed(hdc);
                    counter = 0;
                }
                if(whatToDo == POLYGON_START){
                    hdc = BeginPaint(hwnd, &p);
                    if(poly == nullptr){
                        c = RGB(0,0,255);
                        poly = new Poly(c);
                    }
                    poly->addPointToPolygon(hdc, xs,ys);
                    counter = 0;
                }if(whatToDo == POLYGON_FINISH){
                    hdc = BeginPaint(hwnd, &p);
                    if(poly != nullptr) {
                        poly->finishPolygon(hdc);
                        buffer.addShape(poly);
                        poly = nullptr;
                    }
                    counter = 0;
                    whatToDo = NOTHING;
                }if(whatToDo == BEZIER_CURVE){
                    hdc = BeginPaint(hwnd, &p);
                    c = RGB(255,0, 0);
                    if(cur == nullptr){
                        cur = new BezierCurve(c);
                        cur->addPoint(xs,ys);
                    }else{
                        if(!cur->addPoint(xs,ys)){
                            buffer.addShape(cur);
                            cur->bezierCurve(hdc);
                            //cur = nullptr;
                        }
                    }
                    counter = 0;
                }if(whatToDo == HERMIT_CURVE){
                    hdc = BeginPaint(hwnd, &p);
                    c = RGB(255,0, 0);
                    if(hcur == nullptr){
                        hcur = new HermiteCurve(c);
                        hcur->addPoint(xs,ys);
                    }else{
                        if(!hcur->addPoint(xs,ys)){
                            buffer.addShape(hcur);
                            hcur->hermiteCurve(hdc);
                            hcur = nullptr;
                        }
                    }
                    counter = 0;
                }
            }
            if(whatToDo == FILE_SAVE){
                hdc = BeginPaint(hwnd, &p);
                File f;
                f.save(hwnd , hdc,buffer );
                whatToDo = NOTHING;
                counter = 0;
            }
            if(whatToDo == FILE_LOAD){
                InvalidateRect(hwnd, NULL, TRUE);
                hdc = BeginPaint(hwnd, &p);
                File f;
                f.load(hwnd , hdc);
                whatToDo = NOTHING;
                counter = 0;
            }
            if(whatToDo == NOTHING){
                counter = 0;
            }
            EndPaint(hwnd, &p);

            break;
        default:
            return DefWindowProc(hwnd, message, wp, lp);
    }
}

//Hinstance --> pointer to my exe
//x --> windows minimized or maximized
int APIENTRY WinMain(HINSTANCE curr, HINSTANCE prev, LPSTR str, int x){
    WNDCLASS wc;
    wc.hInstance = curr;
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hIcon = LoadIconA(NULL, IDI_WINLOGO);
    wc.lpfnWndProc = wndProc;
    wc.lpszClassName = "Nada";
    //wc.lpszMenuName = MAKEINTRESOURCE(MY_MENU_ID);
    wc.lpszMenuName = NULL;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    //parameter after 600 is the parent of the window, so that when returning to the parent,
    //it returns to the parent i defined
    HWND myWnd = CreateWindowA("Nada",
                               "Hello",
                               WS_OVERLAPPEDWINDOW,
                               100,
                               100,
                               800,
                               600,
                               NULL,
                               NULL,
                               curr,
                               0);
    // 0 --> default
    //1 --> minimized
    //2 --> maximized
    ShowWindow(myWnd, 1);
    MSG m;
    while(GetMessageA(&m,NULL, 0, 0) > 0){
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    return 0;
}