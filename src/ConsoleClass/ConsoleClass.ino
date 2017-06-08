//We always have to include the library
#include "LedControl.h"
#define TEST
#ifdef TEST

#define CON_SER1 35
#define CON_SER2 36
#define CON_SER3 22
#define CON_SER4 30
#define CON_CLK 34
#define CON_PL 33

void setup()
{
  pinMode(CON_SER1,INPUT);
  digitalWrite(CON_PL,LOW);
  pinMode(CON_PL,OUTPUT);
  digitalWrite(CON_CLK,LOW);
  pinMode(CON_CLK,OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  byte data = 0;

  digitalWrite(CON_PL,LOW);
  digitalWrite(CON_PL,HIGH);

  data = shiftIn(CON_SER1,CON_CLK,MSBFIRST);

  Serial.println(data,BIN);
}
#else
#include "Console.h"
#include "Game.h"
#include "TankGame.h"

#define TANK_GAME_INDEX 0

Console console;
TankGameWrapper tankGame(&console);


void setup()
{
  console.setGame(TANK_GAME_INDEX,&tankGame);
  console.init();
  Serial.println("Starting Up...");
}

void loop()
{
  console.update();
  console.render();
}
#endif
