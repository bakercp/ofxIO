//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxIO.h"


class CountingClass: public ofxIO::Thread
{
public:
    CountingClass():
        ofxIO::Thread(std::bind(&CountingClass::functionToBeRunInAThread, this))
    {
    }

    virtual ~CountingClass()
    {
    }

    void functionToBeRunInAThread()
    {
        uint64_t maxCount = 10;
        uint64_t count = 0;

        while (isRunning() && count < maxCount)
        {
            uint64_t delay = ofRandom(10000);
            ofLogNotice("CountingClass::functionToBeRunInAThread") << count << " ... waiting ... " << delay;
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait_for(lock, std::chrono::milliseconds(delay));
            ++count;
        }
    }

};


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;;
    void draw() override;;

    void keyPressed(int key) override;;

    CountingClass countingClass;

};
