#include "App.h"

App::App(
    ISerial& serial
    , ILcd& lcd
    , IDelay& delay
    , ISoilMoistureSensor& s_m_sensor
    , IPump& pump
) :
    serial(serial)
    , lcd(lcd)
    , delay(delay)
    , s_m_sensor(s_m_sensor)
    , pump(pump)
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

    delay.delay(2000);
    lcd.clear();
};

void App::loop()
{
    if (s_m_sensor.isCalibrated())
    {
        if(s_m_sensor.readPercent() < 20)
            pump.on();
        else
            pump.off();
    }
}
