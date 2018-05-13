#include "zone.h"


//--------------------------------------------------------------
void Zone::setup() {

	gui.setup("zone", "zone.json", 10, 400);

	gui.add(set_ROI_b.set("set_ROI", 1));
	gui.add(crop_x.set("offset_x", 0,0,640));
	gui.add(crop_y.set("offset_y", 0,0,480));
	gui.add(crop_width.set("crop_width", 320,0,640));
	gui.add(crop_height.set("crop_height", 480,0,480));


	set_ROI_b.addListener(this, &Zone::set_ROI_b_changed);
	// crop_width.addListener(this, &Zone::set_crop_changed);
	// crop_height.addListener(this, &Zone::set_crop_changed);
	// crop_x.addListener(this, &Zone::set_crop_changed);
	// crop_y.addListener(this, &Zone::set_crop_changed);


    depth_image.allocate(input_width,input_height);
    depth_image_crop.allocate(input_width,input_height);
    depth_thresh_near.allocate(input_width, input_height);
    depth_thresh_far.allocate(input_width, input_height);
 	

}

//--------------------------------------------------------------
void Zone::update(ofxCvGrayscaleImage _depth_image) 

{

	//depth_image=_depth_image;

	  if (set_ROI_b)
	{	
		_depth_image.setROI(crop_x, crop_y, crop_width, crop_height);
	} else {
		_depth_image.resetROI();
	}


    depth_image_crop=_depth_image.getRoiPixels();
    depth_image=depth_image_crop.getPixels();

    depth_thresh_near = depth_image_crop.getPixels();
	depth_thresh_far = depth_image_crop.getPixels();
	depth_thresh_near.threshold(near_threshold, true);
    depth_thresh_far.threshold(far_threshold);
    cvAnd(depth_thresh_near.getCvImage(), depth_thresh_far.getCvImage(), depth_image_crop.getCvImage(), NULL);
    depth_image_crop.flagImageChanged();
    contour_finder.findContours(depth_image_crop, 10, (input_width*input_height)/2, 20, false);

    // there is a new frame and we are connected
    // if(kinect.isFrameNew()) {
        
    //     // load grayscale depth image from the kinect source
    //     grayImage.setFromPixels(kinect.getDepthPixels());
    //     // test transform
    //     gray_transform = grayImage;

    //     gray_transform.transform(0, input_width, input_height, 2, 2, 0, 0);


        
    //     // we do two thresholds - one for the far plane and one for the near plane
    //     // we then do a cvAnd to get the pixels which are a union of the two thresholds
    
    //         grayThreshNear = grayImage;
    //         grayThreshFar = grayImage;
    //         grayThreshNear.threshold(nearThreshold, true);
    //         grayThreshFar.threshold(farThreshold);
    //         cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
     
        
    //     // update the cv images
    //     grayImage.flagImageChanged();
        
    //     // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
    //     // also, find holes is set to true so we will get interior contours as well....
    //     contourFinder.findContours(grayImage, 10, (input_width*input_height)/2, 20, false);
    // }

}

//--------------------------------------------------------------
void Zone::draw() {

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
    

       
    if (draw_gui)
    {
    	gui.draw();
    }
}



void Zone::set_ROI()
{


}

void Zone::set_ROI_b_changed(bool &b)
{
	set_ROI();
}

void Zone::set_crop_changed(float &f)
{
	set_ROI();
}


//--------------------------------------------------------------
void Zone::exit() {

    

}
