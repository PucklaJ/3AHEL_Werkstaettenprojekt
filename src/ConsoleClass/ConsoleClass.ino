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
}

void loop()
{
  console.update();
  console.render();
}
