#include "zone.h"


//--------------------------------------------------------------
void Zone::setup(std::string _calib_name, int _kinect_id, int _zone_id) {

    zone_id=_zone_id;
    kinect_id=_kinect_id;

    kinect_zone_id = ofToString(kinect_id);
    kinect_zone_id += "_";
    kinect_zone_id += ofToString(zone_id);

    save_path = _calib_name;
    save_path += "/";
    save_path += kinect_zone_id;
    save_path += ".json";

    osc_path = "/";
    osc_path += _calib_name;
    osc_path += "/";
    osc_path += ofToString(kinect_id);
    osc_path += "/";
    osc_path += ofToString(zone_id);
    osc_path += "/";
    

    cout<<kinect_zone_id<<" "<<save_path<<endl;

	gui.setup(kinect_zone_id, save_path, 10, 400);

	gui.add(enable.set("enable", 1));
	gui.add(crop_x.set("offset_x", 0,0,640));
	gui.add(crop_y.set("offset_y", 0,0,480));
	gui.add(crop_width.set("crop_width", 320,0,640));
	gui.add(crop_height.set("crop_height", 480,0,480));
    gui.add(far_threshold.set("far_threshold", 70, 0, 255 ));
    gui.add(near_threshold.set("near_threshold", 230, 0, 255 ));
    



    depth_image.allocate(input_width,input_height);
    depth_image_crop.allocate(input_width,input_height);
    depth_thresh_near.allocate(input_width, input_height);
    depth_thresh_far.allocate(input_width, input_height);
 	
    gui.loadFromFile(save_path);
}

//--------------------------------------------------------------
void Zone::update(ofxCvGrayscaleImage _depth_image) 

{

	//depth_image=_depth_image;
    if(enable)
    {
	_depth_image.setROI(crop_x, crop_y, crop_width, crop_height);

    depth_image_crop=_depth_image.getRoiPixels();
    depth_image=depth_image_crop.getPixels();

    depth_thresh_near = depth_image_crop.getPixels();
    depth_thresh_far = depth_image_crop.getPixels();
    depth_thresh_near.threshold(near_threshold, true);
    depth_thresh_far.threshold(far_threshold);
    cvAnd(depth_thresh_near.getCvImage(), depth_thresh_far.getCvImage(), depth_image_crop.getCvImage(), NULL);
    depth_image_crop.flagImageChanged();
    contour_finder.findContours(depth_image_crop, 10, (input_width*input_height)/2, 20, false);

    blobs_to_osc();
    blobs_count=contour_finder.nBlobs;

    } else {
        osc_blobs.clear();

    }

}


void Zone::blobs_to_osc()
{
    osc_blobs.clear();
    for(int i = 0; i < contour_finder.nBlobs; i++) 
    {
    ofxOscMessage m;

    m.setAddress(osc_path);
    // blob id, blob total, area (x and y relative?)
    m.addInt32Arg(i);
    m.addInt32Arg(contour_finder.nBlobs);
    m.addInt32Arg(contour_finder.blobs.at(i).area);  
    osc_blobs.push_back(m);
    }

}

void Zone::draw_rect() 
{

if (enable)
    {
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(220,10);
    ofSetColor(0,255,0);
    ofNoFill();
    ofDrawRectangle(crop_x/2, crop_y/2, crop_width/2, crop_height/2);
    ofPopStyle();
    ofPopMatrix();
    }
}

//--------------------------------------------------------------
void Zone::draw() {

if (enable)
{
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(220,10);
	ofSetColor(255,0,0);
	ofNoFill();
	ofDrawRectangle(crop_x/2, crop_y/2, crop_width/2, crop_height/2);
    ofPopStyle();
    ofPopMatrix();


	ofPushMatrix();
	ofTranslate(220,400);
    depth_image.draw(0,0, 320, 240);

	ofTranslate(420,0);
	depth_image_crop.draw(0,0, crop_width, crop_height);
	contour_finder.draw(0, 0, crop_width, crop_height);
	ofPopMatrix();
    
}

    gui.draw();

}




//--------------------------------------------------------------
void Zone::exit() {

    

}
