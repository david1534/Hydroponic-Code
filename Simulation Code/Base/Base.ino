#include <Arduino.h>
#include "checkWaterLevel.h"
#include "checkPumpStatus.h"


CheckWaterLevel cw;
CheckPumpStatus cs;

void setup() 
{
  Serial.begin(9600); // Start the serial communication with the computer
  // Set the mode of the pins
  pinMode(static_cast<int>(CheckWaterLevel::WaterLevel::WaterLevelA), INPUT);
  pinMode(static_cast<int>(CheckWaterLevel::WaterLevel::WaterLevelB), INPUT);
  pinMode(static_cast<int>(CheckWaterLevel::WaterLevel::WaterLevelC), INPUT);
  pinMode(static_cast<int>(CheckWaterLevel::WaterLevel::WaterLevelD), INPUT);
  // pinMode(static_cast<int>(Base::Fans::FanA), OUTPUT);
  // pinMode(static_cast<int>(Base::Fans::FanB), OUTPUT);
  pinMode(static_cast<int>(CheckPumpStatus::WaterPumpConst::waterpumpval), OUTPUT);
}

void loop() 
{
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - cs.previousTime;
  unsigned long currentPumpTime = millis();
  unsigned long elapsedPumpTime = currentPumpTime - cs.previousPumpTime;
  int waterLevelA, waterLevelB, waterLevelC, waterLevelD;

  cw.checkWaterLevel(waterLevelA, waterLevelB, waterLevelC, waterLevelD); // Check the current water level
  cs.checkPumpStatus(currentTime, elapsedTime, currentPumpTime, elapsedPumpTime, waterLevelA, waterLevelB, waterLevelC, waterLevelD); // Check and update the pump status
}