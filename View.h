#ifndef VIEW_H
#define VIEW_H

#include "LiquidCrystal_I2C.h"

class View {
public:
  View (
    LiquidCrystal_I2C & lcd,
    int & currentMenuItem,
    int & sensorValue,
    int & soilMoisturePercent,
    bool & pumpOutput
  );

  void lcdUpdate();

private:
  void sensorStatusView();

  LiquidCrystal_I2C & lcd;

  int & currentMenuItem;
  unsigned long lastADCViewUpdateTime;
  const unsigned long ADCViewUpdateInterval = 500; // 0.5 seconds
  int & sensorValue;
  int & soilMoisturePercent;
  bool & pumpOutput;
};

#endif
