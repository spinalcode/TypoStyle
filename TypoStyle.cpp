#include "TypoStyle.h"

TypoStyle::TypoStyle(){} //constructor

#define GREY 0x7BEF

void TypoStyle::drawPixel(int16_t x, int16_t y,uint16_t col){
  switch (col){
    case GREY:
      if(y&1){
        if(x&1){
          display.drawPixel(x, y, GxEPD_BLACK);
        }else{
          display.drawPixel(x, y, GxEPD_WHITE);
        }
      }else{
        if(x&1){
          display.drawPixel(x, y, GxEPD_WHITE);
        }else{
          display.drawPixel(x, y, GxEPD_BLACK);
        }
      }
      break;
    default:
      display.drawPixel(x, y, col);
      break;
  }
}

void TypoStyle::drawBitmapCol(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color1, uint16_t color2){
  int16_t i, j, byteWidth = (w + 7) / 8;
  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      if((pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)))) {
        drawPixel(x+i, y+j, color1);
      }else{
        drawPixel(x+i, y+j, color2);
      }
    }
  }
}

void TypoStyle::drawMyRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1){
  for(int j=0; j<h; j++) {
    for(int i=0; i<w; i++ ) {
      drawPixel(x+i, y+j, color1);
    }
  }  
}

void TypoStyle::drawWatchFace() { //override this method to customize how the watch face looks

    int clockLeft = -14;
    int clockTop = 15;
    int hour1 = currentTime.Hour/10;
    int hour2 = currentTime.Hour%10;
    int minute1 = currentTime.Minute/10;
    int minute2 = currentTime.Minute%10;
    int month = currentTime.Month-1;
    int day1 = currentTime.Day/10;
    int day2 = currentTime.Day%10;
    int year = currentTime.Year;
    int weekday = currentTime.Wday-1;
    int year1,year2,year3,year4;
  
    year4 = year % 10; year /= 10;
    year3 = year % 10; year /= 10;
    year2 = year % 10; year /= 10;
    year1 = year % 10; year /= 10;

    //int col1 = GREY; // foreground colour
    int col1 = GxEPD_WHITE; // foreground colour
    int col2 = GxEPD_BLACK; // background colour

    //drawbg
    drawMyRect(0, 0, 200, 200, col2);

    // time
    int ds = sizeof(clockDigits)/10; // 10 digits in image, so each frame is size of array/10
    int glyphWidth = 54;
    int glyphHeight = 72;
    col1 = GxEPD_WHITE;
    drawBitmapCol(clockLeft, clockTop, &clockDigits[hour1*ds], glyphWidth, glyphHeight, col1, col2);
    drawBitmapCol(clockLeft+glyphWidth, clockTop, &clockDigits[hour2*ds], glyphWidth, glyphHeight, col1, col2);
    col1 = GREY;
    drawBitmapCol(clockLeft+(glyphWidth*2)+(glyphWidth*0.25), clockTop, &clockDigits[minute1*ds], glyphWidth, glyphHeight, col1, col2);
    drawBitmapCol(clockLeft+(glyphWidth*3)+(glyphWidth*0.25), clockTop, &clockDigits[minute2*ds], glyphWidth, glyphHeight, col1, col2);

    drawMyRect(clockLeft+(glyphWidth*2)+2, clockTop+20, 10, 10, col1);
    drawMyRect(clockLeft+(glyphWidth*2)+2, clockTop+40, 10, 10, col1);
    
    // month
    ds = sizeof(monthName)/12;
    col1 = GxEPD_WHITE;
    drawBitmapCol(clockLeft-9, clockTop+72, &monthName[month*ds], 250, 30, col1, col2);

    // day
    ds = sizeof(dateDigits)/10;
    glyphWidth = 45;
    glyphHeight = 60;
    col1 = GREY;
    drawBitmapCol(clockLeft+16,              clockTop+107, &dateDigits[day1*ds], glyphWidth, glyphHeight, col1, col2);
    drawBitmapCol(clockLeft+16+(glyphWidth), clockTop+107, &dateDigits[day2*ds], glyphWidth, glyphHeight, col1, col2);

    // weekday
    ds = sizeof(dayName)/7;
    col1 = GREY;
    drawBitmapCol(clockLeft+103, clockTop+105, &dayName[weekday*ds], 154, 17, col1, col2);

    // year
    ds = sizeof(yearDigits)/10;
    glyphWidth = 30;
    glyphHeight = 45;
    col1 = GxEPD_WHITE;
    drawBitmapCol(clockLeft+103,                clockTop+122, &yearDigits[year1*ds], glyphWidth, glyphHeight, col1, col2);
    drawBitmapCol(clockLeft+103+(glyphWidth),   clockTop+122, &yearDigits[year2*ds], glyphWidth, glyphHeight, col1, col2);
    drawBitmapCol(clockLeft+103+(glyphWidth*2), clockTop+122, &yearDigits[year3*ds], glyphWidth, glyphHeight, col1, col2);
    drawBitmapCol(clockLeft+103+(glyphWidth*3), clockTop+122, &yearDigits[year4*ds], glyphWidth, glyphHeight, col1, col2);

    // battery
    float powerPercent = (getBatteryVoltage()-3.8)*200;
    drawMyRect(0, 187, (int)powerPercent, 13, GREY);
    
} // end function
