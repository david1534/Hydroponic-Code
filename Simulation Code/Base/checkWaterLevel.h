#ifndef CHECKWATERLEVEL_H
#define CHECKWATERLEVEL_H

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

void checkWaterLevel(WaterLevelSensors &sensors);

#endif
