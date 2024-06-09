#ifndef MODEL_H
#define MODEL_H

enum Menu
{
  SENSOR_STATUS,
  SENSOR_CALIBRATION,
  PUMP_STATUS,
  FACTORY_RESET
};

const char * menu2str(int m);

struct Model
{
  unsigned moistureAdcValue;
  unsigned moisturePercent;
  bool pumpOnOffState;
};

#endif
