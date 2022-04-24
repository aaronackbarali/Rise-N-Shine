
#ifndef EPDPAINT_H
#define EPDPAINT_H

// Display orientation
#define ROTATE_0            0
#define ROTATE_90           1
#define ROTATE_180          2
#define ROTATE_270          3

#include <Arduino.h>
#include "./Fonts/fonts.h"

class Paint {
public:
    unsigned char image[4736];
    int width = 0;
    int height = 0;
    int rotate = ROTATE_0;

    int  GetWidth();
    void SetWidth(int width);
    int  GetHeight();
    void SetHeight(int height);
    void SetRotate(int rotate);
    unsigned char* GetImage();
    void DrawAbsolutePixel(int x, int y, int colored);
    void DrawPixel(int x, int y, int colored);
    void DrawCharAt(int x, int y, char ascii_char, sFONT* font, int colored);
    void DrawStringAt(int x, int y, String text, sFONT* font, int colored);
    void Clear(int colored);
};

#endif
