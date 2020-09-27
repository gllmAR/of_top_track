#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "zone.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define TRACKER_JSON "tracker_settings.json"


class ofApp : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void draw_rect();
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
    
    

    ofParameter<std::string> osc_sender_host;
    void osc_sender_host_changed(std::string &s);
    ofParameter<std::string> osc_sender_port;
    void osc_sender_port_changed(std::string &s);
    ofParameter<int> selected_zone;
    ofParameter<int> zone_ammount;
    void zone_ammount_changed(int &i);
    ofParameter<std::string> calib_name;
    void calib_name_changed(std::string &s);
    ofParameter<int> kinect_id;
    void kinect_id_changed(int &i);
    ofParameter<bool> draw_enabled;
    ofParameter<bool> RGB_enabled;
    

    void set_zones();
    void set_sender();
    std::vector<Zone> zones;

    //Zone zone1;
    
    ofxPanel panel;
    ofxOscSender osc_sender;
    ofxOscMessage zones_presence;
};
