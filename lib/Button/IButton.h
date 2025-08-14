#ifndef I_BUTTON_H
#define I_BUTTON_H

class IButton
{
public:
    virtual void setDebounceTime(unsigned long) = 0;
    virtual void loop() = 0;
};

#endif // I_BUTTON_H
