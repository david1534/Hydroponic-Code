#include <Arduino.h>
#include <Base.h>

// Function to check the current water level
void checkWaterLevel(int &waterLevelA, int &waterLevelB, int &waterLevelC) 
{
  // Read the value of the water level sensors
  waterLevelA = digitalRead(WaterLevelA);
  waterLevelB = digitalRead(WaterLevelB);
  waterLevelC = digitalRead(WaterLevelC);
}

// Function to check and update the status of the pump
void checkPumpStatus(unsigned long &currentTime, unsigned long &elapsedTime, 
unsigned long &currentPumpTime, unsigned long &elapsedPumpTime, int waterLevelA, 
int waterLevelB, int waterLevelC) 
{
  currentTime = millis(); // Get the current time
  elapsedTime = currentTime - previousTime; // Calculate how much time has passed since the last water level check
  currentPumpTime = millis(); // Get the current time
  elapsedPumpTime = currentPumpTime - previousPumpTime; // Calculate how much time has passed since the last pump status check
  if (waterLevelC == LOW)
  {
    digitalWrite(WaterLevelD,HIGH);
    delay(300);
    digitalWrite(WaterLevelD,LOW);
    delay(300);
    PumpPWM = 0;
    analogWrite(WaterPump, PumpPWM);
  }
  else if ((pumpStatus) && (elapsedPumpTime <= pumpTimeOn)) // If the pump is currently on and has been on for less than the specified on time
  {
    // Check the water level and adjust the pump speed accordingly
    if ((waterLevelA == HIGH) && (elapsedTime >= stabilityTime))
    {
      PumpPWM = 255; // Set the pump speed to maximum
      previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((waterLevelB == HIGH) && (elapsedTime >= stabilityTime))
    {
      PumpPWM = 170; // Set the pump speed to medium-high
      previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((waterLevelC == HIGH) && (elapsedTime >= stabilityTime))
    {
      PumpPWM = 85; // Set the pump speed to medium-low
      previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((waterLevelC == LOW) && (elapsedTime >= stabilityTime))
    {
      PumpPWM = 0; // Turn off the pump
      previousTime = currentTime; // Update the time of the last water level check
    }
    analogWrite(WaterPump, PumpPWM); // Apply the new pump speed
  }
  else if (elapsedPumpTime >= pumpTimeOn) // If the pump has been on for more than the specified on time
  {
    digitalWrite(WaterPump, LOW); // Turn off the pump
    pumpStatus = false; // Update the pump status
    previousPumpTime = currentPumpTime; // Update the time of the last pump status check
  }
  else if (elapsedPumpTime >= pumpTimeOff)// If the pump has been off for more than the specified off time
  {
    analogWrite(WaterPump, PumpPWM); // Turn on the pump
    pumpStatus = true; // Update the pump status
    previousPumpTime = currentPumpTime; // Update the time of the last pump status check
  }
}