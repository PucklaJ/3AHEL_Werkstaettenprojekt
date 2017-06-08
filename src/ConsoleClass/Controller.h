#ifndef CONTROLLER_H
#define CONTROLLER_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
 #include "pins_arduino.h"
#endif

#define BUT_UP 2
#define BUT_DOWN 1
#define BUT_LEFT 4
#define BUT_RIGHT 8
#define BUT_A 32
#define BUT_B 16
#define CONNECT1 64
#define CONNECT2 128


class Controller
{
  public:
    Controller();
    ~Controller();

    void setPressed(byte);
    void update();

    bool isPressed(byte) const;
    bool justPressed(byte) const;

    bool isConnected() const;

  private:
    byte m_pressed = 0;
    byte m_previousPressed = 0;
};

#endif
