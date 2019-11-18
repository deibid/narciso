#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(INIT_WIDTH,INIT_HEIGHT);
    rsContext.setup(true);
    ofBackground(0);
    

    objectFinder.setup(ofToDataPath("haarcascade_frontalface_default.xml"));
    objectFinder.setPreset(ofxCv::ObjectFinder::Accurate);
    
    image.allocate(ofGetWidth(),ofGetHeight(),OF_IMAGE_COLOR);

//    useCamera.set("Use Camera",false);
//    camPosition.set("Camera Position", glm::vec3(0, 0, 90), glm::vec3(-100), glm::vec3(100));
    camTruck.set("Truck",0.0f,-100.0f,100.0f);
    camBoom.set("Boom",0.0f,-100.0f,100.0f);
    camDolly.set("Dolly",0.0f,-100.0f,100.0f);
    orientCamera.set("Orient Camera",true);
    camLookAt.set("Look At",ofDefaultVec3(0,0,0),ofDefaultVec3(-100),ofDefaultVec3(100));
    camPan.set("Pan",0.0,-90.0f,90.0f);
    camTilt.set("Tilt",0.0f,-90.0f,90.0f);
    camRoll.set("Roll",0.0f,-90.0f,90.0f);
    drawSquare.set("Draw Square",false);
    
    
    guiPanel.setup("Narciso Settings","settings.json");
    guiPanel.add(camPosition);
    guiPanel.add(camTruck);
    guiPanel.add(camBoom);
    guiPanel.add(camDolly);
    guiPanel.add(orientCamera);
    guiPanel.add(camLookAt);
    guiPanel.add(camPan);
    guiPanel.add(camTilt);
    guiPanel.add(camRoll);
    guiPanel.add(drawSquare);
    
    
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    rsContext.update();
    
    
    viewCamera.resetTransform();
    
//    viewCamera.setPosition(camPosition);
    viewCamera.truck(camTruck);
    viewCamera.boom(camBoom);
    viewCamera.dolly(camDolly);
    
    if(orientCamera){
//        viewCamera.lookAt(camLookAt);
        viewCamera.panDeg(camPan);
        viewCamera.tiltDeg(camTilt);
        viewCamera.rollDeg(camRoll);
    }
    
    objectFinder.update(rsContext.getDevice(0)->getColorTex());
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    viewCamera.begin();
    ofScale(0.1f);
    ofScale(-1,1);
    
    std::shared_ptr<ofxRealSense2::Device> rsCam = rsContext.getDevice(0);
    
    if(rsCam){
//        rsCam->getColorTex().draw(0,0,1920,1200);
        rsCam->getColorTex().draw(0,0,INIT_WIDTH,INIT_HEIGHT);
    }else{
        ofLog(OF_LOG_VERBOSE,"No hay camara");
    }
    
    
    if(drawSquare){
        ofPushStyle();
        ofSetColor(255);
        ofDrawRectangle(ofGetWidth()/2,ofGetHeight()/2,200,200);
        ofSetColor(0);
        ofDrawRectangle(ofGetWidth()/4,ofGetHeight()/4,200,200);
        ofPopStyle();
    }
    
    
    viewCamera.end();
    
    
    
    
    
    
    guiPanel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    
    cout << ofGetWidth();
    cout << "by  ";
    cout << ofGetHeight();
    cout << '\n';
    
    
    cout << ofGetWindowPositionX();
    cout << ",  ";
    cout << ofGetWindowPositionY();
    cout << '\n';

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


