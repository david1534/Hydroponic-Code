#include "checkWaterLevel.h"
#include <Arduino.h>

void checkWaterLevel(WaterLevelSensors &sensors) {
  // Read the value of the water level sensors and store them in the struct
  sensors.waterLevelA = digitalRead(sensors.WaterPinA);
  sensors.waterLevelB = digitalRead(sensors.WaterPinB);
  sensors.waterLevelC = digitalRead(sensors.WaterPinC);
}
