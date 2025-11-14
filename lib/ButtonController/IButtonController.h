#ifndef I_BUTTON_CONTROLLER_H
#define I_BUTTON_CONTROLLER_H

class IButtonController
{
public:
    virtual void setDebounceTime(unsigned long) = 0;
    virtual void loop() = 0;
    virtual bool isShortPressed() const = 0;
};

#endif // I_BUTTON_CONTROLLER_H
