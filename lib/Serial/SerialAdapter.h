#ifndef SERIAL_ADAPTER_H
#define SERIAL_ADAPTER_H

#include "ISerial.h"

#include <Arduino.h>

class SerialAdapter : public ISerial
{
public:
    void begin(unsigned long baud) override
    {
        Serial.begin(baud);
    };

    void println(const char* msg) override
    {
        Serial.println(msg);
    };
};

#endif // SERIAL_ADAPTER_H
