// checkWaterLevel.cpp
#include "checkWaterLevel.h"
#include <Arduino.h> // Include Arduino library for functions like digitalRead()

// Define any global variables used in the function
extern const int WaterLevelA;
extern const int WaterLevelB;
extern const int WaterLevelC;

void checkWaterLevel(int &waterLevelA, int &waterLevelB, int &waterLevelC) {
    // Read the value of the water level sensors
    waterLevelA = digitalRead(WaterLevelA);
    waterLevelB = digitalRead(WaterLevelB);
    waterLevelC = digitalRead(WaterLevelC);
}
