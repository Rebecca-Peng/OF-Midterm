#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ard.connect("/dev/tty.usbmodem1411", 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)

}

//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();

}

void ofApp::setupArduino(const int & version) {

    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    
}

void ofApp::updateArduino(){

    ard.update();
}

//--------------------------------------------------------------

int state = 0;
int lastState = 0;
int Num = 0;
int Num1 = 0;

void ofApp::draw(){
    
    int data0 = ard.getAnalog(0);
    
    int data = data0 - 1009;
    if(data <5 ) state = 1;
    else state = 0;
    
    if(lastState != state & state ==1){
        Num ++;
        if(Num%2 ==1) Num1 ++;
      
    }

    lastState = state;
    cout<<"count: "<<Num1<<endl;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
