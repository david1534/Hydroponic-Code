// checkPumpStatus.cpp
#include "checkPumpStatus.h"
#include <Arduino.h> // Include Arduino library for functions like millis()

// Define any global variables used in the function
extern unsigned long previousTime;
extern unsigned long previousPumpTime;
extern int PumpPWM;
extern bool pumpStatus;
extern const unsigned long pumpTimeOn;
extern const unsigned long pumpTimeOff;
extern const unsigned long stabilityTime;

void checkPumpStatus(unsigned long currentTime, unsigned long elapsedTime, 
                     unsigned long currentPumpTime, unsigned long elapsedPumpTime, 
                     int waterLevelA, int waterLevelB, int waterLevelC, int waterLevelD, int WaterPump) 
{
    currentTime = millis(); // Get the current time
    elapsedTime = currentTime - previousTime; // Calculate how much time has passed since the last water level check
    currentPumpTime = millis(); // Get the current time
    elapsedPumpTime = currentPumpTime - previousPumpTime; // Calculate how much time has passed since the last pump status check

    if (waterLevelC == LOW) {
        digitalWrite(waterLevelD, HIGH);
        delay(300);
        digitalWrite(waterLevelD, LOW);
        delay(300);
        PumpPWM = 0;
        analogWrite(WaterPump, PumpPWM);
    } else if ((pumpStatus) && (elapsedPumpTime <= pumpTimeOn)) {
        // Check the water level and adjust the pump speed accordingly
        if ((waterLevelA == HIGH) && (elapsedTime >= stabilityTime)) {
            PumpPWM = 255; // Set the pump speed to maximum
            previousTime = currentTime; // Update the time of the last water level check
        } else if ((waterLevelB == HIGH) && (elapsedTime >= stabilityTime)) {
            PumpPWM = 170; // Set the pump speed to medium-high
            previousTime = currentTime; // Update the time of the last water level check
        } else if ((waterLevelC == HIGH) && (elapsedTime >= stabilityTime)) {
            PumpPWM = 85; // Set the pump speed to medium-low
            previousTime = currentTime; // Update the time of the last water level check
        } else if ((waterLevelC == LOW) && (elapsedTime >= stabilityTime)) {
            PumpPWM = 0; // Turn off the pump
            previousTime = currentTime; // Update the time of the last water level check
        }
        analogWrite(WaterPump, PumpPWM); // Apply the new pump speed
    } else if (elapsedPumpTime >= pumpTimeOn) {
        digitalWrite(WaterPump, LOW); // Turn off the pump
        pumpStatus = false; // Update the pump status
        previousPumpTime = currentPumpTime; // Update the time of the last pump status check
    } else if (elapsedPumpTime >= pumpTimeOff) {
        analogWrite(WaterPump, PumpPWM); // Turn on the pump
        pumpStatus = true; // Update the pump status
        previousPumpTime = currentPumpTime; // Update the time of the last pump status check
    }
}
