#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <math.h>

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
#define SPEED 0
#define BRIGHT 4.0
#define BUT1 45
#define BUT2 47
#define BUT3 49
#define BUT4 51
#define BLACK matrix.Color888(0,0,0)
#define RED matrix.Color888(64,0,0)
#define UP 6
#define DOWN 25
#define LEFT 6
#define RIGHT 25
#define MID 15
#define STEP 0.01
//#define CROSS

int pos[2] = {31,0};
double tick = 0.0;

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);                                                        

void setup()
{
  pinMode(BUT1,INPUT);
  pinMode(BUT2,INPUT);
  pinMode(BUT3,INPUT);
  pinMode(BUT4,INPUT);

  matrix.begin();
  
#ifdef CROSS
  matrix.fillScreen(RED);

  matrix.fillCircle(MID,MID,14,matrix.Color888(255,255,255));
  
  matrix.drawLine(LEFT,MID,RIGHT,MID,BLACK);
  matrix.drawLine(MID,UP,MID,DOWN,BLACK);
  matrix.drawLine(LEFT,UP,MID,UP,BLACK);
  matrix.drawLine(RIGHT,UP,RIGHT,MID,BLACK);
  matrix.drawLine(RIGHT,DOWN,MID,DOWN,BLACK);
  matrix.drawLine(LEFT,MID,LEFT,DOWN,BLACK);
#endif
}

void loop()
{ 
  #ifdef CROSS
  return;
  #endif
  
  
  if(digitalRead(BUT1) == LOW)
  {
    pos[1] += 1;
    if(pos[1] > 31)
      pos[1] = 0;
  }
  if(digitalRead(BUT2) == LOW)
  {
    pos[1] -= 1;
    if(pos[1] < 0)
      pos[1] = 31;
  }
  if(digitalRead(BUT3) == LOW)
  {
    pos[0] -= 1;
    if(pos[0] < 0)
      pos[0] = 31;
  }
  if(digitalRead(BUT4) == LOW)
  {
    pos[0] += 1;
    if(pos[0] > 31)
      pos[0] = 0;
  }

  tick+=STEP;

  

  matrix.fillScreen(matrix.Color888(255,255,255));

  matrix.drawPixel(pos[0],pos[1],0);

  delay(20);


 
  
  
}
