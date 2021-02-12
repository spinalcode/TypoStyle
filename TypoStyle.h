#ifndef WATCHY_TYPOSTYLE_H
#define WATCHY_TYPOSTYLE_H

#include <Watchy.h>
#include "graphics.h"

class TypoStyle : public Watchy{
    public:
        TypoStyle();
		void drawInvertBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color)
		void drawMyRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2)
		void drawWatchFace()
};

#endif