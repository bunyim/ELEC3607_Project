
// all the static constant for setting up the LED floor value
static const uint8_t PROGMEM
    lvl1[] = 
        { B00011000,
          B00111000,
          B01011000,
          B00011000,
          B00011000,
          B00011000,
          B11111111,
          B11111111},
 
    lvl2[] =
        { B11111111,
          B11111111,
          B00000111,
          B11111111,
          B11111111,
          B11100000,
          B11111111,
          B11111111},
 
    lvl3[] =
        { B11111111,
          B11111111,
          B00000111,
          B11111111,
          B11111111,
          B00000111,
          B11111111,
          B11111111} ;

// draw the lvls on the matrix
void draw(const uint8_t x[]) {
  matrix.clear();
  matrix.drawBitmap(0, 0, x, 8, 8, LED_ON);
  matrix.writeDisplay();
  }

// function to draw lvl 3
void arr3(){
  
  draw(lvl3);
  
}

// function to draw lvl 2
 void arr2(){
  
  
  draw(lvl2);
  
}

// function to draw lvl 1
void arr1(){

  draw(lvl1);
  
}
 
