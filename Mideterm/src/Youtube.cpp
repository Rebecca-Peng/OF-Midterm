//
//  Youtube.cpp
//  Mideterm
//
//  Created by pfy on 3/12/17.
//
//

#include "Youtube.hpp"
Youtube::Youtube(){

}

void Youtube::setup(){
    
    std::string url = "https://www.googleapis.com/youtube/v3/search?key=AIzaSyBw7PR0KBSq-Mb_hD5ESH03oc62YxP9lHw&channelId=UCi8e0iOVk1fEOogdfu4YgfA&part=snippet,id&order=date&maxResults=10";
    bool parsingSuccessful = json.open(url);
    if(parsingSuccessful){
        ofLogNotice("ofApp::setup")<<json.getRawString(true);
    }
    else{
        ofLogNotice("ofApp::setup")<<"Failed to parse Json";
    }
    
}
