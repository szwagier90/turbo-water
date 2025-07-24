#ifndef I_SOIL_MOISTURE_SENSOR_H
#define I_SOIL_MOISTURE_SENSOR_H

class ISoilMoistureSensor
{
public:
    virtual bool isCalibrated() const = 0;

    virtual void calibrate() = 0;

    virtual int readPercent() const = 0;
};

#endif // I_SOIL_MOISTURE_SENSOR_H
