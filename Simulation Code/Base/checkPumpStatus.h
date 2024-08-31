#include <Arduino.h>
#ifndef BASE_H
#define BASE_H

class CheckPumpStatus {
    public:
        CheckPumpStatus();

        // Function to check and update the status of the pump
        void checkPumpStatus(unsigned long currentTime, unsigned long elapsedTime, 
        unsigned long currentPumpTime, unsigned long elapsedPumpTime);

        // Define the variables for the water pump
        enum class WaterPumpConst {
            stabilityTime = 1000, // Time in milliseconds to wait before changing the pump speed
            pumpTimeOff = 1000, // Time in milliseconds for the pump to stay off
            pumpTimeOn = 5000, // Time in milliseconds for the pump to stay on
            waterpumpval = 11, // Pin for the water pump
        };

        unsigned long previousTime = 0; // Variable to store the last time the water level was checked
        unsigned long previousPumpTime = 0; // Variable to store the last time the pump status was checked
        bool pumpStatus = false; // Variable to store the current status of the pump (true = on, false = off)
        int PumpPWM = 0; // Variable to control the speed of the water pump
};

#endif