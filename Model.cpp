#include "Model.h"

const char * menu2str(int m)
{
  switch(m)
  {
    case SENSOR_STATUS:
      return "SENSOR_STATUS";
    case SENSOR_CALIBRATION:
      return "SENSOR_CALIBRATION";
    case PUMP_STATUS:
      return "PUMP_STATUS";
    case PUMP_CALIBRATION:
      return "PUMP_CALIBRATION";
    case FACTORY_RESET:
      return "FACTORY_RESET";
    default:
      return "UNKNOWN";
  }
}
