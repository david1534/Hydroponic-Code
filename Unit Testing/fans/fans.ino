#include <Arduino.h>

const int fanTest = 9; 
//value can be changed to test PWM function
int fanPWM = 0; 

void setup()
{
    Serial.begin(9600);
    pinMode(fanTest, OUTPUT);
}

void loop()
{
    //analogWrite(fanTest, fanPWM);
    digitalWrite(fanTest, HIGH);
}