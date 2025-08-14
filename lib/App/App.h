#ifndef APP_H
#define APP_H

#include "ISerial.h"
#include "ILcd.h"
#include "IDelay.h"
#include "ISoilMoistureSensor.h"
#include "IPump.h"
#include "IButton.h"

class App
{
public:
    App(
        ISerial& serial
        , ILcd& lcd
        , IDelay& delay
        , ISoilMoistureSensor& s_m_sensor
        , IPump& pump
        , IButton& button
    );
    void setup();
    void loop();

private:
    ISerial& serial;
    ILcd& lcd;
    IDelay& delay;
    ISoilMoistureSensor& s_m_sensor;
    IPump& pump;
    IButton& button;
};

#endif // APP_H
