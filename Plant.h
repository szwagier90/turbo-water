#ifndef PLANT_H
#define PLANT_H

struct Plant
{
  Plant(
    int threshold = 30,
    unsigned long act_time = 5000,
    unsigned long interval = 10000
  );

  const int soilMoistureThreshold;

  const unsigned long pumpActivationTime;
  unsigned long pumpActivationStartTime;

  const unsigned long pumpIntervalTime;
  unsigned long pumpLastActivationTime;
};

#endif
