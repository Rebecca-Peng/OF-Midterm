#include "ofApp.h"

//--------------------------------------------------------------
Params param; 

void ofApp::setup(){
    
    ofSetWindowShape(1024,768);
    ofSetFrameRate(60);
    setupJson();
    downloadVideo();
    connectArduino();
    count = 0;
    setupParticle();
//    myPlayer.load("/Applications/of_v0.9.8_osx_release/apps/myApps/Mideterm/bin/data/Movies/"+movieName[0]);
//    myPlayer.play();
    
    myBgm.load("Music.mp3");
    myBgm.setVolume(0.75f);
    myBgm.play();
    
    Title.load("Phosphate.ttc",90);
    
}

void ofApp::setupJson(){
    
    std::string url = "https://www.googleapis.com/youtube/v3/search?key=AIzaSyBw7PR0KBSq-Mb_hD5ESH03oc62YxP9lHw&channelId=UCi8e0iOVk1fEOogdfu4YgfA&part=snippet,id&order=date&maxResults=30";
    bool parsingSuccessful = json.open(url);
    if(parsingSuccessful){
        ofLogNotice("ofApp::setup")<<json.getRawString(true);
    }
    else{
        ofLogNotice("ofApp::setup")<<"Failed to parse Json";
    }

}

void ofApp::downloadVideo(){
    
    for(Json::ArrayIndex i = 0; i < 30; ++i){
        id[i] = json["items"][i]["id"]["videoId"].asString();
        title[i] =json["items"][i]["snippet"]["title"].asString();
        videoUrl[i] = "http://www.youtube.com/watch?v=" + id[i];
    }
    

    for(int i = 0; i < 30; ++i){
            myCommand[i] = "/usr/local/bin/youtube-dl  -o /Applications/of_v0.9.8_osx_release/apps/myApps/Mideterm/bin/data/\\%\\(title\\)s.\\%\\(ext\\)s " + videoUrl[i];
//        cout<<ofSystem(myCommand[i]);
        num[i] = ofToString(i);
        movieName[i] = num[i] + ".mp4";
//            ofSystem("mv /Applications/of_v0.9.8_osx_release/apps/myApps/Mideterm/bin/data/*.mp4 /Applications/of_v0.9.8_osx_release/apps/myApps/Mideterm/bin/data/Movies/"+movieName[i]);
    }

}

