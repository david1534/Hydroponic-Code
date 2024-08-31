#include <Arduino.h>
#include "checkWaterLevel.h"

// Function to check the current water level
void CheckWaterLevel::checkWaterLevel() {
  // Read the value of the water level sensors
  digitalRead(static_cast<int>(WaterLevel::WaterLevelA));
  digitalRead(static_cast<int>(WaterLevel::WaterLevelB));
  digitalRead(static_cast<int>(WaterLevel::WaterLevelC));
  digitalRead(static_cast<int>(WaterLevel::WaterLevelD));
}
