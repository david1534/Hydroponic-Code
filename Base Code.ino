//The setup() function initializes the system, and the loop() function continuously 
//checks the water level and updates the pump status. The checkWaterLevel() and checkPumpStatus() 
//functions are helper functions that are used to read the water level sensors and control the 
//pump, respectively. The PumpPWM variable controls the speed of the pump, with a
//higher value indicating a higher speed. The FanPWM variable would be used to control 
//the speed of the fans in a similar manner. The pumpStatus variable indicates whether 
//the pump is currently on (true) or off (false). The previousTime and previousPumpTime 
//variables store the last time the water level and pump status were checked, respectively. 
//The stabilityTime, pumpTimeOff, and pumpTimeOn variables are used to control the timing 
//of the system. The stabilityTime is the amount of time to wait before changing the 
//pump speed, and the pumpTimeOff and pumpTimeOn are the amounts of time to keep the pump off 
//and on, respectively. The WaterLevelA, WaterLevelB, WaterLevelC, and WaterLevelD variables
//are the pins connected to the water level sensors, and the FanA, FanB, and WaterPump 
//variables are the pins connected to the fans and the water pump, respectively. The 
//waterLevelA, waterLevelB, waterLevelC, and waterLevelD variables in the loop() function
//are used to store the current state of the water level sensors, and the currentTime, 
//elapsedTime, currentPumpTime, and elapsedPumpTime variables are used to calculate the current 
//time and the amount of time that has passed since the last water level and pump status checks.
//The checkWaterLevel() function reads the state of the water level sensors and stores the
//results in the waterLevelA, waterLevelB, waterLevelC, and waterLevelD variables. 
//The checkPumpStatus() function calculates the current time and the elapsed time since the 
//last water level and pump status checks, and then updates the pump status and speed based 
//on the current water level and the elapsed time. If the pump is currently on and the elapsed 
//time since the last pump status check is less than the specified on time, the function checks 
//the water level and adjusts the pump speed accordingly. If the water level is high, the pump 
//speed is set to maximum, and if the water level is low, the pump speed is set to minimum. If 
//the elapsed time since the last pump status check is greater than the specified on time, the 
//pump is turned off. If the pump is currently off and the elapsed time since the last pump status 
//check is greater than the specified off time, the pump is turned on. The analogWrite() function 
//is used to apply the new pump speed, and the digitalWrite() function is used to turn the pump on 
//and off. The pumpStatus variable is updated to reflect the current status of the pump. The 
//previousTime and previousPumpTime variables are updated to store the current time. The loop() 
//function continuously calls the checkWaterLevel() and checkPumpStatus() functions to monitor the 
//water level and control the pump. 

// Define the pins for the water level sensors
const int WaterLevelA = 4;
const int WaterLevelB = 5;
const int WaterLevelC = 6;
const int WaterLevelD = 7;

// Define the pins for the fans
const int FanA = 9;
const int FanB = 10;
int FanPWM; // Variable to control the speed of the fans

// Define the variables for the water pump
unsigned long previousTime = 0; // Variable to store the last time the water level was checked
unsigned long previousPumpTime = 0; // Variable to store the last time the pump status was checked
const unsigned long stabilityTime = 1000; // Time in milliseconds to wait before changing the pump speed
bool pumpStatus = false; // Variable to store the current status of the pump (true = on, false = off)
const unsigned long pumpTimeOff = 1000; // Time in milliseconds for the pump to stay off
const unsigned long pumpTimeOn = 5000; // Time in milliseconds for the pump to stay on
const int WaterPump = 11; // Pin for the water pump
int PumpPWM; // Variable to control the speed of the water pump

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
void checkPumpStatus(unsigned long &currentTime, unsigned long &elapsedTime, 
unsigned long &currentPumpTime, unsigned long &elapsedPumpTime, int waterLevelA, 
int waterLevelB, int waterLevelC) 
{
  currentTime = millis(); // Get the current time
  elapsedTime = currentTime - previousTime; // Calculate how much time has passed since the last water level check
  currentPumpTime = millis(); // Get the current time
  elapsedPumpTime = currentPumpTime - previousPumpTime; // Calculate how much time has passed since the last pump status check
  if (waterLevelC == LOW)
  {
    digitalWrite(WaterLevelD,HIGH);
    delay(300);
    digitalWrite(WaterLevelD,LOW);
    delay(300);
    PumpPWM = 0;
    analogWrite(WaterPump, PumpPWM);
  }
  else if ((pumpStatus) && (elapsedPumpTime <= pumpTimeOn)) // If the pump is currently on and has been on for less than the specified on time
  {
    // Check the water level and adjust the pump speed accordingly
    if ((waterLevelA == HIGH) && (elapsedTime >= stabilityTime))
    {
      PumpPWM = 255; // Set the pump speed to maximum
      previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((waterLevelB == HIGH) && (elapsedTime >= stabilityTime))
    {
      PumpPWM = 170; // Set the pump speed to medium-high
      previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((waterLevelC == HIGH) && (elapsedTime >= stabilityTime))
    {
      PumpPWM = 85; // Set the pump speed to medium-low
      previousTime = currentTime; // Update the time of the last water level check
    }
    else if ((waterLevelC == LOW) && (elapsedTime >= stabilityTime))
    {
      PumpPWM = 0; // Turn off the pump
      previousTime = currentTime; // Update the time of the last water level check
    }
    analogWrite(WaterPump, PumpPWM); // Apply the new pump speed
  }
  else if (elapsedPumpTime >= pumpTimeOn) // If the pump has been on for more than the specified on time
  {
    digitalWrite(WaterPump, LOW); // Turn off the pump
    pumpStatus = false; // Update the pump status
    previousPumpTime = currentPumpTime; // Update the time of the last pump status check
  }
  else if (elapsedPumpTime >= pumpTimeOff)// If the pump has been off for more than the specified off time
  {
    analogWrite(WaterPump, PumpPWM); // Turn on the pump
    pumpStatus = true; // Update the pump status
    previousPumpTime = currentPumpTime; // Update the time of the last pump status check
  }
}

void loop() 
{
  int waterLevelA, waterLevelB, waterLevelC; // Variables to store the current water level
  unsigned long currentTime, elapsedTime, currentPumpTime, elapsedPumpTime; // Variables to store the current time and elapsed time

  checkWaterLevel(waterLevelA, waterLevelB, waterLevelC); // Check the current water level
  checkPumpStatus(currentTime, elapsedTime, currentPumpTime, elapsedPumpTime, 
  waterLevelA, waterLevelB, waterLevelC); // Check and update the pump status
  
}