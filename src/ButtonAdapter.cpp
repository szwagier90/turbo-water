#include "ButtonAdapter.h"

ButtonAdapter::ButtonAdapter(
    int buttonInputPin
)
    : button(buttonInputPin, INPUT_PULLUP)
{}

void ButtonAdapter::setDebounceTime(unsigned long)
{
    button.setDebounceTime(50);
}

void ButtonAdapter::loop()
{
    button.loop();
}
