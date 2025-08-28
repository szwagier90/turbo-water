#include "ButtonController.h"

ButtonController::ButtonController(
    IButton& button
)
    : button(button)
{}

void ButtonController::setDebounceTime(unsigned long)
{
    button.setDebounceTime(50);
}

void ButtonController::loop()
{
    button.loop();
}
