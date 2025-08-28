#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include "IButtonController.h"

#include "IButton.h"

class ButtonController : public IButtonController
{
public:
    ButtonController(IButton& button);

    void setDebounceTime(unsigned long) override;
    void loop() override;
    bool isShortPressed() const override;

private:
    IButton& button;
};

#endif // BUTTON_CONTROLLER_H
