#ifndef I_TIME_PROVIDER_H
#define I_TIME_PROVIDER_H

class IMockTimeProvider
{
public:
    virtual unsigned millis() const = 0;
    virtual ~IMockTimeProvider() = default;
};

#endif // I_TIME_PROVIDER_H
