#include "Plant.h"

Plant::Plant(
  int threshold,
  unsigned long act_time,
  unsigned long interval
) :
  soilMoistureThreshold(threshold),
  pumpActivationTime(act_time),
  pumpActivationStartTime(0),
  pumpIntervalTime(interval),
  pumpLastActivationTime(0) {};
