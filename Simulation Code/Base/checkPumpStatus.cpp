#include <Arduino.h>
#include "checkPumpStatus.h"

CheckPumpStatus::CheckPumpStatus() {
  unsigned long previousTime = 0; 
  unsigned long previousPumpTime = 0;
  bool pumpStatus = false; 
  int PumpPWM = 0;
}

// Function to check and update the status of the pump
void CheckPumpStatus::checkPumpStatus(unsigned long &currentTime, unsigned long &elapsedTime, 
        unsigned long &currentPumpTime, unsigned long &elapsedPumpTime, int &waterLevelA, int &waterLevelB, int &waterLevelC, int &waterLevelD) { 
  if (waterLevelC == LOW)
  {
    digitalWrite(waterLevelD,HIGH);
    delay(300);
    digitalWrite(waterLevelD,LOW);
    delay(300);
    analogWrite(static_cast<int>(WaterPumpConst::waterpumpval), this->PumpPWM);
  }
  else if ((this->pumpStatus) && (elapsedPumpTime <= static_cast<int>(WaterPumpConst::pumpTimeOn))) // If the pump is currently on and has been on for less than the specified on time
  {
    // Check the water level and adjust the pump speed accordingly
    if ((waterLevelA == HIGH) && (elapsedTime >= static_cast<int>(WaterPumpConst::stabilityTime)))
    {
      this->PumpPWM = 255; // Set the pump speed to maximum
      this->previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((waterLevelB == HIGH) && (elapsedTime >= static_cast<int>(WaterPumpConst::stabilityTime)))
    {
      this->PumpPWM = 170; // Set the pump speed to medium-high
      this->previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((waterLevelC == HIGH) && (elapsedTime >= static_cast<int>(WaterPumpConst::stabilityTime)))
    {
      this->PumpPWM = 85; // Set the pump speed to medium-low
      this->previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((waterLevelC == LOW) && (elapsedTime >= static_cast<int>(WaterPumpConst::stabilityTime)))
    {
      this->PumpPWM = 0; // Turn off the pump
      this->previousTime = currentTime; // Update the time of the last water level check
    }
    analogWrite(static_cast<int>(WaterPumpConst::waterpumpval), this->PumpPWM); // Apply the new pump speed
  }
  else if (elapsedPumpTime >= static_cast<int>(WaterPumpConst::pumpTimeOn)) // If the pump has been on for more than the specified on time
  {
    digitalWrite(static_cast<int>(WaterPumpConst::waterpumpval), LOW); // Turn off the pump
    this->pumpStatus = false; // Update the pump status
    this->previousPumpTime = currentPumpTime; // Update the time of the last pump status check
  }
  else if (elapsedPumpTime >= static_cast<int>(WaterPumpConst::pumpTimeOff))// If the pump has been off for more than the specified off time
  {
    analogWrite(static_cast<int>(WaterPumpConst::waterpumpval), this->PumpPWM); // Turn on the pump
    this->pumpStatus = true; // Update the pump status
    this->previousPumpTime = currentPumpTime; // Update the time of the last pump status check
  }
}