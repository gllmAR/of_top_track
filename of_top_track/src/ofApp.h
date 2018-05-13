#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "zone.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    
    ofxKinect kinect;
    ofxCvColorImage color_image;
    ofxCvGrayscaleImage depth_image; // grayscale depth image
    Zone zone1;
    
    ofxPanel panel;
};
