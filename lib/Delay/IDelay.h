#ifndef I_DELAY_H
#define I_DELAY_H

class IDelay
{
public:
    virtual void delay(unsigned long ms) = 0;
    virtual ~IDelay() = default;
};

#endif // I_DELAY_H
