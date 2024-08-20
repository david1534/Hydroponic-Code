#include <Arduino.h>
#include <Base.h>

Base Base()

void setup() 
{
  Serial.begin(9600); // Start the serial communication with the computer
  // Set the mode of the pins
  pinMode(WaterLevelA, INPUT);
  pinMode(WaterLevelB, INPUT);
  pinMode(WaterLevelC, INPUT);
  pinMode(WaterLevelD, OUTPUT);
  pinMode(FanA, OUTPUT);
  pinMode(FanB, OUTPUT);
  pinMode(WaterPump, OUTPUT);
}

void loop() 
{
  int waterLevelA, waterLevelB, waterLevelC; // Variables to store the current water level
  unsigned long currentTime, elapsedTime, currentPumpTime, elapsedPumpTime; // Variables to store the current time and elapsed time

  checkWaterLevel(waterLevelA, waterLevelB, waterLevelC); // Check the current water level
  checkPumpStatus(currentTime, elapsedTime, currentPumpTime, elapsedPumpTime, 
  waterLevelA, waterLevelB, waterLevelC); // Check and update the pump status
}