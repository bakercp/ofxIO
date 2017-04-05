//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ditherThreshold.addListener(this, &ofApp::ditherChanged);
    ditherQuantWeight.addListener(this, &ofApp::ditherChanged);

    gui.setup();
    gui.add(ditherThreshold.setup("dither threshold", 0.75, 0, 1));
    gui.add(ditherQuantWeight.setup("dither quant. weight", 0.125, 0, 1));

    std::filesystem::path path = ofToDataPath("puppy.jpg", true);

    bool success = ofxIO::ImageUtils::loadHeader(header, path);

    if (!success)
    {
        ofLogError() << "Unable to load header from image.";
    }

    ofLoadImage(originalPix, path);
    originalTex.loadData(originalPix);

    grayscalePix = ofxIO::ImageUtils::toGrayscale(originalPix);
    grayscaleTex.loadData(grayscalePix);

    ofSetWindowShape(originalPix.getWidth() * 2,
                     originalPix.getHeight() * 2);
}


void ofApp::update()
{
    if (doDither)
    {
        ditheredPix = ofxIO::ImageUtils::dither(grayscalePix,
                                                ditherThreshold,
                                                ditherQuantWeight);

        ditheredTex.loadData(ditheredPix);
        doDither = false;
    }
}


void ofApp::draw()
{
    ofSetBackgroundColor(0);

    originalTex.draw(0, 0);
    grayscaleTex.draw(originalTex.getWidth(), 0);
    ditheredTex.draw(0, originalTex.getHeight());

    std::stringstream ss;

    ss << "Header Data" << std::endl;
    ss << "     Width: " << header.width << std::endl;
    ss << "    Height: " << header.height << std::endl;
    ss << "Bits/Pixel: " << header.bpp;

    ofDrawBitmapStringHighlight(ss.str(),
                                originalTex.getWidth() + 14,
                                originalTex.getHeight() + 20);

    gui.draw();
}


void ofApp::ditherChanged(float&)
{
    doDither = true;
}
