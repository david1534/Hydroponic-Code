#include "checkWaterLevel.h"
#include <Arduino.h>

void checkWaterLevel(WaterLevelSensors &sensors) {
  sensors.waterLevelA = digitalRead(sensors.WaterPinA);
  sensors.waterLevelB = digitalRead(sensors.WaterPinB);
  sensors.waterLevelC = digitalRead(sensors.WaterPinC);
}
