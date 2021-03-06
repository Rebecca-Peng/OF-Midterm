#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
//#include "Particle.hpp"


class Particle {
public:
    Particle();                //Class constructor
    void setup();              //Start particle
    void update( float dt );   //Recalculate physics
    void draw();               //Draw particle
    
    ofPoint pos;               //Position
    ofPoint vel;               //Velocity
    float time;                //Time of living
    float lifeTime;            //Allowed lifetime
    bool live;                 //Is particle live
};

//Control parameters class
class Params {
public:
    void setup();
    ofPoint eCenter;    //Emitter center
    float eRad;         //Emitter radius
    float velRad;       //Initial velocity limit
    float lifeTime;     //Lifetime in seconds
    
    float rotate;   //Direction rotation speed in angles per second
    
    float force;       //Attraction/repulsion force inside emitter
    float spinning;    //Spinning force inside emitter
    float friction;    //Friction, in the range [0, 1]
};



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        int count = 0;
        ofVideoPlayer myPlayer;
    
        ofxJSONElement json;
        string id[30];
        string videoUrl[30];
        string title[30];
        string myCommand[30];
        string movieName[30];
        string num[30];
        void setupJson();
        void downloadVideo();
    
    
        ofArduino  ard;
        int state = 0;
        int lastState = 0;
        int Num = 0;
        int Num1 = 0;
    
        private:
        void connectArduino();
        void doorOpen();
        void setupArduino(const int & version);
        void updateArduino();
        bool bSetupArduino;
    
    
        vector<Particle> p;	  //Particles
        ofFbo fbo;            //Off-screen buffer for trails
        float history;        //Control parameter for trails
        float time0;          //Time value for computing dt
        float bornRate;       //Particles born rate per second
        float bornCount;      //Integrated number of particles to born
        void setupParticle();
        void updateParticle();
        void drawParticleTitle();
    
        ofSoundPlayer myBgm;
    
        string typeStr;
        ofTrueTypeFont Title;
    
};

extern Params params; //Declaration a of global variable

