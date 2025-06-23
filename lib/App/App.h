#ifndef APP_H
#define APP_H

#include "ISerial.h"
#include "ILcd.h"
#include "IDelay.h"

class App
{
public:
    App(
        ISerial& serial,
        ILcd& lcd,
        IDelay& delay
    );
    void setup();

private:
    ISerial& serial;
    ILcd& lcd;
    IDelay& delay;
};

#endif // APP_H
