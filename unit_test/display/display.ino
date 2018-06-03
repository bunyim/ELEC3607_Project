// this code is used to test the LED matrix 

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

static const uint8_t PROGMEM
    lvl1[] = 
        { B00000000,
          B00000000,
          B00000010,
          B00000110,
          B00000010,
          B00000010,
          B00000111,
          B00000000},
 
    lvl2[] =
        { B00000000,
          B00000000,
          B00000111,
          B00000001,
          B00000111,
          B00000100,
          B00000111,
          B00000000},
 
    lvl3[] =
        { B00000000,
          B00000000,
          B00000111,
          B00000001,
          B00000111,
          B00000001,
          B00000111,
          B00000000},
    
    arr_lvl1[] = 
        { B00000000,
          B01000000,
          B10100010,
          B00000110,
          B00000010,
          B10100010,
          B01000111,
          B00000000},
 
    arr_lvl2[] =
        { B00000000,
          B01000000,
          B10100111,
          B00000001,
          B00000111,
          B10100100,
          B01000111,
          B00000000},
 
    arr_lvl3[] =
        { B00000000,
          B01000000,
          B10100111,
          B00000001,
          B00000111,
          B10100001,
          B01000111,
          B00000000},
 
    up3_lvl1[] =
        { B00000000,
          B01000000,
          B10100010,
          B00000110,
          B00000010,
          B00000010,
          B00000111,
          B00000000},
 
    up2_lvl1[] =
        { B00000000,
          B00000000,
          B01000010,
          B10100110,
          B00000010,
          B00000010,
          B00000111,
          B00000000},
 
    up1_lvl1[] =
        { B00000000,
          B00000000,
          B00000010,
          B01000110,
          B10100010,
          B00000010,
          B00000111,
          B00000000},
 
    up3_lvl2[] =
        { B00000000,
          B01000000,
          B10100111,
          B00000001,
          B00000111,
          B00000100,
          B00000111,
          B00000000},
 
    up2_lvl2[] =
        { B00000000,
          B00000000,
          B01000111,
          B10100001,
          B00000111,
          B00000100,
          B00000111,
          B00000000},
 
    up1_lvl2[] =
        { B00000000,
          B00000000,
          B00000111,
          B01000001,
          B10100111,
          B00000100,
          B00000111,
          B00000000},
 
    dwn3_lvl3[] =
        { B00000000,
          B00000000,
          B00000111,
          B00000001,
          B00000111,
          B10100001,
          B01000111,
          B00000000},
 
    dwn2_lvl3[] =
        { B00000000,
          B00000000,
          B00000111,
          B00000001,
          B10100111,
          B01000001,
          B00000111,
          B00000000},
 
    dwn1_lvl3[] =
        { B00000000,
          B00000000,
          B00000111,
          B10100001,
          B01000111,
          B00000001,
          B00000111,
          B00000000},

    dwn3_lvl2[] =
        { B00000000,
          B00000000,
          B00000111,
          B00000001,
          B00000111,
          B10100100,
          B01000111,
          B00000000},
 
    dwn2_lvl2[] =
        { B00000000,
          B00000000,
          B00000111,
          B00000001,
          B10100111,
          B01000100,
          B00000111,
          B00000000},
 
    dwn1_lvl2[] =
        { B00000000,
          B00000000,
          B00000111,
          B10100001,
          B01000111,
          B00000100,
          B00000111,
          B00000000}  ;

void draw(const uint8_t x[]) {
  matrix.clear();
  matrix.drawBitmap(0, 0, x, 8, 8, LED_ON);
  matrix.writeDisplay();
  }
  
void up1() {
  draw(up1_lvl1);
  delay(300);
  draw(up2_lvl1);
  delay(300);
  draw(up3_lvl1);
  delay(300);
  }

void up2() {
  draw(up1_lvl2);
  delay(300);
  draw(up2_lvl2);
  delay(300);
  draw(up3_lvl2);
  delay(300);
  }

void dwn3() {
  draw(dwn1_lvl3);
  delay(300);
  draw(dwn2_lvl3);
  delay(300);
  draw(dwn3_lvl3);
  delay(300);
  }

void dwn2() {
  draw(dwn1_lvl2);
  delay(300);
  draw(dwn2_lvl2);
  delay(300);
  draw(dwn3_lvl2);
  delay(300);
  }

void arr1() {
  draw(arr_lvl1);
  delay(300);
  draw(lvl1);
  }

void arr2() {
  draw(arr_lvl2);
  delay(300);
  draw(lvl2);  
  }

void arr3() {
  draw(arr_lvl3);
  delay(300);
  draw(lvl3);  
  }
  

void setup() {
  matrix.begin(0x70);  // pass in the address
}

void loop() {
//sample
  up1();
  up1();
  up2();
  up2();
  arr3();
  delay(500);
  dwn3();
  dwn3();
  arr2();
  delay(500);
  dwn2();
  dwn2();
  arr1();
  delay(1000);
  }
