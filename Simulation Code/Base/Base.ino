#include <Arduino.h>
//Actual Revised Code
// Define the pins for the water level sensors
const int WaterLevelA = 4;
const int WaterLevelB = 5;
const int WaterLevelC = 6;
const int WaterLevelD = 7;

// Define the pins for the fans
const int FanA = 9;
const int FanB = 10;
int FanPWM; // Variable to control the speed of the fans

// Define the water pump struct
struct WaterPumpFn {
    unsigned long previousTime = 0; // Time of the last water level check
    unsigned long previousPumpTime = 0; // Time of the last pump status check
    int PumpPWM = 0; // Variable to control the speed of the water pump
    bool pumpStatus = false; // Pump status (true = on, false = off)

    const unsigned long stabilityTime = 1000; // Stability time in milliseconds
    const unsigned long pumpTimeOff = 1000; // Pump off time in milliseconds
    const unsigned long pumpTimeOn = 5000; // Pump on time in milliseconds
};

// Create an instance of the WaterPumpFn struct
WaterPumpFn waterPump;

const int WaterPump = 11; // Pin for the water pump

void setup() 
{
  Serial.begin(9600); // Start the serial communication with the computer
  // Set the mode of the pins
  pinMode(WaterLevelA, INPUT);
  pinMode(WaterLevelB, INPUT);
  pinMode(WaterLevelC, INPUT);
  pinMode(WaterLevelD, OUTPUT);
  pinMode(FanA, OUTPUT);
  pinMode(FanB, OUTPUT);
  pinMode(WaterPump, OUTPUT);
}

// Function to check the current water level
void checkWaterLevel(int &waterLevelA, int &waterLevelB, int &waterLevelC) 
{
  // Read the value of the water level sensors
  waterLevelA = digitalRead(WaterLevelA);
  waterLevelB = digitalRead(WaterLevelB);
  waterLevelC = digitalRead(WaterLevelC);
}

// Function to check and update the status of the pump
void checkPumpStatus(WaterPumpFn &waterPump, unsigned long &currentTime, unsigned long &elapsedTime, 
unsigned long &currentPumpTime, unsigned long &elapsedPumpTime, int waterLevelA, 
int waterLevelB, int waterLevelC) 
{
  currentTime = millis(); // Get the current time
  elapsedTime = currentTime - waterPump.previousTime; // Calculate elapsed time since last water level check
  currentPumpTime = millis(); // Get the current time for the pump
  elapsedPumpTime = currentPumpTime - waterPump.previousPumpTime; // Calculate elapsed time since last pump status check
  
  if (waterLevelC == LOW)
  {
    digitalWrite(WaterLevelD,HIGH);
    delay(300);
    digitalWrite(WaterLevelD,LOW);
    delay(300);
    waterPump.PumpPWM = 0;
    analogWrite(WaterPump, waterPump.PumpPWM);
  }
  else if ((waterPump.pumpStatus) && (elapsedPumpTime <= waterPump.pumpTimeOn)) // Pump is on and within on-time
  {
    if ((waterLevelA == HIGH) && (elapsedTime >= waterPump.stabilityTime))
    {
      waterPump.PumpPWM = 255; // Set pump speed to maximum
      waterPump.previousTime = currentTime; // Update last water level check time
    }
    else if ((waterLevelB == HIGH) && (elapsedTime >= waterPump.stabilityTime))
    {
      waterPump.PumpPWM = 170; // Set pump speed to medium-high
      waterPump.previousTime = currentTime; // Update last water level check time
    }
    else if ((waterLevelC == HIGH) && (elapsedTime >= waterPump.stabilityTime))
    {
      waterPump.PumpPWM = 85; // Set pump speed to medium-low
      waterPump.previousTime = currentTime; // Update last water level check time
    }
    else if ((waterLevelC == LOW) && (elapsedTime >= waterPump.stabilityTime))
    {
      waterPump.PumpPWM = 0; // Turn off the pump
      waterPump.previousTime = currentTime; // Update last water level check time
    }
    analogWrite(WaterPump, waterPump.PumpPWM); // Apply the new pump speed
  }
  else if (elapsedPumpTime >= waterPump.pumpTimeOn) // Pump on-time exceeded
  {
    digitalWrite(WaterPump, LOW); // Turn off the pump
    waterPump.pumpStatus = false; // Update pump status
    waterPump.previousPumpTime = currentPumpTime; // Update last pump status check time
  }
  else if (elapsedPumpTime >= waterPump.pumpTimeOff)// Pump off-time exceeded
  {
    analogWrite(WaterPump, waterPump.PumpPWM); // Turn on the pump
    waterPump.pumpStatus = true; // Update pump status
    waterPump.previousPumpTime = currentPumpTime; // Update last pump status check time
  }
}

void loop() 
{
  int waterLevelA, waterLevelB, waterLevelC; // Variables to store the current water level
  unsigned long currentTime, elapsedTime, currentPumpTime, elapsedPumpTime; // Variables to store the current time and elapsed time

  checkWaterLevel(waterLevelA, waterLevelB, waterLevelC); // Check the current water level
  checkPumpStatus(waterPump, currentTime, elapsedTime, currentPumpTime, elapsedPumpTime, 
  waterLevelA, waterLevelB, waterLevelC); // Check and update the pump status
}