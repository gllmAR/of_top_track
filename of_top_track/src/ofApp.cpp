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

    
    //zone1.setup("test", 0, 1);
    
    panel.setup("tracker", TRACKER_JSON, 10, 10);
    panel.add(osc_sender_host.set("osc_host","localhost"));
    panel.add(osc_sender_port.set("osc_port", "12345"));
    panel.add(calib_name.set("calib_name","change_me"));
    panel.add(kinect_id.set("kinect_id",0,0,9));
    panel.add(zone_ammount.set("zone_ammount",3,1,3));
    panel.add(selected_zone.set("selected_zone",0,0,3));

    panel.loadFromFile(TRACKER_JSON);


    set_zones();
    set_sender();
    
    osc_sender_host.addListener(this, &ofApp::osc_sender_host_changed);
    osc_sender_port.addListener(this, &ofApp::osc_sender_port_changed);
    zone_ammount.addListener(this, &ofApp::zone_ammount_changed);
    calib_name.addListener(this, &ofApp::calib_name_changed);
    kinect_id.addListener(this, &ofApp::kinect_id_changed);

    ofSetFrameRate(60);
    

} 

//--------------------------------------------------------------
void ofApp::set_zones()
{
    zones.clear();
    zones.resize(zone_ammount);
    for (int i =0; i<zone_ammount; i++)
    {
        zones[i].setup(calib_name,kinect_id,i+1);
    }
    selected_zone.setMax(zone_ammount);

}

void ofApp::set_sender()
{
    int output_port = std::stoi(osc_sender_port); 
    osc_sender.setup(osc_sender_host, output_port);
}
//--------------------------------------------------------------
void ofApp::update() {
    
    ofBackground(100, 100, 100);
    
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        // load grayscale depth image from the kinect source
        depth_image.setFromPixels(kinect.getDepthPixels());

        for (int i =0; i<zones.size(); i++ )
        {
            zones[i].update(depth_image);
            for (ofxOscMessage m : zones[i].osc_blobs)
            {
                osc_sender.sendMessage(m, false);
            }
        }
    }



}

//--------------------------------------------------------------
void ofApp::draw() 
{
           
    // draw instructions
    ofSetColor(255, 255, 255);
    
    // draw from the live kinect
    kinect.drawDepth(220, 10, 320, 240);
    kinect.draw(620, 10, 320, 240);
        
        for (int i =0; i<zones.size(); i++ )
        {
            zones[i].draw_rect();
        }
    if (selected_zone ==0 ){
        // draw nothing, save cpu
    } else {
    zones[selected_zone-1].draw();
    }
            
panel.draw();
        
}



//--------------------------------------------------------------
void ofApp::exit() 
{
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


void ofApp::osc_sender_host_changed(std::string &s)
{
    set_sender();
}

void ofApp::osc_sender_port_changed(std::string &s)
{
    set_sender();
}

void ofApp::zone_ammount_changed(int &i)
{
    set_zones();
}

void ofApp::calib_name_changed(std::string &s)
{
    set_zones();
}

void ofApp::kinect_id_changed(int &i)
{
    set_zones();
}
