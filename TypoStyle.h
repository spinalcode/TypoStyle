#ifndef WATCHY_TYPOSTYLE_H
#define WATCHY_TYPOSTYLE_H

#include <Watchy.h>
#include "graphics.h"

class TypoStyle : public Watchy{
    public:
        TypoStyle();
		void drawPixel(int16_t x, int16_t y,uint16_t col);
		void drawBitmapCol(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color1, uint16_t color2);
		void drawMyRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1);
		void drawWatchFace();
};

#endif
