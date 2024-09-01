#include <Arduino.h>
#include "checkWaterLevel.h"

CheckWaterLevel::CheckWaterLevel() {

}

// Function to check the current water level
void CheckWaterLevel::checkWaterLevel(int &waterLevelA, int &waterLevelB, int &waterLevelC, int &waterLevelD) {
  // Read the value of the water level sensors
  waterLevelA = digitalRead(static_cast<int>(WaterLevel::WaterLevelA));
  waterLevelB = digitalRead(static_cast<int>(WaterLevel::WaterLevelB));
  waterLevelC = digitalRead(static_cast<int>(WaterLevel::WaterLevelC));
  waterLevelD = digitalRead(static_cast<int>(WaterLevel::WaterLevelD));
}