void ofApp::connectArduino(){
    
    ard.connect("/dev/tty.usbmodem1411", 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;

}

void ofApp::setupParticle(){
    
    int w = 1920;
    int h = 1080;
    fbo.allocate( 1920, 1080, GL_RGB32F_ARB );
    ofBackground(255,255,255);
    //Fill buffer with white color
    fbo.begin();
    ofBackground(255,255,255);
    fbo.end();
    
    //Set up parameters
    param.setup();		//Global parameters
    history = 0.1;
    bornRate = 150;
    
    bornCount = 0;
    time0 = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    myPlayer.update();
    
    updateArduino();
    if(Num < 0) Num = ofRandom(5,9);
    else if(Num >29) Num = ofRandom(0,29);
    
    if(count < 0) count = ofRandom(5,9);
    else if(count >9) count = ofRandom(0,9);
    
    updateParticle();

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

void ofApp::updateParticle(){
    
    float time = ofGetElapsedTimef();
    float dt = ofClamp( time - time0, 0, 0.5 );
    time0 = time;
    
    //Delete inactive particles
    int i=0;
    while (i < p.size()) {
        if ( !p[i].live ) {
            p.erase( p.begin() + i );
        }
        else {
            i++;
        }
    }
    
    //Born new particles
    bornCount += dt * bornRate;      //Update bornCount value
    if ( bornCount >= 1 ) {          //It's time to born particle(s)
        int bornN = int( bornCount );//How many born
        bornCount -= bornN;          //Correct bornCount value
        for (int i=0; i<bornN; i++) {
            Particle newP;
            newP.setup();            //Start a new particle
            p.push_back( newP );     //Add this particle to array
        }
    }
    
    //Update the particles
    for (int i=0; i<p.size(); i++) {
        p[i].update( dt );
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( 255,255,255);
    drawParticleTitle();
    myPlayer.draw(0,0,ofGetWidth(),ofGetHeight());
    doorOpen();
    
    if(myPlayer.getPosition() >= 0.99f)
    {
        myPlayer.close();
        myBgm.play();
        ofBackground( 255,255,255);
        drawParticleTitle();
        
    }

}

void ofApp::drawParticleTitle(){
    fbo.begin();
    
    //Draw semi-transparent white rectangle
    //to slightly clearing a buffer (depends on history value)
    
    ofEnableAlphaBlending();         //Enable transparency
    
    float alpha = (1-history) * 150;
    ofSetColor( 0,0,0, alpha );
    ofFill();
    ofRect( 0, 0, 1920, 1080);
    
    ofDisableAlphaBlending();        //Disable transparency
    
    //Draw the particles
    ofFill();
    ofSetColor(155, 155, 155);
    for (int i=0; i<p.size(); i++) {
        p[i].draw();
    }
    
    ofSetColor(205,205,205);
    //    OF_RECTMODE_CENTER;
    Title.drawString("Movie Journey", ofGetWidth()/10, ofGetHeight()/2);
    
    fbo.end();
    
    //2. Draw buffer on the screen
    ofSetColor(255,255,255);
    fbo.draw( 0, 0 );
}

void ofApp::doorOpen(){
    
    int data0 = ard.getAnalog(0);
    
    int data = data0 - 1009;
    if(data <3 ) state = 1;
    else state = 0;
    
    if(lastState != state & state ==1){
        Num ++;
        if(Num%2 ==1) Num1 ++;
        
        myBgm.stop();
        ofBackground( 255,255,255);
        myPlayer.stop();
        myPlayer.load("/Applications/of_v0.9.8_osx_release/apps/myApps/Mideterm/bin/data/Movies/"+movieName[Num]);
        myPlayer.play();
        float m = myPlayer.getPosition();
        
    }
    
    lastState = state;
    cout<<"Num: "<<Num<<endl;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
        if (key == OF_KEY_RIGHT){
            count ++;
                }
        else if(key == OF_KEY_LEFT){
            count --;
        }
    
        myBgm.stop();
        ofBackground( 255,255,255);
        myPlayer.load("/Applications/of_v0.9.8_osx_release/apps/myApps/Mideterm/bin/data/Movies/"+movieName[count]);
        myPlayer.play();

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

void Params::setup() {
    eCenter = ofPoint( ofGetWidth() / 2, ofGetHeight() / 2 );
    eRad = ofGetHeight();
    velRad = 0;
    lifeTime = 2.0;
    
    rotate = 0;
    force = 1000;
    spinning = 10;
    friction = 0.03;
}


Particle::Particle() {
    live = false;
}

//--------------------------------------------------------------
ofPoint randomPointInCircle( float maxRad ){
    ofPoint pnt;
    float rad = ofRandom( 0, maxRad );
    float angle = ofRandom( 0, M_TWO_PI );
    pnt.x = cos( angle ) * rad;
    pnt.y = sin( angle ) * rad;
    return pnt;
}

//--------------------------------------------------------------
void Particle::setup() {
    pos = param.eCenter + randomPointInCircle( param.eRad );
    vel = randomPointInCircle( param.velRad );
    time = 0;
    lifeTime = param.lifeTime;
    live = true;
}

//--------------------------------------------------------------
void Particle::update( float dt ){
    if ( live ) {
        //Rotate vel
        vel.rotate( 0, 0, param.rotate * dt );
        
        ofPoint acc;         //Acceleration
        ofPoint delta = pos - param.eCenter;
        float len = delta.length();
        if ( ofInRange( len, 0, param.eRad ) ) {
            delta.normalize();
            
            //Attraction/repulsion force
            acc += delta * param.force;
            
            //Spinning force
            acc.x += -delta.y * param.spinning;
            acc.y += delta.x * param.spinning;
        }
        vel += acc * dt;            //Euler method
        vel *= (1-param.friction);  //Friction
        
        //Update pos
        pos += vel * dt;    //Euler method
        
        //Update time and check if particle should die
        time += dt;
        if ( time >= lifeTime ) {
            live = false;   //Particle is now considered as died
        }
    }
}

//--------------------------------------------------------------
void Particle::draw(){
    if ( live ) {
        //Compute size
        float size = ofMap(
                           fabs(time - lifeTime/2), 0, lifeTime/2, 5, 1 );
        
        //Compute color
        
        float hue = ofMap( time, 0, lifeTime, 128, 255 );
        //		color.setHue( hue );
        ofSetColor(200,200,200);
        
        ofCircle(pos, size );  //Draw particle
    }
}
