//
//  Arduino.hpp
//  Mideterm
//
//  Created by pfy on 3/12/17.
//
//

#ifndef Arduino_hpp
#define Arduino_hpp

#include "ofMain.h"
#include <stdio.h>

class Arduino{
public:
    Arduino();
    void setup();
    void update();
    void draw();
    
    ofArduino  ard;
    
    int state = 0;
    int lastState = 0;
    int Num = 0;
    int Num1 = 0;
    
private:
//    void setupArduino(const int & version);
    void updateArduino();
    bool		bSetupArduino;		
};

#endif /* Arduino_hpp */
