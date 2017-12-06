#include <stdio.h>
#include <cstring>
#include "frame.h"

frame::frame(int w, int h)  {
    this->w = w;
    this->h = h;
    pixels = new byte[w * h * 3]; 
}

frame::~frame() {
    delete pixels; 
}

void frame::setPixel(int x, int y, byte r, byte g, byte b) {
    pixels[y * w * 3 + x * 3 + 0] = r;
    pixels[y * w * 3 + x * 3 + 1] = g;
    pixels[y * w * 3 + x * 3 + 2] = b;
}

void frame::clear() {
    memset(pixels, 0, h * w * 3); 
}

bool frame::isOutside(int x, int y) const {
    return x < 0 || x >= w || y < 0 || y >= h;
}

void frame::write(FILE * file) const {
    fwrite(pixels, 3, w * h, file);
}
