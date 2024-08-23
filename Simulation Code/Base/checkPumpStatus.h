// checkPumpStatus.h
#ifndef CHECKPUMPSTATUS_H
#define CHECKPUMPSTATUS_H

void checkPumpStatus(unsigned long currentTime, unsigned long elapsedTime, 
                     unsigned long currentPumpTime, unsigned long elapsedPumpTime, 
                     int waterLevelA, int waterLevelB, int waterLevelC, int waterLevelD, int waterPump);

#endif
