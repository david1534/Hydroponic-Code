// checkWaterLevel.cpp
#include "checkWaterLevel.h"
#include <Arduino.h> // Include Arduino library for functions like digitalRead()

void checkWaterLevel(int waterLevelA, int waterLevelB, int waterLevelC) {
    // Read the value of the water level sensors
    digitalRead(waterLevelA);
    digitalRead(waterLevelB);
    digitalRead(waterLevelC);
}
