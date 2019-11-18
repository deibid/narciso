#include "ofApp.h"


using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    objectFinder.setup("haarcascade_frontalface_default.xml");
    objectFinder.setPreset(ObjectFinder::Fast);
    
    ofSetWindowShape(640,360);
    rsContext.setup(true);
    
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

    rsContext.update();
    
    std::shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
    colorPixels = rsDevice->getColorTex();
    objectFinder.update(rsDevice->getColorPix());
    
    if(objectFinder.size() != 0){
        cout <<"Tengo algo en la bolsa \n";
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    std::shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
    if (rsDevice)
    {
    
        colorPixels.draw(0,0);
        
        if(objectFinder.size() != 0){
            ofPushStyle();
            ofSetColor(ofColor(200,100,100));
            ofDrawRectangle(objectFinder.getObject(0));
            ofPopStyle();
        }
        // Draw the depth texture.
        
//        rsDevice->getDepthTex().draw(0, 0);
    }

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
