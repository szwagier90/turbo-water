#ifndef VIEW_H
#define VIEW_H

#include "LiquidCrystal_I2C.h"

#define MENU_SIZE 2

struct MenuItem {
  String title;
  String templ;
};

class View {
public:
  enum Menu
  {
    SENSOR_STATUS,
    PUMP_STATUS,
  };

  View (
    int & newMenuItem,
    int & sensorValue,
    int & soilMoisturePercent,
    bool & pumpOutput
  );

  void lcdInit();
  void redrawMenu();
  void lcdUpdate();

private:
  void sensorStatusView();
  void pumpStatusView();

  LiquidCrystal_I2C lcd;

  int & newMenuItem;
  size_t currentMenuItem;
  unsigned long lastADCViewUpdateTime;
  const unsigned long ADCViewUpdateInterval = 500; // 0.5 seconds
  int & sensorValue;
  int & soilMoisturePercent;
  bool & pumpOutput;
};

#endif
