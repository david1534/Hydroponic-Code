There are three folders in this repo

1. Simulation Code: which is will serve as the code used in SimulIDE, our electrical 
circuit simulator. This code will be functionally different than the tactical code and will 
not work on the actual software deployment. 

2. Tactical Code: will be the actual C++ arduino code that will be used in the system. The
implementation of this code will be similar to the simulation code. This code is still in 
development and will be complete after the integration of all the unit tests

3. Unit Testing: this folder will contain all the unit tests for each individual subsystem. The 
current subsystems are water level sensors, fans, water pump, and LED's. Once the unit tests are writted
and validated on a subsystem level, integration may begin. Integration will involve the cumulative 
combination of unit tests until a final baselined version of tactical code is ready for 
deployment. 