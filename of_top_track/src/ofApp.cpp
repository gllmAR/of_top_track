#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {

    ofSetLogLevel(OF_LOG_VERBOSE);

    
    // enable depth->video image calibration
    kinect.setRegistration(true);
    
    kinect.init();
    //kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();        // opens first available kinect
    //kinect.open(1);    // open a kinect by id, starting with 0 (sorted by serial # lexicographically))
    //kinect.open("A00362A08602047A");    // open a kinect using it's unique serial #
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
    
    color_image.allocate(kinect.width, kinect.height);
    depth_image.allocate(kinect.width, kinect.height);

    
    zone1.setup();
    
    panel.setup("tracker");

    ofSetFrameRate(60);
    

}

//--------------------------------------------------------------
void ofApp::update() {
    
    ofBackground(100, 100, 100);
    
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        // load grayscale depth image from the kinect source
        depth_image.setFromPixels(kinect.getDepthPixels());
        zone1.update(depth_image);
    }

}

//--------------------------------------------------------------
void ofApp::draw() {
    
    ofSetColor(255, 255, 255);
    
    
    
    // draw instructions
    ofSetColor(255, 255, 255);
    
    // draw from the live kinect
    kinect.drawDepth(220, 10, 320, 240);
    kinect.draw(620, 10, 320, 240);
        
       
    zone1.draw();
    panel.draw();
    
    
    
}



//--------------------------------------------------------------
void ofApp::exit() {
    kinect.close();
    

}

//--------------------------------------------------------------
void ofApp::keyPressed (int key) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}
