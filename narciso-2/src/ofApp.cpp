#include "ofApp.h"


using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    objectFinder.setup("haarcascade_frontalface_default.xml");
    objectFinder.setPreset(ObjectFinder::Fast);
    
    ofSetWindowShape(1472,828);
    ofSetWindowPosition(-306,-1006);
    
    rsContext.setup(true);
    

    guiPanel.setup("Camera Controls", "settings.json");
    
    useCamera.set("Use Camera", false);
    camPosition.set("Cam Position", glm::vec3(0, 0, 50), glm::vec3(0,0,50), glm::vec3(0,0,50));
    camTruck.set("Truck", 0.0f, -100.0f, 100.0f);
    camBoom.set("Boom", 0.0f, -100.0f, 100.0f);
    camDolly.set("Dolly", 0.0f, -100.0f, 100.0f);
    orientCamera.set("Orient Camera", true);
    camLookAt.set("Cam Look At", ofDefaultVec3(0, 0, 0), ofDefaultVec3(-100), ofDefaultVec3(100));
    camPan.set("Pan", 0.0f, -90.0f, 90.0f);
    camTilt.set("Tilt", 0.0f, -90.0f, 90.0f);
    camRoll.set("Roll", 0.0f, -90.0f, 90.0f);
    drawDepthTex.set("Draw Depth",false);
    

    guiPanel.add(camTruck);
    guiPanel.add(camBoom);
    guiPanel.add(camDolly);
    guiPanel.add(camTilt);
    guiPanel.add(drawDepthTex);

    

}

//--------------------------------------------------------------
void ofApp::update(){

    rsContext.update();
    
    cam.resetTransform();
    cam.truck(camTruck);
    cam.boom(camBoom);
    cam.dolly(camDolly);
    cam.tiltDeg(camTilt);
    
    cam.orbitDeg(<#float longitude#>, <#float latitude#>, <#float radius#>, <#ofNode &centerNode#>)
    
    std::shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
    colorPixels = rsDevice->getColorTex();
    
    ofPixels pixels = rsDevice->getColorPix();
    Mat transformedPix = toCv(pixels);
    //revisar esto
    objectFinder.update(pixels);
    auto camMatrix = cam.getProjectionMatrix();
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    std::shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
    if (rsDevice){
        
        ofBackground(0);
        cam.begin();
        ofScale(0.1f);
//        ofScale(2.3,2.3);
//        rsDevice->getColorTex().draw(0, 0);
        if(drawDepthTex){
          rsDevice->getDepthTex().draw(0,0);
        }else{
            
            //Crahing when hover on scale=0.1f;
            //        cout<<"Mouse X   " << ofGetMouseX();
            //        ofShortPixels rawDepthPix = rsDevice->getRawDepthPix();
            //        int depthAtMouse = rawDepthPix.getColor(ofGetMouseX(), ofGetMouseY()).r;
            //        ofDrawBitmapStringHighlight(ofToString(depthAtMouse), ofGetMouseX() + 16, ofGetMouseY() + 10);
            if(objectFinder.size() != 0){
                ofPushStyle();
//                ofSetColor(0);
//                ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
                rsDevice->getColorTex().draw(0,0);
                ofSetColor(255);
                ofDrawRectangle(objectFinder.getObject(0));
                ofPopStyle();
        }
        
        cam.end();
    }
    
    
    }
    guiPanel.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
