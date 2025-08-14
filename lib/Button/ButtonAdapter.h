#ifndef BUTTON_ADAPTER_H
#define BUTTON_ADAPTER_H

#include "IButton.h"

#include <ezButton.h>

class ButtonAdapter : public IButton
{
public:
    ButtonAdapter(int buttonInputPin);

    void setDebounceTime(unsigned long) override;
    void loop() override;

private:
    ezButton button;
};

#endif // BUTTON_ADAPTER_H
