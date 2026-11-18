#ifndef I_TIME_PROVIDER_H
#define I_TIME_PROVIDER_H

class ITimeProvider
{
public:
    virtual unsigned millis() const = 0;
    virtual ~ITimeProvider() = default;
};

#endif // I_TIME_PROVIDER_H
