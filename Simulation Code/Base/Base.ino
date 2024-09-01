#include <Arduino.h>
#include "checkWaterLevel.h"
#include "checkPumpStatus.h"

// Create instances of the structs
WaterLevelSensors waterLevelSensors;
WaterPumpFn waterPumpFn;

void setup() 
{
  Serial.begin(9600); // Start the serial communication with the computer

  // Set the mode of the pins using the struct instances
  pinMode(waterLevelSensors.WaterPinA, INPUT);
  pinMode(waterLevelSensors.WaterPinB, INPUT);
  pinMode(waterLevelSensors.WaterPinC, INPUT);
  pinMode(waterLevelSensors.WaterPinD, OUTPUT);
  pinMode(waterPumpFn.WaterPump, OUTPUT);
}

void loop() 
{
  // Update the current time in the waterPumpFn struct
  waterPumpFn.currentTime = millis();

  // Check the current water level
  checkWaterLevel(waterLevelSensors);

  // Check and update the pump status
  checkPumpStatus(waterPumpFn, waterLevelSensors);
}


