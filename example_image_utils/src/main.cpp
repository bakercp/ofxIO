//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"
#include "ofAppNoWindow.h"


int main()
{
	ofAppNoWindow window;
	ofSetupOpenGL(&window, 0, 0, OF_WINDOW);
    return ofRunApp(std::make_shared<ofApp>());
}
