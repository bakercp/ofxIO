//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofxIO::StringFilter filter = ofLoadJson("filter.json");

    filter.setWhitelist({ "drug" });

    std::string input = "Drug drugs xxx.";

    std::string output = filter.filter(input);

    std::cout << output << std::endl;

    ofExit();

}
