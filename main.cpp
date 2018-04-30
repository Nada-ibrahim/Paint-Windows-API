
#include <windows.h>
#include "Line.h"
#include "MyMenu.h"
#include "Circle.h"
#include "Filling.h"
#include "EndpointsBuffer.h"
#include "Clipping.h"

#define DRAW_LINE_CART 1
#define DRAW_LINE_DDA 2
#define DRAW_LINE_MID 3
#define DRAW_CIRCLE_MID 4
#define DRAW_CIRCLE_CART 5
#define DRAW_FILL_SEED 6
#define DRAW_CLIP_LINE 7

int xs, ys, xe, ye;
int counter = 0;
int whatToDraw;
EndpointsBuffer lines;

//wparam what i clicked on, file--> open
//lparam is related to the coordianes of the mouse

void addMenu(HWND hwnd){
    HMENU hmenu = CreateMenu();
    HMENU fileMenu = CreateMenu();
    HMENU lineMenu = CreateMenu();
    HMENU circleMenu = CreateMenu();
    HMENU fillMenu = CreateMenu();
    HMENU clipMenu = CreateMenu();

    AppendMenu(hmenu, MF_POPUP, (UINT)fileMenu , "&File");
    AppendMenu(hmenu, MF_POPUP, (UINT)lineMenu , "&Line");
    AppendMenu(hmenu, MF_POPUP, (UINT)circleMenu , "&Circle");
    AppendMenu(hmenu, MF_POPUP, (UINT)fillMenu , "f&ill");
    AppendMenu(hmenu, MF_POPUP, (UINT)clipMenu , "Cli&p");
    AppendMenu(fileMenu, MF_STRING, FILE_EXIT, "&Exit");
    AppendMenu(lineMenu, MF_STRING, LINE_CARTESIAN, "&Cartesian Line");
    AppendMenu(lineMenu, MF_STRING, LINE_DDA, "&DDA Line");
    AppendMenu(lineMenu, MF_STRING, LINE_MIDPOINt, "&Midpoint Line");
    AppendMenu(circleMenu, MF_STRING, CIRCLE_MIDPOINT, "Midp&oint Circle");
    AppendMenu(circleMenu, MF_STRING, CIRCLE_CARTESIAN, "Cartesian Ci&rcle");
    AppendMenu(fillMenu, MF_STRING, FILL_SEED, "Fill &Seed");
    AppendMenu(clipMenu, MF_STRING, CLIP_LINE, "Clip Line");

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
                    whatToDraw = DRAW_LINE_CART;
                    break;
                case LINE_DDA:
                    whatToDraw = DRAW_LINE_DDA;
                    break;
                case LINE_MIDPOINt:
                    whatToDraw = DRAW_LINE_MID;
                    break;
                case CIRCLE_MIDPOINT:
                    whatToDraw = DRAW_CIRCLE_MID;
                    break;
                case CIRCLE_CARTESIAN:
                    whatToDraw = DRAW_CIRCLE_CART;
                    break;
                case FILL_SEED:
                    whatToDraw = DRAW_FILL_SEED;
                    break;
                case CLIP_LINE:
                    whatToDraw = DRAW_CLIP_LINE;
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
            hdc = BeginPaint(hwnd, &p);
            if(counter == 2) {
                if (whatToDraw == DRAW_LINE_DDA) {
                    Line l;
                    c = RGB(255,0,0);
                    MyPoint ps(xs, ys);
                    MyPoint pe(xe, ye);
                    lines.addLine(ps, pe);
                    l.drawLineDDA(hdc, c, xs, xe, ys, ye);
                    counter = 0;
                } else if (whatToDraw == DRAW_LINE_MID) {
                    Line l;
                    MyPoint ps(xs, ys);
                    MyPoint pe(xe, ye);
                    lines.addLine(ps, pe);
                    c = RGB(0,255,0);
                    l.drawLineCartesian(hdc, c, xs, xe, ys, ye);
                    counter = 0;
                } else if (whatToDraw == DRAW_LINE_CART) {
                    Line l;
                    MyPoint ps(xs, ys);
                    MyPoint pe(xe, ye);
                    lines.addLine(ps, pe);
                    c = RGB(0,0,255);
                    l.drawLineMidpoint(hdc, c, xs, xe, ys, ye);
                    counter = 0;
                }else if(whatToDraw == DRAW_CIRCLE_MID){
                    Circle cir;
                    c = RGB(255,0,0);
                    cir.drawCircleMidpoint(hdc, c, xs, ys, xe, ye);
                    counter = 0;
                }else if(whatToDraw == DRAW_CIRCLE_CART){
                    Circle cir;
                    c = RGB(0,255,0);
                    cir.drawCircleCartesian(hdc, c, xs, ys, xe, ye);
                    counter = 0;
                }else if(whatToDraw == DRAW_CLIP_LINE){
                    Clipping cl;
                    c = RGB(255,0,0);
                    //InvalidateRect(hwnd, NULL, TRUE);
                    cl.clip(MyPoint(xs, ys), MyPoint(xe, ye), lines, hdc, c);

                    counter = 0;
                }

            }
            if(counter == 1){
                if(whatToDraw == DRAW_FILL_SEED) {
                    Filling f;
                    COLORREF cfill = RGB(255,255,0);
                    COLORREF cBound = RGB(0,255,0);
                    f.fillSeed(cfill, cBound,hdc, xs, ys);
                    counter = 0;
                }
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