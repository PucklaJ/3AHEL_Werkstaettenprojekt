#include "Console.h"
#include <math.h>
#include "Game.h"


Console::Console() : RGBmatrixPanel::RGBmatrixPanel(MATRIX_A,MATRIX_B,MATRIX_C,MATRIX_D,MATRIX_SCLK,MATRIX_LAT,MATRIX_OE,false)
{
  for(int i = 0;i<NUM_GAMES;i++)
  {
    m_games[i] = nullptr;
  }
}

Console::~Console()
{
  quit();
}

void Console::init()
{
  initPins();
  initMAX();
	begin();
  

  Serial.begin(9600);
  
  readBrightness();

  testStartup();

  for(int i = 0;i<NUM_GAMES;i++)
  {
    m_games[i]->menu_init();
  }
}

void Console::initMAX()
{
  m_ledControl = new LedControl(MAX_DATA,MAX_CLK,MAX_CS,1);
  m_ledControl->shutdown(0,false);
  m_ledControl->setIntensity(0,15);

  for(int i=0;i<13;i++) {
    m_ledControl->setDigit(0,7,i,false);
    m_ledControl->setDigit(0,6,i+1,false);
    m_ledControl->setDigit(0,5,i+2,false);
    m_ledControl->setDigit(0,4,i+3,false);
    m_ledControl->setDigit(0,3,i+4,false);
    m_ledControl->setDigit(0,2,i+5,false);
    m_ledControl->setDigit(0,1,i+6,false);
    m_ledControl->setDigit(0,0,i+7,false);
    delay(400);
  }
}

void Console::initPins()
{
  pinMode(BRIGHT_POTI,INPUT);
  pinMode(CON_SER1,INPUT);
  pinMode(CON_SER2,INPUT);
  pinMode(CON_SER3,INPUT);
  pinMode(CON_SER4,INPUT);
  digitalWrite(CON_CLK,LOW);
  pinMode(CON_CLK,OUTPUT);
  digitalWrite(CON_PL,HIGH);
  pinMode(CON_PL,OUTPUT);
}

void Console::update()
{
  readBrightness();
  readInput();

  updateGames();

  if(m_curState == MENU_STATE)
    menuControl();
  else
    playControl();

  for(int i = 0;i<4;i++)
  {
    m_controllers[i].update();
  }
}

void Console::render()
{
  renderGames();
}

void Console::updateGames()
{
  if(m_curState == MENU_STATE)
  {
    if(m_games[m_curGame])
    {
      m_games[m_curGame]->menu_update();
    }
  }
  else
  {
    if(m_games[m_curGame])
    {
      m_games[m_curGame]->update();
    }
  }
}

void Console::renderGames()
{
  if(m_curState == MENU_STATE)
  {
    if(m_games[m_curGame])
    {
      m_games[m_curGame]->menu_render();
    }
  }
  else
  {
    if(m_games[m_curGame])
    {
      m_games[m_curGame]->render();
    }
  }
}

void Console::menuControl()
{
  byte control = 0;

  for(int i = 0;i<4;i++)
  {
    if(false && m_controllers[i].justPressed(BUT_LEFT))
    {
      control = 1;
      break;
    }
    else if(false && m_controllers[i].justPressed(BUT_RIGHT))
    {
      control = 2;
      break;
    }
    else if(true || m_controllers[i].justPressed(BUT_A))
    {
      control = 3;
      break;
    }
  }

  if(control == 1)
  {
    if(m_curGame == 0)
      m_curGame = NUM_GAMES-1;
    else
      m_curGame--;
  }
  else if(control == 2)
  {
    if(m_curGame == NUM_GAMES-1)
      m_curGame = 0;
    else
      m_curGame++;
  }
  else if(control == 3)
  {
    switchState(PLAY_STATE);
  }
}

void Console::playControl()
{
  for(int i = 0;i<4;i++)
  {
    if(m_controllers[i].isConnected())
      return;
  }

  switchState(MENU_STATE);
}

void Console::quit()
{
  if(m_curState == MENU_STATE)
  {
    if(m_games[m_curGame])
    {
      m_games[m_curGame]->menu_quit();
    }
  }
  else
  {
    if(m_games[m_curGame])
    {
      m_games[m_curGame]->quit();
    }
  }
  
  delete m_ledControl;
}

void Console::switchState(byte state)
{
  if(m_curState == MENU_STATE)
  {
    for(int i = 0;i<NUM_GAMES;i++)
    {
      m_games[i]->menu_quit();
    }
  }
  else
  {
    m_games[m_curGame]->quit();
  }
  
  m_curState = state;

  if(state == MENU_STATE)
  {
    for(int i = 0;i<NUM_GAMES;i++)
    {
      m_games[i]->menu_init();
    }
  }
  else
  {
    m_games[m_curGame]->init();
  }
}

void Console::testStartup()
{
  fillScreen(this->Color(WHITE));
  //for(int i = 0;i<8;i++)
  //{
  //  m_ledControl->setDigit(0,8,i,false);
  //}

  delay(1000);
  fillScreen(this->Color(BLACK));
  m_ledControl->clearDisplay(0);
  
}

float Console::getBrightness() const
{
  return m_brightness;
}

void Console::readBrightness()
{
  m_brightness = (float)analogRead(BRIGHT_POTI)/1024.0f;
}

void Console::readInput()
{
  // Load the button states into shift register
  digitalWrite(CON_PL,LOW);
  digitalWrite(CON_PL,HIGH);

  byte data = 0;

  // Loop through all controllers and shift the data in
  for(int i = 0;i<4;i++)
  {
    data = 0;
    data = shiftIn((i == 0 ? CON_SER1 : (i == 1 ? CON_SER2 : (i == 2 ? CON_SER3 : CON_SER4))),CON_CLK,MSBFIRST);

    m_controllers[i].setPressed(data);
  }
}

void Console::setScoreString(byte digit,const char* letter)
{
  if(digit > 4)
    return;
    
  m_ledControl->setChar(0,(int)digit*2,letter[1],false);
  m_ledControl->setChar(0,(int)digit*2+1,letter[0],false);
}

void Console::setScoreNumber(byte digit,unsigned int number)
{
  if(digit > 4 || number > 99)
    return;
    
  m_ledControl->setDigit(0,(int)digit*2,((int)(number / pow(10,0))) % 10,false);
  m_ledControl->setDigit(0,(int)digit*2+1,((int)(number / pow(10,1))) % 10,false);
}

uint16_t Console::Color(float r,float g,float b)
{
  return Color888((uint8_t)(r*m_brightness),(uint8_t)(g*m_brightness),(uint8_t)(b*m_brightness));
}

uint16_t Console::Color(const ColorRGB& col)
{
  return Color(col.r,col.g,col.b);
}

void Console::setGame(byte index,Game* game)
{
  if(index > NUM_GAMES-1)
    return;

   m_games[index] = game;
}

