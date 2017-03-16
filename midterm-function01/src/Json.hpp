//
//  Json.hpp
//  midterm-function01
//
//  Created by pfy on 3/8/17.
//
//

#ifndef Json_hpp
#define Json_hpp
#include "ofMain.h"

#include <stdio.h>

class Json{
public:
    Json();
    void setup();
    void update();
    void draw();
    void activate();
    
    ofxJSONElement json;
    string id[20];
    string videoUrl[20];
    string title[20];
    string myCommand[20];
    string movieName[20];
}

#endif /* Json_hpp */
