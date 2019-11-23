#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(960,540);
    rsContext.setup(true);
    
    ofSetFrameRate(10);
    
    translateX.set("Translate X",0,-100,100);
    translateY.set("Translate Y",0,-100,100);
    scaleFactor.set("Scale",1.0f, -5.0f, 5.0f);
    
    guiPanel.setup("Options","settings.json");
    guiPanel.add(translateX);
    guiPanel.add(translateY);
    guiPanel.add(scaleFactor);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

    rsContext.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    std::shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
    
    if(rsDevice){
        
        
        
        //scale from center and X&Y translation
        float videoWidth = rsDevice->getColorTex().getWidth();
        float videoHeight = rsDevice->getColorTex().getHeight();
        float windowWidth = ofGetWindowWidth();
        float windowHeight = ofGetWindowHeight();
        
//        ofTranslate((windowWidth-videoWidth*scaleAmount)/2, (windowHeight-videoHeight*scaleAmount)/2 );
//        ofScale(scaleAmount,scaleAmount,1);
//        ofTranslate(translateX, translateY);

        glm::mat4 mat;
//        mat = glm::translate(mat,glm::vec3(0.f,0.f,0.f));
//        mat = glm::scale(mat,glm::vec3(1.f,1.f,1.f));
//        mat = glm::translate(mat,glm::vec3(0.f,0.f,0.f));

        mat = glm::translate(mat,glm::vec3((windowWidth-videoWidth*scaleFactor)/2,
                                           (windowHeight-videoHeight*scaleFactor)/2,
                                           0.f));
        
        mat = glm::scale(mat,glm::vec3(scaleFactor,
                                       scaleFactor,
                                       1.f));
        
        mat = glm::translate(mat,glm::vec3(translateX,
                                           translateY,
                                           0.f));
        
        ofPushMatrix();
        ofMultMatrix(mat);
        
        //draw the color texture
//        rsDevice->getColorTex().draw(videoWidth,0,-videoWidth,videoHeight);
        
        rsDevice->getDepthTex().draw(videoWidth,0,-videoWidth,videoHeight);
        
        glm::vec4 globalMouse(ofGetMouseX(),ofGetMouseY(),0.f,1.f);
        glm::vec4 localMouse = glm::inverse(mat)*globalMouse;
        
        int boundedMouseX = ofClamp(localMouse.x, 0,videoWidth);
        int boundedMouseY = ofClamp(localMouse.y,0, videoHeight);

        float distance = rsDevice->getDistance(boundedMouseX, boundedMouseY);
        ofDrawBitmapStringHighlight(ofToString(distance), boundedMouseX,boundedMouseY);
        
        cout << "LocalX -> "<<localMouse.x <<"\nLocalY -> "<<localMouse.y<<"\n\n\n";
        
        ofRectangle rect(0,0,videoWidth, videoHeight);
        if(rect.inside(localMouse.x, localMouse.y)){
            cout<<"Mouse inside projected matrix";
        }
        
        ofPopMatrix();

        
        

        
//        ofShortPixels depthPixels = rsDevice->getRawDepthPix();
//        int depthAtMouse = depthPixels.getColor(ofGetMouseX(),ofGetMouseY()).r;
//         ofDrawBitmapStringHighlight(ofToString(depthAtMouse), ofGetMouseX() + 16, ofGetMouseY() + 10);
        
        ofPopMatrix();
        
    }
    
    if(drawPanel)guiPanel.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == ' '){
        drawPanel = !drawPanel;
    }

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
