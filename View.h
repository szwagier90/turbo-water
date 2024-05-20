#ifndef VIEW_H
#define VIEW_H

#include "Model.h"
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
    Model & model,
    int & newMenuItem
  );

  void lcdInit();
  void redrawMenu();
  void lcdUpdate();

private:
  void initSplash();
  void sensorStatusView();
  void pumpStatusView();

  Model & model;
  LiquidCrystal_I2C lcd;

  int & newMenuItem;
  size_t currentMenuItem;
  unsigned long lastADCViewUpdateTime;
  const unsigned long ADCViewUpdateInterval = 500; // 0.5 seconds
  bool pumpOnOffState;
};

#endif
