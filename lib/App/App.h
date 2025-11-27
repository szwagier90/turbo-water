#ifndef APP_H
#define APP_H

#include "ISerial.h"
#include "ILcd.h"
#include "IDelay.h"
#include "IMockTimeProvider.h"
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
        , IMockTimeProvider& timeProvider
        , ISoilMoistureSensor& s_m_sensor
        , IPump& pump
        , IButtonController& button
    );
    void setup();
    void loop();

    float getPumpFlowA();
    float getPumpFlowB();

    void setPumpFlowAB(float a, float b);

    const float vol1 = 200;
    const float vol2 = 500;

    uint8_t runIndex = 0;

    uint32_t startMs = 0;
    uint32_t duration1 = 0;
    uint32_t duration2 = 0;

    float pumpFlowA = 0.0f;
    float pumpFlowB = 0.0f;

private:
    void calculatePumpCalibration();

    ISerial& serial;
    ILcd& lcd;
    IDelay& delay;
    IMockTimeProvider& timeProvider;
    ISoilMoistureSensor& s_m_sensor;
    IPump& pump;
    IButtonController& button;

    short sensorReadCounter = 0;
    int dry;
    int wet;
};

#endif // APP_H
