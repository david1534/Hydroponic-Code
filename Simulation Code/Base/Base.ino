#include <Arduino.h>
#include "base.h"



Base base;

void setup() 
{
  Serial.begin(9600); // Start the serial communication with the computer
  // Set the mode of the pins
  pinMode(static_cast<int>(Base::WaterLevel::WaterLevelA), INPUT);
  pinMode(static_cast<int>(Base::WaterLevel::WaterLevelB), INPUT);
  pinMode(static_cast<int>(Base::WaterLevel::WaterLevelC), INPUT);
  pinMode(static_cast<int>(Base::WaterLevel::WaterLevelD), INPUT);
  pinMode(static_cast<int>(Base::Fans::FanA), OUTPUT);
  pinMode(static_cast<int>(Base::Fans::FanB), OUTPUT);
  pinMode(static_cast<int>(Base::WaterPumpConst::waterpumpval), OUTPUT);
}

void loop() 
{
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - base.previousTime;
  unsigned long currentPumpTime = millis();
  unsigned long elapsedPumpTime = currentPumpTime - base.previousPumpTime;

  base.checkWaterLevel(); // Check the current water level
  base.checkPumpStatus(currentTime, elapsedTime, currentPumpTime, elapsedPumpTime); // Check and update the pump status
}