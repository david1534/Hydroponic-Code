#include <Arduino.h>

// Define the pins for the water level sensors and other components
//
const int WaterLevelA = 4;
const int WaterLevelB = 5;
const int WaterLevelC = 6;
const int WaterLevelD = 7;
const int FanA = 9;
const int FanB = 10;
const int WaterPump = 11;

// Define a structure for water level sensors
struct WaterLevelSensors {
    int pinA;
    int pinB;
    int pinC;

    void begin() {
        pinMode(pinA, INPUT);
        pinMode(pinB, INPUT);
        pinMode(pinC, INPUT);
    }

    void readLevels(int &levelA, int &levelB, int &levelC) {
        levelA = digitalRead(pinA);
        levelB = digitalRead(pinB);
        levelC = digitalRead(pinC);
    }
};

// Define a structure for fan control
struct Fans {
    int pinA;
    int pinB;
    unsigned long previousTime;
    int state;

    Fans(int aPin, int bPin) : pinA(aPin), pinB(bPin), previousTime(0), state(0) {}

    void begin() {
        pinMode(pinA, OUTPUT);
        pinMode(pinB, OUTPUT);
        previousTime = millis();
    }

    void update(unsigned long currentTime) {
        const unsigned long intervals[] = {1000, 1000, 1000, 3000}; // FanA, FanB, Both, Off
        const int outputs[][2] = {{HIGH, LOW}, {LOW, HIGH}, {HIGH, HIGH}, {LOW, LOW}};

        if (currentTime - previousTime >= intervals[state]) {
            digitalWrite(pinA, outputs[state][0]);
            digitalWrite(pinB, outputs[state][1]);
            state = (state + 1) % 4;
            previousTime = currentTime;
        }
    }
};

// Define a structure for water pump control
struct WaterPumpController {
    int pin;
    int pumpPWM;
    bool pumpStatus;
    unsigned long previousTime;
    unsigned long previousPumpTime;
    const unsigned long stabilityTime;
    const unsigned long pumpTimeOff;
    const unsigned long pumpTimeOn;

    WaterPumpController(int p) 
        : pin(p), pumpPWM(0), pumpStatus(false), previousTime(0), previousPumpTime(0), 
          stabilityTime(1000), pumpTimeOff(1000), pumpTimeOn(5000) {}

    void begin() {
        pinMode(pin, OUTPUT);
        previousTime = millis();
        previousPumpTime = millis();
    }

    void updatePumpStatus(unsigned long currentTime, int waterLevelA, int waterLevelB, int waterLevelC, int waterLevelD) {
        unsigned long elapsedTime = currentTime - previousTime;
        unsigned long elapsedPumpTime = currentTime - previousPumpTime;

        if (waterLevelC == LOW) {
            digitalWrite(WaterLevelD, HIGH);
            // Cycle WaterLevelD
            if (elapsedTime % 600 < 300) {
                digitalWrite(WaterLevelD, HIGH);
            } else {
                digitalWrite(WaterLevelD, LOW);
            }
            pumpPWM = 0;
            analogWrite(pin, pumpPWM);
        } else if (pumpStatus && (elapsedPumpTime <= pumpTimeOn)) {
            if (waterLevelA == HIGH && elapsedTime >= stabilityTime) {
                pumpPWM = 255;
            } else if (waterLevelB == HIGH && elapsedTime >= stabilityTime) {
                pumpPWM = 170;
            } else if (waterLevelC == HIGH && elapsedTime >= stabilityTime) {
                pumpPWM = 85;
            } else if (waterLevelC == LOW && elapsedTime >= stabilityTime) {
                pumpPWM = 0;
            }
            analogWrite(pin, pumpPWM);
            previousTime = currentTime;
        } else if (elapsedPumpTime >= pumpTimeOn) {
            digitalWrite(pin, LOW);
            pumpStatus = false;
            previousPumpTime = currentTime;
        } else if (elapsedPumpTime >= pumpTimeOff) {
            analogWrite(pin, pumpPWM);
            pumpStatus = true;
            previousPumpTime = currentTime;
        }
    }
};

// Instantiate structures for each component
WaterLevelSensors waterLevelSensors = {WaterLevelA, WaterLevelB, WaterLevelC};
Fans fans = {FanA, FanB};
WaterPumpController waterPumpController = {WaterPump};

void setup() {
    Serial.begin(9600);
    waterLevelSensors.begin();
    fans.begin();
    waterPumpController.begin();
}

void loop() {
    int waterLevelA, waterLevelB, waterLevelC;
    unsigned long currentTime = millis();

    waterLevelSensors.readLevels(waterLevelA, waterLevelB, waterLevelC);
    waterPumpController.updatePumpStatus(currentTime, waterLevelA, waterLevelB, waterLevelC, WaterLevelD);
    fans.update(currentTime);
