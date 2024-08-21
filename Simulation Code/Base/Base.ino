#include <Arduino.h>
#include "checkWaterLevel.h"
#include "checkPumpStatus.h"

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