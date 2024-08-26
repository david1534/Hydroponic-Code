#include <Arduino.h>

//Initialize Water Pump Pin
const int pumpPin = 11; 
int pumpPWM = 0; // PWM value for controlling pump speed

void setup() {
    Serial.begin(9600);
    pinMode(pumpPin, OUTPUT); // Set the pump pin as an output
}

void loop() {
    //analogWrite(pumpPin, pumpPWM); // Uncomment to control pump with PWM
    digitalWrite(pumpPin, HIGH); // Turn the pump on
}
