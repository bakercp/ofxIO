//
// Copyright (c) 2009 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <deque>
#include "ofMain.h"
#include "ofxIO.h"


class ofApp: public ofBaseApp
{
public:
    enum
    {
        TXT_HEIGHT = 14
    };

    void setup();
    void draw();

    void gotMessage(ofMessage msg);

    void onDirectoryWatcherItemAdded(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt)
    {
        ofSendMessage("Added:    " + evt.item.path());
    }

    void onDirectoryWatcherItemRemoved(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt)
    {
        ofSendMessage("Removed:  " + evt.item.path());
    }

    void onDirectoryWatcherItemModified(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt)
    {
        ofSendMessage("Modified: " + evt.item.path());
    }

    void onDirectoryWatcherItemMovedFrom(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt)
    {
        ofLogNotice("ofApp::onDirectoryWatcherItemMovedFrom") << "Moved From: " << evt.item.path();
    }

    void onDirectoryWatcherItemMovedTo(const ofxIO::DirectoryWatcherManager::DirectoryEvent& evt)
    {
        ofLogNotice("ofApp::onDirectoryWatcherItemMovedTo") << "Moved To: " << evt.item.path();
    }

    void onDirectoryWatcherError(const Poco::Exception& exc)
    {
        ofLogError("ofApp::onDirectoryWatcherError") << "Error: " << exc.displayText();
    }


    ofxIO::DirectoryWatcherManager watcher;

    ofxIO::HiddenFileFilter fileFilter; // an example file filter

    std::deque<std::string> messages;

};
