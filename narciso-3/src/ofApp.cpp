#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(960,540);
    rsContext.setup(true);
    
    translateX.set("Translate X",0,-100,100);
    translateY.set("Translate Y",0,-100,100);
    scaleAmount.set("Scale",1.0f, -5.0f, 5.0f);
    
    guiPanel.setup("Options","settings.json");
    guiPanel.add(translateX);
    guiPanel.add(translateY);
    guiPanel.add(scaleAmount);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

    rsContext.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    std::shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
    if(rsDevice){
        ofPushMatrix();

        float videoWidth = rsDevice->getColorTex().getWidth();
        float videoHeight = rsDevice->getColorTex().getHeight();
        float windowWidth = ofGetWindowWidth();
        float windowHeight = ofGetWindowHeight();
        
        
//        ofTranslate(videoWidth,0);
        
        
        ofTranslate((windowWidth-videoWidth*scaleAmount)/2, (windowHeight-videoHeight*scaleAmount)/2 );
        ofScale(scaleAmount,scaleAmount,1);
        
        ofTranslate(translateX, translateY);
        
        rsDevice->getColorTex().draw(videoWidth,0,-videoWidth,videoHeight);
        ofPopMatrix();
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
