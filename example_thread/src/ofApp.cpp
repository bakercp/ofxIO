//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofLog::setChannel(std::make_shared<ofxIO::ThreadsafeConsoleLoggerChannel>());

    ofSetLogLevel(OF_LOG_VERBOSE);

    countingClass.start();
}


void ofApp::update()
{
}


void ofApp::draw()
{
}


void ofApp::keyPressed(int key)
{
    if (key == '1')
    {
        countingClass.start();
    }
    else if (key == '2')
    {
        countingClass.stop();
    }
    else if (key == '3')
    {
        countingClass.stopAndJoin();
    }
}

