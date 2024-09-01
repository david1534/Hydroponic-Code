#include "checkPumpStatus.h"
#include <Arduino.h>

void checkPumpStatus(WaterPumpFn &pumpFn, WaterLevelSensors &sensors) 
{
    pumpFn.elapsedTime = pumpFn.currentTime - pumpFn.previousTime;
    pumpFn.currentPumpTime = millis();
    pumpFn.elapsedPumpTime = pumpFn.currentPumpTime - pumpFn.previousPumpTime;

    if (sensors.waterLevelC == LOW) {
        digitalWrite(sensors.WaterPinD, HIGH);
        delay(300);
        digitalWrite(sensors.WaterPinD, LOW);
        delay(300);
        pumpFn.PumpPWM = 0;
        analogWrite(pumpFn.WaterPump, pumpFn.PumpPWM);
    } else if (pumpFn.pumpStatus && pumpFn.elapsedPumpTime <= pumpFn.pumpTimeOn) {
        if (sensors.waterLevelA == HIGH && pumpFn.elapsedTime >= pumpFn.stabilityTime) {
            pumpFn.PumpPWM = 255;
            pumpFn.previousTime = pumpFn.currentTime;
        } else if (sensors.waterLevelB == HIGH && pumpFn.elapsedTime >= pumpFn.stabilityTime) {
            pumpFn.PumpPWM = 170;
            pumpFn.previousTime = pumpFn.currentTime;
        } else if (sensors.waterLevelC == HIGH && pumpFn.elapsedTime >= pumpFn.stabilityTime) {
            pumpFn.PumpPWM = 85;
            pumpFn.previousTime = pumpFn.currentTime;
        } else if (sensors.waterLevelC == LOW && pumpFn.elapsedTime >= pumpFn.stabilityTime) {
            pumpFn.PumpPWM = 0;
            pumpFn.previousTime = pumpFn.currentTime;
        }
        analogWrite(pumpFn.WaterPump, pumpFn.PumpPWM);
    } else if (pumpFn.elapsedPumpTime >= pumpFn.pumpTimeOn) {
        digitalWrite(pumpFn.WaterPump, LOW);
        pumpFn.pumpStatus = false;
        pumpFn.previousPumpTime = pumpFn.currentPumpTime;
    } else if (pumpFn.elapsedPumpTime >= pumpFn.pumpTimeOff) {
        analogWrite(pumpFn.WaterPump, pumpFn.PumpPWM);
        pumpFn.pumpStatus = true;
        pumpFn.previousPumpTime = pumpFn.currentPumpTime;
    }
}

