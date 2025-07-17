#ifndef APP_H
#define APP_H

#include "ISerial.h"
#include "ILcd.h"
#include "IDelay.h"
#include "IPump.h"

class App
{
public:
    App(
        ISerial& serial
        , ILcd& lcd
        , IDelay& delay
        , IPump& pump
    );
    void setup();
    void loop();

private:
    ISerial& serial;
    ILcd& lcd;
    IDelay& delay;
    IPump& pump;
};

#endif // APP_H
