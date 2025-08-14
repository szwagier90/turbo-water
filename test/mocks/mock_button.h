#ifndef MOCK_BUTTON_H
#define MOCK_BUTTON_H

#include "IButton.h"

class MockButton : public IButton
{
public:
    MOCK_METHOD(void, setDebounceTime, (unsigned long), (override));
    MOCK_METHOD(void, loop, (), (override));
};

#endif // MOCK_BUTTON_H
