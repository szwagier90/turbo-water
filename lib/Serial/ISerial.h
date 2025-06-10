#ifndef I_SERIAL_H
#define I_SERIAL_H

class ISerial
{
public:
    virtual void begin(unsigned long baud) = 0;
    virtual void println(const char* msg) = 0;
    virtual ~ISerial() = default;
};

#endif // I_SERIAL_H
