//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxGui.h"
#include "ofxIO.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    void ditherChanged(float&);

    bool doDither = true;

    ofPixels originalPix;
    ofPixels grayscalePix;
    ofPixels ditheredPix;

    ofTexture originalTex;
    ofTexture grayscaleTex;
    ofTexture ditheredTex;

    ofxIO::ImageUtils::ImageHeader header;

    ofxPanel gui;
    ofxFloatSlider ditherThreshold;
    ofxFloatSlider ditherQuantWeight;

};
