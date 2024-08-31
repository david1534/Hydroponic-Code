#include <Arduino.h>
#ifndef BASE_H
#define BASE_H

class Base {
    public:
        

        // Define the pins for the fans
        enum class Fans {
            FanA = 9,
            FanB = 10,
        };
        int FanPWM;
        
};

#endif