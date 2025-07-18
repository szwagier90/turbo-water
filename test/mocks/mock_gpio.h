#ifndef MOCK_GPIO_H
#define MOCK_GPIO_H

#include "IGpio.h"

#include <stdint.h>


class MockGpio : public IGpio
{
public:
    MOCK_METHOD(void, pinMode, (uint8_t pin, PinMode mode), (override));
    MOCK_METHOD(void, digitalWrite, (uint8_t pin, PinOutput mode), (override));
};

#endif // MOCK_GPIO_H
