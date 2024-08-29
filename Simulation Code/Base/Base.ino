#include <Arduino.h>

// Define the pins for the sensors and component
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

    WaterLevelSensors(int a, int b, int c) : pinA(a), pinB(b), pinC(c) {}
};

// Define a structure for fan control
struct Fans {
    int pinA;
    int pinB;
    unsigned long previousTime;
    int state;

    Fans(int aPin, int bPin) : pinA(aPin), pinB(bPin), previousTime(0), state(0) {}
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
};

// Initialize the water level sensors
void beginWaterLevelSensors(WaterLevelSensors &sensors) {
    pinMode(sensors.pinA, INPUT);
    pinMode(sensors.pinB, INPUT);
    pinMode(sensors.pinC, INPUT);
}

// Read water levels from sensors
void readWaterLevels(WaterLevelSensors &sensors, int &levelA, int &levelB, int &levelC) {
    levelA = digitalRead(sensors.pinA);
    levelB = digitalRead(sensors.pinB);
    levelC = digitalRead(sensors.pinC);
}

// Initialize the fans
void beginFans(Fans &fans) {
    pinMode(fans.pinA, OUTPUT);
    pinMode(fans.pinB, OUTPUT);
    fans.previousTime = millis();
}

// Update fan control based on time
void updateFans(Fans &fans, unsigned long currentTime) {
    const unsigned long intervals[] = {1000, 1000, 1000, 3000}; // On times for FanA, FanB, Both, Off
    const int outputs[][2] = {{HIGH, LOW}, {LOW, HIGH}, {HIGH, HIGH}, {LOW, LOW}};

    // Change fan states based on time intervals
    if (currentTime - fans.previousTime >= intervals[fans.state]) {
        digitalWrite(fans.pinA, outputs[fans.state][0]);
        digitalWrite(fans.pinB, outputs[fans.state][1]);
        fans.state = (fans.state + 1) % 4; // Cycle through states
        fans.previousTime = currentTime;
    }
}

// Initialize the water pump controller
void beginWaterPumpController(WaterPumpController &controller) {
    pinMode(controller.pin, OUTPUT);
    controller.previousTime = millis();
    controller.previousPumpTime = millis();
}

// Update the water pump status based on water levels and time
void updateWaterPumpStatus(WaterPumpController &controller, unsigned long currentTime, int waterLevelA, int waterLevelB, int waterLevelC, int waterLevelD) {
    unsigned long elapsedTime = currentTime - controller.previousTime;
    unsigned long elapsedPumpTime = currentTime - controller.previousPumpTime;

    if (waterLevelC == LOW) {
        // Control WaterLevelD based on time
        digitalWrite(WaterLevelD, (elapsedTime % 600 < 300) ? HIGH : LOW);
        controller.pumpPWM = 0;
        analogWrite(controller.pin, controller.pumpPWM);
    } else if (controller.pumpStatus && (elapsedPumpTime <= controller.pumpTimeOn)) {
        // Set pump PWM based on water levels
        if (waterLevelA == HIGH && elapsedTime >= controller.stabilityTime) {
            controller.pumpPWM = 255;
        } else if (waterLevelB == HIGH && elapsedTime >= controller.stabilityTime) {
            controller.pumpPWM = 170;
        } else if (waterLevelC == HIGH && elapsedTime >= controller.stabilityTime) {
            controller.pumpPWM = 85;
        } else if (waterLevelC == LOW && elapsedTime >= controller.stabilityTime) {
            controller.pumpPWM = 0;
        }
        analogWrite(controller.pin, controller.pumpPWM);
        controller.previousTime = currentTime;
    } else if (elapsedPumpTime >= controller.pumpTimeOn) {
        digitalWrite(controller.pin, LOW);
        controller.pumpStatus = false;
        controller.previousPumpTime = currentTime;
    } else if (elapsedPumpTime >= controller.pumpTimeOff) {
        analogWrite(controller.pin, controller.pumpPWM);
        controller.pumpStatus = true;
        controller.previousPumpTime = currentTime;
    }
}

// Create instances of the structs
WaterLevelSensors waterLevelSensors(WaterLevelA, WaterLevelB, WaterLevelC);
Fans fans(FanA, FanB);
WaterPumpController waterPumpController(WaterPump);

void setup() {
    Serial.begin(9600);
    beginWaterLevelSensors(waterLevelSensors);
    beginFans(fans);
    beginWaterPumpController(waterPumpController);
}

void loop() {
    int waterLevelA, waterLevelB, waterLevelC;
    unsigned long currentTime = millis();

    readWaterLevels(waterLevelSensors, waterLevelA, waterLevelB, waterLevelC);
    updateWaterPumpStatus(waterPumpController, currentTime, waterLevelA, waterLevelB, waterLevelC, WaterLevelD);
    updateFans(fans, currentTime);
}
