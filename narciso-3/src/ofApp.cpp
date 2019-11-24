#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(960,540);
    rsContext.setup(true);
    
    ofSetFrameRate(10);
    
    translateX.set("Translate X",0,-100,100);
    translateY.set("Translate Y",0,-100,100);
    scaleFactor.set("Scale",1.0f, -5.0f, 5.0f);
    drawDepth.set("Show Depth",false);
    nearBandThreshold.set("Near Depth",0.01f,0.f,0.1f);
    farBandThreshold.set("Far Depth",0.02,0.f,0.1f);
    
    
    
    guiPanel.setup("Options","settings.json");
    guiPanel.add(translateX);
    guiPanel.add(translateY);
    guiPanel.add(scaleFactor);
    guiPanel.add(drawDepth);
    guiPanel.add(nearBandThreshold);
    guiPanel.add(farBandThreshold);
    
    
    std::shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
    if(rsDevice){
        guiPanel.add(rsDevice->params);
    }
    
    

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
        mat = glm::translate(mat,glm::vec3((windowWidth-videoWidth*scaleFactor)/2,
                                           (windowHeight-videoHeight*scaleFactor)/2,
                                           0.f));
        mat = glm::scale(mat,glm::vec3(scaleFactor, scaleFactor, 1.f));
        mat = glm::translate(mat,glm::vec3(translateX, translateY, 0.f));
        
        ofPushMatrix();
        ofMultMatrix(mat);
        
        
        if(!drawDepth){
            rsDevice->getColorTex().draw(videoWidth,0,-videoWidth,videoHeight);
        }else{
            ofShortPixels rawDepthPixels = rsDevice->getRawDepthPix();
            ofShortPixels near, far, mask;
            
            ofxCv::threshold(rawDepthPixels, near, nearBandThreshold);
            ofxCv::threshold(rawDepthPixels, far, farBandThreshold,true);
            ofxCv::bitwise_and(near,far,mask);
            
//            cout<<"mask channels: "<<mask.getNumChannels();
//            cout<<"depth channels: "<<rawDepthPixels.getNumChannels();
            
            cout<<"mask width: "<<mask.getWidth() << "  mask height: "<<mask.getHeight()<<endl;
            cout<<"depth width: "<<rawDepthPixels.getWidth() << "  depth height: "<<rawDepthPixels.getHeight()<<endl;

            
            ofShortPixels rawShorts = rsDevice->getRawDepthPix();
            ofShortPixels maskedShortPixels = maskPixels(rawShorts, mask);
            thresholdImage.setFromPixels(maskedShortPixels);
            thresholdImage.draw(videoWidth,0,-videoWidth,videoHeight);
            
            
//            thresholdImage.setFromPixels(mask);
//            thresholdImage.draw(videoWidth,0,-videoWidth,videoHeight);
            
//            ofFloatPixels maskedDepthPixels = maskFloatPixels(rawDepthPixels, mask);
//            thresholdImage.setFromPixels(maskedDepthPixels);
//            thresholdImage.draw(videoWidth,0,-videoWidth,videoHeight);
            
        }
        
        
        
        glm::vec4 globalMouse(ofGetMouseX(),ofGetMouseY(),0.f,1.f);
        glm::vec4 localMouse = glm::inverse(mat)*globalMouse;
        
        int boundedMouseX = ofClamp(localMouse.x, 0,videoWidth);
        int boundedMouseY = ofClamp(localMouse.y,0, videoHeight);
        
        ofShortPixels depthPixels = rsDevice->getRawDepthPix();
        int depthAtMouse = depthPixels.getColor(boundedMouseX, boundedMouseY).r;
        ofDrawBitmapStringHighlight(ofToString(depthAtMouse), boundedMouseX, boundedMouseY);
    
        ofRectangle rect(0,0,videoWidth, videoHeight);
        if(rect.inside(localMouse.x, localMouse.y)){
            cout<<"Mouse inside projected matrix";
        }
        
        ofPopMatrix();

    }
    
    if(drawPanel)guiPanel.draw();

}


ofShortPixels ofApp::maskPixels(ofShortPixels pixels, ofShortPixels mask){
    
    
    ofShortPixels result;
    result.allocate(pixels.getWidth(), pixels.getHeight(), pixels.getNumChannels());
    
    for(int i = 0; i<pixels.size(); i++){
        result[i] = pixels[i] * mask[i];
//        float p = pixels.getColor(i).r;
//        cout<<p<<endl;
//        float m = mask.getColor(i).r;
//        float res = p*m;
////        if(m != 0){
////            cout<<"match"<<endl;
////        }
//        result[i] = res;
    }
    
    return result;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == ' '){
        drawPanel = !drawPanel;
    }
    
    if(key == 'a'){
        Keyframe k1(1,100,20,40);
        Keyframe k2(.2,400,20,40);
        Keyframe k3(.6,500,20,45);
        
        calibrator.addNewKeyframe(k1);
        calibrator.addNewKeyframe(k2);
        calibrator.addNewKeyframe(k3);        
    }
    if(key =='b'){
        calibrator.toString();
        Keyframe k = calibrator.getScaleKeyframes(1.7);
        cout<<"your result is -> "<<k.depth<<" depth at:   "<<k.scale<<"  scale" <<endl;
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
