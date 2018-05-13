#pragma once


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class Zone {
public:
    
    void setup();
    void update(ofxCvGrayscaleImage _depth_image);
    void set_ROI_b_changed(bool &b);
    void set_crop_changed(float &f);
    void draw();
    void exit();
    

    void set_ROI();

    
    ofxCvGrayscaleImage depth_image; // grayscale depth image
    ofxCvGrayscaleImage depth_image_crop;
    ofxCvGrayscaleImage depth_image_crop_blob;
    ofxCvGrayscaleImage depth_thresh_near; // the near thresholded image
    ofxCvGrayscaleImage depth_thresh_far; // the far thresholded image
    

    ofxCvContourFinder contour_finder;


    
    bool bThreshWithOpenCV;
    bool bDrawPointCloud;
    

    int input_width =640;
    int input_height= 480;
    ofParameter <int> near_threshold = 230;
    ofParameter <int> far_threshold = 70;

    ofRectangle rect;
    ofxPanel gui;
    ofxGuiGroup gui_crop;
    ofxGuiGroup gui_depth;
    ofxGuiGroup gui_contour;

    ofParameter <bool> set_ROI_b;
    ofParameter <int> crop_width;
    ofParameter <int> crop_height;
    ofParameter <int> crop_x;
    ofParameter <int> crop_y;

    bool draw_gui = 1;

    
    // used for viewing the point cloud
};
