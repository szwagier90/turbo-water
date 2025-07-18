#ifndef I_SOIL_MOISTURE_SENSOR_H
#define I_SOIL_MOISTURE_SENSOR_H

class ISoilMoistureSensor
{
public:
    virtual int readPercent() const = 0;
};

#endif // I_SOIL_MOISTURE_SENSOR_H
