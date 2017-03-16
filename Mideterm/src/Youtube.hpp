//
//  Youtube.hpp
//  Mideterm
//
//  Created by pfy on 3/12/17.
//

#ifndef Youtube_hpp
#define Youtube_hpp

#include "ofMain.h"
#include "ofxJSON.h"

class Youtube{
    
    public:
    Youtube();
    
    void setup();
    void update();
    void draw();
    
    ofxJSONElement json;
    

};

#include <stdio.h>

#endif /* Youtube_hpp */
