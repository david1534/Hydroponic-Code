#include <Arduino.h>
#include "checkWaterLevel.h"
#include "checkPumpStatus.h"

// Define the structs

struct WaterLevelSensors {
  const int WaterPinA = 4;
  const int WaterPinB = 5;
  const int WaterPinC = 6;
  const int WaterPinD = 7;
  int waterLevelA;
  int waterLevelB;
  int waterLevelC;
  int waterLevelD;
};

struct Fans {
  const int FanA = 9;
  const int FanB = 10;
  int FanPWM;
};

struct WaterPumpFn {
  unsigned long previousTime = 0;
  unsigned long previousPumpTime = 0;
  const unsigned long stabilityTime = 1000;
  bool pumpStatus = false;
  const unsigned long pumpTimeOff = 1000;
  const unsigned long pumpTimeOn = 5000;
  const int WaterPump = 11;
  int PumpPWM;
  unsigned long currentTime, elapsedTime, currentPumpTime, elapsedPumpTime;
};

// Create instances of the structs
WaterLevelSensors waterLevelSensors;
Fans fans;
WaterPumpFn waterPumpFn;

void setup() 
{
  Serial.begin(9600);

  // Set the mode of the pins using the struct instances
  pinMode(waterLevelSensors.WaterPinA, INPUT);
  pinMode(waterLevelSensors.WaterPinB, INPUT);
  pinMode(waterLevelSensors.WaterPinC, INPUT);
  pinMode(waterLevelSensors.WaterPinD, OUTPUT);
  pinMode(fans.FanA, OUTPUT);
  pinMode(fans.FanB, OUTPUT);
  pinMode(waterPumpFn.WaterPump, OUTPUT);
}

void loop() 
{
  waterPumpFn.currentTime = millis();

  // Check the current water level
  checkWaterLevel(waterLevelSensors);

  // Check and update the pump status
  checkPumpStatus(waterPumpFn, waterLevelSensors);
}
