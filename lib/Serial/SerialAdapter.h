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
};

#endif // SERIAL_ADAPTER_H
