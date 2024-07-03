#ifndef MODEL_H
#define MODEL_H

enum Menu
{
  SENSOR_STATUS,
  SENSOR_CALIBRATION,
  PUMP_STATUS,
  PUMP_CALIBRATION,
  FACTORY_RESET
};

const char * menu2str(int m);

struct Model
{
  unsigned moistureAdcValue;
  unsigned moisturePercent;
  unsigned short calibrationState;
  bool pumpOnOffState;
};

#endif
