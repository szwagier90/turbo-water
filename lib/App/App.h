#ifndef APP_H
#define APP_H

#include "ISerial.h"

class App
{
public:
    App(ISerial& serial);

private:
    ISerial& serial;
};

#endif // APP_H
