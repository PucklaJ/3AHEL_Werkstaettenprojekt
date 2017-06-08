#ifndef CONSOLE_H
#define CONSOLE_H
#include <RGBmatrixPanel.h>
#include <LedControl.h>
#include "Controller.h"

#define MATRIX_A A0
#define MATRIX_B A1
#define MATRIX_C A2
#define MATRIX_D A3
#define MATRIX_SCLK 11
#define MATRIX_LAT 10
#define MATRIX_OE 9

#define MAX_DATA 23
#define MAX_CLK 32
#define MAX_CS 31

#define BRIGHT_POTI A4

#define CON_SER1 35
#define CON_SER2 36
#define CON_SER3 22
#define CON_SER4 30
#define CON_CLK 34
#define CON_PL 33

#define WHITE 255,255,255
#define BLACK 0,0,0
#define RED 255,0,0
#define GREEN 0,255,0
#define BLUE 0,0,255
#define YELLOW 255,255,0
#define PINK_COLOR 255,20,147
#define BROWN 139,69,19

#ifndef NUM_GAMES
  #define NUM_GAMES 1
#endif

#define MENU_STATE 0
#define PLAY_STATE 1

class Game;

struct Vec2
{
  int x;
  int y;
};

struct ColorRGB
{
  uint8_t r;
  uint8_t g;
  uint8_t b;

  ColorRGB(uint8_t _r,uint8_t _g,uint8_t _b)
  {
    r = _r;
    g = _g;
    b = _b;
  }
  ColorRGB()
  {
    r = 0;
    g = 0;
    b = 0;
  }
};

class Console : public RGBmatrixPanel
{
	public:
		Console();
		~Console();


  	void init();
  	void update();
  	void render();
  	void quit();
  
    void setScoreString(byte,const char*);
    void setScoreNumber(byte,unsigned int);

    float getBrightness() const;

    uint16_t Color(float,float,float);
    uint16_t Color(const ColorRGB&);

    const Controller& getController(byte c) const {return m_controllers[c];}
    LedControl* getMAX() {return m_ledControl;}

    void setGame(byte,Game*);

  private:
    void initMAX();
    void initPins();
    void testStartup();
    void readBrightness();
    void readInput();
    void switchState(byte);

    void menuControl();
    void playControl();
    void updateGames();
    void renderGames();
  
    LedControl* m_ledControl = nullptr;
    float m_brightness = 1.0f;
    Controller m_controllers[4];
    Game* m_games[NUM_GAMES];
    long m_curGame = 0;
    byte m_curState = MENU_STATE;
};


#endif
