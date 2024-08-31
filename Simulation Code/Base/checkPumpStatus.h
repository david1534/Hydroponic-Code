#ifndef CHECKPUMPSTATUS_H
#define CHECKPUMPSTATUS_H

#include "Arduino.h"
#include "checkWaterLevel.h"

// Function declaration that takes the structs as parameters
void checkPumpStatus(struct WaterPumpFn &pumpFn, struct WaterLevelSensors &sensors);

#endif
