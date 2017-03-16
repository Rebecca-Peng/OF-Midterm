#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(24);
    
    std::string url = "https://www.googleapis.com/youtube/v3/search?key=AIzaSyBw7PR0KBSq-Mb_hD5ESH03oc62YxP9lHw&channelId=UCi8e0iOVk1fEOogdfu4YgfA&part=snippet,id&order=date&maxResults=10";
    bool parsingSuccessful = json.open(url);
    if(parsingSuccessful){
        ofLogNotice("ofApp::setup")<<json.getRawString(true);
    }
    else{
        ofLogNotice("ofApp::setup")<<"Failed to parse Json";
    }
    
    for(Json::ArrayIndex i = 0; i < 10; ++i){
        id[i] = json["items"][i]["id"]["videoId"].asString();
        title[i] =json["items"][i]["snippet"]["title"].asString();
        videoUrl[i] = "http://www.youtube.com/watch?v=" + id[i];
    }
    
    for(int i = 0; i < 10; ++i){
//    myCommand[i] = "/usr/local/bin/youtube-dl  -o /Applications/of_v0.9.8_osx_release/apps/myApps/Midterm-funcation-2/bin/data/\\%\\(title\\)s.\\%\\(ext\\)s " + videoUrl[i];
    cout<<ofSystem(myCommand[i]);
    num[i] = ofToString(i);
    movieName[i] = num[i] + ".mp4";
//    ofSystem("mv /Applications/of_v0.9.8_osx_release/apps/myApps/Midterm-funcation-2/bin/data/*.mp4 /Applications/of_v0.9.8_osx_release/apps/myApps/Midterm-funcation-2/bin/data/Movies/"+movieName[i]);
    }
    
    myPlayer.load("/Applications/of_v0.9.8_osx_release/apps/myApps/Midterm-funcation-2/bin/data/Movies/"+movieName[0]);
    myPlayer.play();
    
    
    
    ard.connect("/dev/tty.usbmodem1411", 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
}

//--------------------------------------------------------------
void ofApp::update(){
    
    myPlayer.update();
    if(Num < 0) Num = ofRandom(5,9);
    else if(Num >9) Num = ofRandom(0,9);
    
    updateArduino();

    
}

void ofApp::setupArduino(const int & version){
    
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;
    
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    ard.sendAnalogPinReporting(0,ARD_ANALOG);
}

void ofApp::updateArduino(){
    
    ard.update();
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofSetColor(255);
    ofSetHexColor(0xFFFFFF);

    myPlayer.draw(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(255,129,199);

    int data0 = ard.getAnalog(0);
    
    int data = data0 - 1009;
    if(data <5 ) state = 1;
    else state = 0;
    
    if(lastState != state & state ==1){
        Num ++;
        if(Num%2 ==1) Num1 ++;
    
        
        myPlayer.stop();
        myPlayer.load("/Applications/of_v0.9.8_osx_release/apps/myApps/Midterm-funcation-2/bin/data/Movies/"+movieName[Num]);
        myPlayer.play();
        
    }
    
    lastState = state;
    cout<<"Num: "<<Num<<endl;
    
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    
//    if (key == OF_KEY_RIGHT){
//        count ++;
//            }
//    else if(key == OF_KEY_LEFT){
//        count --;
//    }
//    
//    myPlayer.stop();
//    myPlayer.load("/Applications/of_v0.9.8_osx_release/apps/myApps/Midterm-funcation-2/bin/data/Movies/"+movieName[count]);
//    myPlayer.play();

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

