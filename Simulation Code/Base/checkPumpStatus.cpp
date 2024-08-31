#include <Arduino.h>
#include "base.h"

// Function to check and update the status of the pump
void Base::checkPumpStatus(unsigned long currentTime, unsigned long elapsedTime, 
unsigned long currentPumpTime, unsigned long elapsedPumpTime)
{ 
  if (static_cast<int>(WaterLevel::WaterLevelC) == LOW)
  {
    digitalWrite(static_cast<int>(WaterLevel::WaterLevelD),HIGH);
    delay(300);
    digitalWrite(static_cast<int>(WaterLevel::WaterLevelD),LOW);
    delay(300);
    analogWrite(static_cast<int>(WaterPumpConst::waterpumpval), PumpPWM);
  }
  else if ((this->pumpStatus) && (elapsedPumpTime <= static_cast<int>(WaterPumpConst::pumpTimeOn))) // If the pump is currently on and has been on for less than the specified on time
  {
    // Check the water level and adjust the pump speed accordingly
    if ((static_cast<int>(WaterLevel::WaterLevelA) == HIGH) && (elapsedTime >= static_cast<int>(WaterPumpConst::stabilityTime)))
    {
      this->PumpPWM = 255; // Set the pump speed to maximum
      this->previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((static_cast<int>(WaterLevel::WaterLevelB) == HIGH) && (elapsedTime >= static_cast<int>(WaterPumpConst::stabilityTime)))
    {
      this->PumpPWM = 170; // Set the pump speed to medium-high
      this->previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((static_cast<int>(WaterLevel::WaterLevelC) == HIGH) && (elapsedTime >= static_cast<int>(WaterPumpConst::stabilityTime)))
    {
      this->PumpPWM = 85; // Set the pump speed to medium-low
      this->previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((static_cast<int>(WaterLevel::WaterLevelC) == LOW) && (elapsedTime >= static_cast<int>(WaterPumpConst::stabilityTime)))
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