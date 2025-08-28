#ifndef APP_H
#define APP_H

#include "ISerial.h"
#include "ILcd.h"
#include "IDelay.h"
#include "ISoilMoistureSensor.h"
#include "IPump.h"
#include "IButtonController.h"

class App
{
public:
    App(
        ISerial& serial
        , ILcd& lcd
        , IDelay& delay
        , ISoilMoistureSensor& s_m_sensor
        , IPump& pump
        , IButtonController& button
    );
    void setup();
    void loop();

private:
    ISerial& serial;
    ILcd& lcd;
    IDelay& delay;
    ISoilMoistureSensor& s_m_sensor;
    IPump& pump;
    IButtonController& button;
};

#endif // APP_H
