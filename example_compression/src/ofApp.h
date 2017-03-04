//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxIO.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void draw() override;

    bool test(ofxIO::AbstractByteEncoderDecoder& encoder);
    void test(ofxIO::Compression::Type type,
              int level = -1,
              int windowBits = -1);

    static const std::string LOREM_IPSUM;

};
