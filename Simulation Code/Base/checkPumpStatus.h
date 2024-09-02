#ifndef CHECKPUMPSTATUS_H
#define CHECKPUMPSTATUS_H

#include "checkWaterLevel.h"

struct WaterPumpFn {
  unsigned long previousTime = 0;
  unsigned long previousPumpTime = 0;
  const unsigned long stabilityTime = 1000;
  bool pumpStatus = false;
  const unsigned long pumpTimeOff = 1000;
  const unsigned long pumpTimeOn = 5000;
  const int WaterPump = 11;
  int PumpPWM;
  unsigned long currentTime, elapsedTime, currentPumpTime, elapsedPumpTime;
};

void checkPumpStatus(WaterPumpFn &pumpFn, WaterLevelSensors &sensors);

#endif

