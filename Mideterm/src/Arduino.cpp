//
//  Arduino.cpp
//  Mideterm
//
//  Created by pfy on 3/12/17.
//
//

#include "Arduino.hpp"

Arduino::Arduino(){}

void Arduino::setup(){
    ard.connect("/dev/tty.usbmodem1411", 57600);
    bSetupArduino	= false;
}

void Arduino::update(){
    
    if(Num < 0) Num = ofRandom(5,9);
    else if(Num >9) Num = ofRandom(0,9);
    
    updateArduino();
}

void Arduino::draw(){
    
    int data0 = ard.getAnalog(0);
    
    int data = data0 - 1009;
    if(data <5 ) state = 1;
    else state = 0;
    
    if(lastState != state & state ==1){
        Num ++;
        if(Num%2 ==1) Num1 ++;
        
//        
//        myPlayer.stop();
//        myPlayer.load("/Applications/of_v0.9.8_osx_release/apps/myApps/Midterm-funcation-2/bin/data/Movies/"+movieName[Num]);
//        myPlayer.play();
        
    }
    
    lastState = state;
    cout<<"Num: "<<Num<<endl;

}

