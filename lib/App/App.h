#ifndef APP_H
#define APP_H

#include "ISerial.h"
#include "ILcd.h"

class App
{
public:
    App(
        ISerial& serial
        , ILcd& lcd
    );
    void setup();
    void loop();

private:
    ISerial& serial;
    ILcd& lcd;
};

#endif // APP_H
