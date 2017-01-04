//
// Copyright (c) 2009 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetWindowShape(ofGetScreenWidth(), 200);
    ofSetWindowPosition(0, 20);

    watcher.registerAllEvents(this);

    std::string folderToWatch = ofToDataPath("", true);
    bool listExistingItemsOnStart = true;

    watcher.addPath(folderToWatch, listExistingItemsOnStart, &fileFilter);

}


void ofApp::draw()
{
    ofBackground(0);
    ofFill();

    int y = TXT_HEIGHT;

    for (std::size_t i = 0; i < messages.size(); ++i)
    {
        ofSetColor(ofMap(i, 0, messages.size(), 255, 90));
        ofDrawBitmapString(messages[i], 10, y);
        y += TXT_HEIGHT;
    }
}


void ofApp::gotMessage(ofMessage msg)
{
    int height = ofGetHeight();

    std::size_t numLines = static_cast<std::size_t>(height / TXT_HEIGHT);

    messages.push_front(msg.message);

    while (messages.size() > numLines)
    {
        messages.pop_back();
    }
}
