//
//  Particle.cpp
//  Mideterm
//
//  Created by pfy on 3/13/17.
//
//

#include "Particle.hpp"

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

