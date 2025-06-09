#ifdef ARDUINO
#include <Arduino.h>

#include <App.h>

App app(
);

void setup()
{
}

void loop()
{
}

#else
// If compiled for native testing, provide an alternative entry point
#include <iostream>

int main()
{
    std::cout << "Running in native environment. No Arduino setup needed.\n";
    return 0;
}
#endif
