#include "Model.h"

const char * menu2str(int m)
{
  switch(m)
  {
    case SENSOR_STATUS:
      return "SENSOR_STATUS";
    case PUMP_STATUS:
      return "PUMP_STATUS";
    default:
      return "UNKNOWN";
  }
}
