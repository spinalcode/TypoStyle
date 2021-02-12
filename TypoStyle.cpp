#include "TypoStyle.h"

TypoStyle::TypoStyle(){} //constructor


void TypoStyle::drawInvertBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color){
  int16_t i, j, byteWidth = (w + 7) / 8;
  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      if((pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)))==0) {
        display.drawPixel(x+i, y+j, color);
      }
    }
  }
}

void TypoStyle::drawMyRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2){
	for(int j=0; j<h; j++) {
		for(int i=0; i<w; i++ ) {
			if(j&1){
				if(i&1){
					display.drawPixel(x+i, y+j, color1);
				}else{
					display.drawPixel(x+i, y+j, color2);
				}
			}else{
				if(i&1){
					display.drawPixel(x+i, y+j, color2);
				}else{
					display.drawPixel(x+i, y+j, color1);
				}
			}
		}
	}  
}

void TypoStyle::drawWatchFace() { //override this method to customize how the watch face looks

	int clockLeft = -16;
	int clockTop = 15;
	int hour1 = currentTime.Hour/10;
	int hour2 = currentTime.Hour%10;
	int minute1 = currentTime.Minute/10;
	int minute2 = currentTime.Minute%10;
	int month = currentTime.Month-1;
	int day1 = currentTime.Day/10;
	int day2 = currentTime.Day%10;
	int year = currentTime.Year;
	int weekday = dateTime.dayofWeek-1;
	int year1,year2,year3,year4;

	year4 = year % 10; year /= 10;
	year3 = year % 10; year /= 10;
	year2 = year % 10; year /= 10;
	year1 = year % 10; year /= 10;

    //drawbg
    display.fillScreen(GxEPD_BLACK);

    // time
    int ds = sizeof(clockDigits)/10; // 10 digits in image, so each fram is size of array/10
    //display.drawBitmap(clockLeft, clockTop, &clockDigits[hour1*ds], 36, 48, GxEPD_WHITE);
    int glyphWidth = 54;
    int glyphHeight = 72;
    drawMyRect(clockLeft, clockTop, glyphWidth, glyphHeight, GxEPD_BLACK, GxEPD_WHITE);
    drawInvertBitmap(clockLeft, clockTop, &clockDigits[hour1*ds], glyphWidth, glyphHeight, GxEPD_BLACK);
    drawMyRect(clockLeft+glyphWidth, clockTop, glyphWidth, glyphHeight, GxEPD_BLACK, GxEPD_WHITE);
    drawInvertBitmap(clockLeft+glyphWidth, clockTop, &clockDigits[hour2*ds], glyphWidth, glyphHeight, GxEPD_BLACK);
    drawMyRect(clockLeft+(glyphWidth*2)+(glyphWidth*0.25), clockTop, glyphWidth, glyphHeight, GxEPD_BLACK, GxEPD_WHITE);
    drawInvertBitmap(clockLeft+(glyphWidth*2)+(glyphWidth*0.25), clockTop, &clockDigits[minute1*ds], glyphWidth, glyphHeight, GxEPD_BLACK);
    drawMyRect(clockLeft+(glyphWidth*3)+(glyphWidth*0.25), clockTop, glyphWidth, glyphHeight, GxEPD_BLACK, GxEPD_WHITE);
    drawInvertBitmap(clockLeft+(glyphWidth*3)+(glyphWidth*0.25), clockTop, &clockDigits[minute2*ds], glyphWidth, glyphHeight, GxEPD_BLACK);

    drawMyRect(clockLeft+(glyphWidth*2)+2, clockTop+20, 10, 10, GxEPD_BLACK, GxEPD_WHITE);
    drawMyRect(clockLeft+(glyphWidth*2)+2, clockTop+40, 10, 10, GxEPD_BLACK, GxEPD_WHITE);

	// month
    ds = sizeof(monthName)/12;
    display.drawBitmap(clockLeft-9, clockTop+72, &monthName[month*ds], 250, 30, GxEPD_WHITE);

	// day
    ds = sizeof(dateDigits)/10;
    glyphWidth = 45;
    glyphHeight = 60;
    display.drawBitmap(clockLeft+16,              clockTop+107, &dateDigits[day1*ds], glyphWidth, glyphHeight, GxEPD_WHITE);
    display.drawBitmap(clockLeft+16+(glyphWidth), clockTop+107, &dateDigits[day2*ds], glyphWidth, glyphHeight, GxEPD_WHITE);

	// weekday
    ds = sizeof(dayName)/7;
    display.drawBitmap(clockLeft+103, clockTop+105, &dayName[weekday*ds], 154, 17, GxEPD_WHITE);

    // year
    ds = sizeof(yearDigits)/10;
    glyphWidth = 30;
    glyphHeight = 45;
    display.drawBitmap(clockLeft+103,                clockTop+122, &yearDigits[year1*ds], glyphWidth, glyphHeight, GxEPD_WHITE);
    display.drawBitmap(clockLeft+103+(glyphWidth),   clockTop+122, &yearDigits[year2*ds], glyphWidth, glyphHeight, GxEPD_WHITE);
    display.drawBitmap(clockLeft+103+(glyphWidth*2), clockTop+122, &yearDigits[year3*ds], glyphWidth, glyphHeight, GxEPD_WHITE);
    display.drawBitmap(clockLeft+103+(glyphWidth*3), clockTop+122, &yearDigits[year4*ds], glyphWidth, glyphHeight, GxEPD_WHITE);

	// Not sure about this bit yet

    // battery
    float power = getBatteryVoltage();
    display.drawBitmap(0,200-16, batteryIcon, 32, 16, GxEPD_WHITE);
    //int width = 23; // 100% = 23
    float powerPercent = (power-3.8)*23;
    drawMyRect(3, 200-13, (int)powerPercent, 10, GxEPD_BLACK, GxEPD_WHITE);


    // steps
    uint32_t stepCount = 1000; //sensor.getCounter();
    
} // end function
