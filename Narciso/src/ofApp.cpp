#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(INIT_WIDTH,INIT_HEIGHT);
    rsContext.setup(true);
    ofBackground(0);
    
    
    scaleZ.set("Zoom",1.0f, 0.0f, 2.0f);
    guiPanel.setup("Narciso Settings","settings.json");
    guiPanel.add(scaleZ);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    rsContext.update();

    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    std::shared_ptr<ofxRealSense2::Device> rsCam = rsContext.getDevice(0);
    
    if(rsCam){
        
        ofScale(scaleZ,scaleZ,scaleZ);
        ofTranslate((INIT_WIDTH-ofGetWidth())/2,(INIT_HEIGHT-ofGetHeight())/2);
        
        rsCam->getColorTex().draw(0,0,1920,1200);
    }else{
        ofLog(OF_LOG_VERBOSE,"No hay camara");
    }
    
    
    ofScale(1,1,1);
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
