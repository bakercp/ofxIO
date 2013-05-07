#include "ofExampleApp.h"

//------------------------------------------------------------------------------
void ofExampleApp::exit() {
    watcher.UnregisterEvents(this);
}

//------------------------------------------------------------------------------
void ofExampleApp::setup(){

    ofSetWindowShape(ofGetScreenWidth(), 200);
    ofSetWindowPosition(0, 20);

    watcher.RegisterEvents(this);

    string folderToWatch = ofToDataPath("",true);
    bool   bListExistingItemsOnStart = true;

    watcher.addPath(folderToWatch,bListExistingItemsOnStart,&fileFilter);
}

//------------------------------------------------------------------------------
void ofExampleApp::draw(){
    ofBackground(0);
    ofFill();

    int y = TXT_HEIGHT;
    for(size_t i = 0; i < messages.size(); i++) {
        ofSetColor(ofMap(i, 0, messages.size(), 255, 90));
        ofDrawBitmapString(messages[i], 10, y);
        y += TXT_HEIGHT;
    }
}

//------------------------------------------------------------------------------
void ofExampleApp::gotMessage(ofMessage msg){

    int height = ofGetHeight();
    int numLines = (int)(height / TXT_HEIGHT);

    messages.push_front(msg.message);

    while(messages.size() > numLines) {
        messages.pop_back();
    }
}
