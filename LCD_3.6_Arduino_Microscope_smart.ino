// Davide Caminati Demo Microscope 2019
// Demo based on:
// UTFT_Demo by Henning Karlsen
// web: http://www.henningkarlsen.com/electronics


#include "Adafruit_GFX_AS.h"
#include "Adafruit_R61581_AS.h"

#define R61581_MY_BLUE   0x001F // background
#define R61581_MY_CYAN    0x07FF // sprite

Adafruit_R61581_AS myGLCD = Adafruit_R61581_AS();       // Invoke custom library

const String linea00 = "000000000100000000000"; // start
const String linea01 = "011101111111111101110";
const String linea02 = "010001010000010101010";
const String linea03 = "011111010111110101010";
const String linea04 = "000000000100010101010";
const String linea05 = "011111011101110101010";
const String linea06 = "010001010001000101010";
const String linea07 = "010111011101110111010";
const String linea08 = "010101000100010000010";
const String linea09 = "010101110111011101110";
const String linea10 = "000100010001000101000";
const String linea11 = "011101011101110101110";
const String linea12 = "010001000100010100010";
const String linea13 = "011101111111110101010";
const String linea14 = "000100000000000101010";
const String linea15 = "010111110111111101010";
const String linea16 = "010000010100000001010";
const String linea17 = "010111010111011111010";
const String linea18 = "010101010001010000010";
const String linea19 = "011101111101011111110";
const String linea20 = "000000000001000000000"; // exit
const String arr[21] = {linea00,linea01,linea02,linea03,linea04,linea05,linea06,linea07
                        ,linea08,linea09,linea10,linea11,linea12,linea13,linea14,linea15
                        ,linea16,linea17,linea18,linea19,linea20};
int startX,prevX ;
int startY ,prevY = 0 ;

void setup()
{
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  delay(10);
  digitalWrite(7, HIGH);
// Setup the LCD
  myGLCD.begin(R61581B);
  myGLCD.setRotation(3);
// Draw labirint  
  DrawLabyrint();
  // fake ald position
  prevX = startX;
  prevY = startY;
  // place player
  move(startX,startY);
  // initialize serial
  Serial.begin(9600);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    if (inChar == 'd')  move(prevX+1,prevY); // destra
    if (inChar == 's')  move(prevX-1,prevY); // sinistra
    if (inChar == 'a')  move(prevX,prevY-1); // alto
    if (inChar == 'b')  move(prevX,prevY+1); // basso
  }

}

void DrawLabyrint(){
  
  myGLCD.fillScreen(R61581_WHITE); // background

  for (int i = 0; i<20;i++){
    for (int x = 0; x < 20; x++){
      if (arr[x].charAt(i) == '1') {
        myGLCD.drawLine(i, x, i, x,R61581_BLACK);
        if (x == 0) startX = i; // start
      }
    }
  }
}

void loop()
{
  //runTime = millis();
  blinkPlayer();
  //move(prevX,prevY + 1);
  //move(prevX+1,prevY);
}

// TODO implement sizeof for more flexibility
bool canMove(int x, int y){
  if ((x < 1) || (x > 20)) return false;
  if ((y < 1) || (y > 20)) return false;
  
  if (prevX == x){
    //move Up Down
    return  (arr[y].charAt(prevX) == '1') ? true: false;
  }
  else if (prevY == y){
    //move Left Right
    return (arr[y].charAt(x) == '1') ? true: false;
  }
}

void blinkPlayer(){
  myGLCD.drawPixel(prevX, prevY,R61581_BLACK);
  delay(500);
  myGLCD.drawPixel(prevX, prevY,R61581_GREEN);
  delay(500);
}

void move(int x, int y){
  if (canMove(x,y)){
    myGLCD.drawPixel(prevX, prevY,R61581_BLACK);
    myGLCD.drawPixel(x, y,R61581_GREEN);
    prevX = x;
    prevY = y;
  }
}
