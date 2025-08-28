#ifndef MOCK_BUTTON_CONTROLLER_H
#define MOCK_BUTTON_CONTROLLER_H

#include "IButtonController.h"

class MockButtonController : public IButtonController
{
public:
    MOCK_METHOD(void, setDebounceTime, (unsigned long), (override));
    MOCK_METHOD(void, loop, (), (override));

    MOCK_METHOD(bool, isShortPressed, (), (const override));
};

#endif // MOCK_BUTTON_CONTROLLER_H
