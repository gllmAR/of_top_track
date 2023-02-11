#pragma once


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "ofxOsc.h"

class Zone {
public:
    
    void setup(std::string calib_name, int kinect_id, int zone_id);
    void update(ofxCvGrayscaleImage _depth_image);
    void save_zone();
    void set_paths(std::string _calib_name, int _kinect_id, int _zone_id);
    bool clic_inside(int x, int y);
    void blobs_to_osc();
    void draw();
    void draw_rect();
    void exit();
    


    
    ofxCvGrayscaleImage depth_image; // grayscale depth image
    ofxCvGrayscaleImage depth_image_crop;
    ofxCvGrayscaleImage depth_image_crop_blob;
    ofxCvGrayscaleImage depth_thresh_near; // the near thresholded image
    ofxCvGrayscaleImage depth_thresh_far; // the far thresholded image
    

    ofxCvContourFinder contour_finder;

    int blobs_count;

    
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

    ofParameter <bool> enable;
    ofParameter <int> crop_width;
    ofParameter <int> crop_height;
    ofParameter <int> crop_x;
    ofParameter <int> crop_y;

    bool draw_gui = 1;
    bool reset_roi_flag =0;

    vector <ofxOscMessage> osc_blobs;

    int kinect_id;
    int zone_id;
    std::string kinect_zone_id;
    std::string save_path;
    std::string osc_path;

    
};
