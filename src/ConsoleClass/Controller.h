#ifndef CONTROLLER_H
#define CONTROLLER_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
 #include "pins_arduino.h"
#endif

#define BUT_UP 1
#define BUT_DOWN 2
#define BUT_LEFT 4
#define BUT_RIGHT 8
#define BUT_A 16
#define BUT_B 32
#define CONNECT1 64
#define CONNECT2 128


class Controller
{
  public:
    Controller();
    ~Controller();

    void setPressed(byte);
    void update();

    bool isPressed(byte);
    bool justPressed(byte);

    bool isConnected();

  private:
    byte m_pressed = 0;
    byte m_previousPressed = 0;
};

#endif
