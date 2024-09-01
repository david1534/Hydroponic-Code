#include <Arduino.h>
#ifndef CHECKWATERLEVEL_H
#define CHECKWATERLEVEL_H

class CheckWaterLevel {
    public:
        CheckWaterLevel();

        // Function to check the current water level
        void checkWaterLevel(int &waterLevelA, int &waterLevelB, int &waterLevelC, int &waterLevelD);

        // Define the pins for the water level sensors
        enum class WaterLevel {
            WaterLevelA = 4,
            WaterLevelB = 5,
            WaterLevelC = 6,
            WaterLevelD = 7
        };
};

#endif