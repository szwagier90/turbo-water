#ifndef MOCK_GPIO_H
#define MOCK_GPIO_H

#include "IGpio.h"

#include <stdint.h>


class MockGpio : public IGpio
{
public:
    MOCK_METHOD(void, pinMode, (uint8_t pin, PinMode mode), (override));
};

#endif // MOCK_GPIO_H
