#include "App.h"

App::App(
    ISerial& serial
    , ILcd& lcd
    , IDelay& delay
    , ISoilMoistureSensor& s_m_sensor
    , IPump& pump
    , IButtonController& button
) :
    serial(serial)
    , lcd(lcd)
    , delay(delay)
    , s_m_sensor(s_m_sensor)
    , pump(pump)
    , button(button)
{}

void App::setup() {
    serial.begin(115200);
    serial.println("SERIAL_INIT");

    lcd.init(4, 5);
    lcd.backlight();
    lcd.print(" PLANT WATERING ");
    lcd.setCursor(0,1);
    lcd.print("     SYSTEM     ");
    serial.println("LCD Initialization");

    button.setDebounceTime(50);
    delay.delay(2000);
    lcd.clear();
};

void App::loop()
{
    int sensorValue;

    button.loop(); // MUST call the loop() function first

    if(button.isShortPressed())
    {
        sensorValue = s_m_sensor.readRaw();

        if(0 == sensorReadCounter)
            dry = sensorValue;
        else if(1 == sensorReadCounter)
        {
            wet = sensorValue;
            s_m_sensor.calibrate(dry, wet);
        }

        sensorReadCounter++;
    }

    if (s_m_sensor.isCalibrated())
    {
        if(s_m_sensor.readPercent() < 20)
            pump.on();
        else
            pump.off();
    }
}
