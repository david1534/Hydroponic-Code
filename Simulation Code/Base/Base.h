#include <Arduino.h>

class Base {
    Public:
        Base();

        // Function to check the current water level
        void checkWaterLevel(int &waterLevelA, int &waterLevelB, int &waterLevelC);

        // Function to check and update the status of the pump
        void checkPumpStatus(unsigned long &currentTime, unsigned long &elapsedTime, 
        unsigned long &currentPumpTime, unsigned long &elapsedPumpTime, int waterLevelA, 
        int waterLevelB, int waterLevelC);

        // Define the pins for the water level sensors
        const int WaterLevelA = 4;
        const int WaterLevelB = 5;
        const int WaterLevelC = 6;
        const int WaterLevelD = 7;

        // Define the pins for the fans
        const int FanA = 9;
        const int FanB = 10;
        int FanPWM; // Variable to control the speed of the fans

        // Define the variables for the water pump
        unsigned long previousTime = 0; // Variable to store the last time the water level was checked
        unsigned long previousPumpTime = 0; // Variable to store the last time the pump status was checked
        const unsigned long stabilityTime = 1000; // Time in milliseconds to wait before changing the pump speed
        bool pumpStatus = false; // Variable to store the current status of the pump (true = on, false = off)
        const unsigned long pumpTimeOff = 1000; // Time in milliseconds for the pump to stay off
        const unsigned long pumpTimeOn = 5000; // Time in milliseconds for the pump to stay on
        const int WaterPump = 11; // Pin for the water pump
        int PumpPWM; // Variable to control the speed of the water pump
};