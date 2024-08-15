#include <Arduino.h>

//this code tests the water level sensors by itself. This is different from the simulation
//code because LOW and HIGH values are swapped. When the actual water level sensors detect water
//the signal recieved will be 0V or LOW. In the simulation, it is implemented the opposite 
//way (5v or HIGH) because of the way simulIDE works. 

const int SensorA = 5;
const int SensorB = 6;
const int SensorC = 7;

void setup()
{
  Serial.begin(9600);
  pinMode(SensorA, INPUT);
  pinMode(SensorB, INPUT);
  pinMode(SensorC, INPUT);
}

void loop()
{
  int readingA = digitalRead(SensorA);
  int readingB = digitalRead(SensorB);
  int readingC = digitalRead(SensorC);

  if (readingA == LOW && readingB == LOW && readingC == LOW)
  {
    Serial.println("Water Detected on all Sensors");
  }
  else if (readingA == HIGH && readingB == HIGH && readingC == HIGH)
  {
    Serial.println("No water Detected on all Sensors");
  }
  else if (readingA == LOW)
  {
    Serial.println("Water Detected on A");
  }
  else if (readingB == LOW)
  {
    Serial.println("Water Detected on B");
  }
  else if (readingC == LOW)
  {
    Serial.println("Water Detected on C");
  }
  else
  {
    Serial.println();
  }
}
