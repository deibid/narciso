//#include "ofApp.h"
//
////--------------------------------------------------------------
//void ofApp::setup(){
//
//
//    //With calibrated settings for other screen
////    ofSetWindowPosition(1508, 45);
////    ofSetWindowShape(1470,930);
//
//    //for Planar screen, vertical
//    ofSetWindowPosition(-1080,0);
//    ofSetWindowShape(1280,800);
//    rsContext.setup(true);
//
//    ofSetFrameRate(10);
//
//    translateX.set("Translate X",0,-100,100);
//    translateY.set("Translate Y",0,-100,100);
//    scaleFactor.set("Scale",1.0f, -5.0f, 6.0f);
//    drawDepth.set("Show Depth",false);
//    nearBandThreshold.set("Near Depth",200,0,9000);
//    farBandThreshold.set("Far Depth",1000,0,9000);
//    calibrationMode.set("Calibration Mode",false);
//    playMode.set("Play Mode",false);
//
//
//    effectGroup.setName("Effects");
//    effectToggle.set("EffectToggle",true);
//    effectGroup.add(effectToggle);
//
//
//    guiPanel.setup("Options","settings.json");
//    guiPanel.add(translateX);
//    guiPanel.add(translateY);
//    guiPanel.add(scaleFactor);
//    guiPanel.add(drawDepth);
//    guiPanel.add(nearBandThreshold);
//    guiPanel.add(farBandThreshold);
//    guiPanel.add(calibrationMode);
//    guiPanel.add(playMode);
//    guiPanel.add(blurAmount.set("Blur",0,0,100));
//    guiPanel.add(effectGroup);
//
//
//
//
//    std::shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
//    if(rsDevice){
//        guiPanel.add(rsDevice->params);
//        rsDevice->holeFillingEnabled = true;
//        rsDevice->holeFillingMode = 1;
//        rsDevice->alignMode = 1;
//    }
//
//
//    thresholdImage.allocate(640,360,OF_IMAGE_GRAYSCALE);
//    ofBackground(0);
//
//    calibrator.readFile();
//
//
//}
//
////--------------------------------------------------------------
//void ofApp::update(){
//
//    rsContext.update();
//
//    if(playMode){
//
//        Keyframe k = calibrator.getScaleKeyframes(averageDepthInFrame);
//        scaleFactor.set(k.scale);
//        translateX.set(k.translateX);
//        translateY.set(k.translateY);
//
//    }
//
//    if(!effectToggle){
//        blurAmount = 0;
//    }else{
//        blurAmount = 12;
//    }
//
//}
//
////--------------------------------------------------------------
//void ofApp::draw(){
//
//    std::shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
//
//    if(true){
//
//
//        ofPixels pxs = rsDevice->getColorPix();
//        pxs.rotate90(3);
//        ofImage img;
//        img.setFromPixels(pxs);
//        img.draw(0,0);
//
//        float videoWidth = rsDevice->getColorTex().getWidth();
//        float videoHeight = rsDevice->getColorTex().getHeight();
//        float windowWidth = ofGetWindowWidth();
//        float windowHeight = ofGetWindowHeight();
//
//        ofLog(OF_LOG_NOTICE,"video Width: "+ ofToString(videoWidth));
//        ofLog(OF_LOG_NOTICE,"video height: " +ofToString(videoHeight));
//        ofLog(OF_LOG_NOTICE,"Window Width: "+ ofToString(windowWidth));
//        ofLog(OF_LOG_NOTICE,"window Height: "+ofToString(windowHeight));
//
//        return;
//
//
//
//    }
//
//
//    if(rsDevice){
//
//        //scale from center and X&Y translation
//        float videoWidth = rsDevice->getColorTex().getWidth();
//        float videoHeight = rsDevice->getColorTex().getHeight();
//        float windowWidth = ofGetWindowWidth();
//        float windowHeight = ofGetWindowHeight();
//
//        //        ofTranslate((windowWidth-videoWidth*scaleAmount)/2, (windowHeight-videoHeight*scaleAmount)/2 );
//        //        ofScale(scaleAmount,scaleAmount,1);
//        //        ofTranslate(translateX, translateY);
//
//        glm::mat4 mat;
//        mat = glm::translate(mat,glm::vec3((windowWidth-videoWidth*scaleFactor)/2,
//                                           (windowHeight-videoHeight*scaleFactor)/2,
//                                           0.f));
//        mat = glm::scale(mat,glm::vec3(scaleFactor, scaleFactor, 1.f));
//        mat = glm::translate(mat,glm::vec3(translateX, translateY, 0.f));
//
//        ofPushMatrix();
//        ofMultMatrix(mat);
//
//        glm::vec4 globalMouse(ofGetMouseX(),ofGetMouseY(),0.f,1.f);
//        glm::vec4 localMouse = glm::inverse(mat)*globalMouse;
//
//        safeMouseX = ofClamp(localMouse.x, 0,videoWidth);
//        safeMouseY = ofClamp(localMouse.y,0, videoHeight);
//
//
//
//        long numPixelsInRange = 0;
//        long sumOfPixelsInRange = 0;
//        averageDepthInFrame = 0;
//
//        ofShortPixels rawDepthPix = rsDevice->getRawDepthPix();
//        ofPixels& thresholdPix  = thresholdImage.getPixels();
//        for(int y=0; y<rawDepthPix.getHeight(); y++){
//            for(int x = 0; x<rawDepthPix.getWidth();x++){
//                int depth = rawDepthPix.getColor(x, y).r;
//                if(depth <= farBandThreshold && depth >= nearBandThreshold){
//
//                    float normPix = ofNormalize(depth, 0, 9000);
//
//                    int val;
//                    if(effectToggle){
//                        val = 255 - 255*normPix;
//                    }else{
//                        val = ofRandom(255);
//                    }
//
//                    thresholdPix.setColor(x, y, ofColor(val));
//                    numPixelsInRange++;
//                    sumOfPixelsInRange += depth;
//
//                }else{
//                    thresholdPix.setColor(x, y, 0);
//                }
//            }
//        }
//        //avoid division over 0 error
//        if(numPixelsInRange >0) averageDepthInFrame = sumOfPixelsInRange/numPixelsInRange;
//
//
//        if(!drawDepth){
//            rsDevice->getColorTex().draw(videoWidth,0,-videoWidth,videoHeight);
//        }else{
//
//            if(playMode){
//
//                for(int i = 0; i< (int)ofRandom(80);i++){
//                    ofPushStyle();
//                    ofSetColor(200, 200, 255);
//                    ofDrawCircle(ofRandom(videoWidth), ofRandom(videoHeight), 20);
//                    ofPopStyle();
//                }
//
//
//            }
//
//
//
//            ofxCv::medianBlur(thresholdImage,blurAmount);
//            thresholdImage.update();
//            thresholdImage.draw(videoWidth,0,-videoWidth,videoHeight);
////            thresholdImage.draw(0,0);
////            float depthAtMouse = rsDevice->getDistance(safeMouseX,safeMouseY);
////            ofDrawBitmapStringHighlight(ofToString(depthAtMouse), safeMouseX, safeMouseY);
//
//            std::string msg = "Average depth in frame: "+ofToString(averageDepthInFrame)+" mm";
//            ofDrawBitmapStringHighlight(msg,videoWidth-videoWidth/10,5);
//
//        }
//        ofPopMatrix();
//    }
//
//    if(drawPanel)guiPanel.draw();
//
//}
//
////--------------------------------------------------------------
//void ofApp::keyPressed(int key){
//
//    if(key == ' '){
//        drawPanel = !drawPanel;
//    }
//
//    if(key == 'a'){
//        Keyframe k1(1,100,20,40);
//        Keyframe k2(.2,400,20,40);
//        Keyframe k3(.6,500,20,45);
//
//        calibrator.addNewKeyframe(k1);
//        calibrator.addNewKeyframe(k2);
//        calibrator.addNewKeyframe(k3);
//    }
//    if(key =='b'){
//        calibrator.toString();
//        Keyframe k = calibrator.getScaleKeyframes(averageDepthInFrame);
//        k.toString();
////        cout<<"your result is -> "<<k.depth<<" depth at:   "<<k.scale<<"  scale" <<endl;
//    }
//
//    if(key == 'k'){
//
//        //get the ofParameter data and calculated depth whenever we add a keyframe to the calibration data.
//        if(calibrationMode){
//            Keyframe k(averageDepthInFrame, scaleFactor, translateX, translateY);
//            calibrator.addNewKeyframe(k);
//            calibrator.saveDataToFile();
//            k.toString();
//        }
//    }
//
//    if(key == 'f'){
////        calibrator.readFile();
//    }
//
//    if(key =='l'){
////        calibrator.saveDataToFile();
//    }
//
//    if(key == 'q'){
//        cout<<"Width "<<ofGetWindowWidth()<<endl;
//        cout<<"Height "<<ofGetWindowHeight()<<endl;
//        cout<<"X "<<ofGetWindowPositionX()<<endl;
//        cout<<"Y "<<ofGetWindowPositionY()<<endl;
//    }
//
//    if(key == '1'){
//        drawDepth.set(false);
//    }
//    if(key =='2'){
//        drawDepth.set(true);
//        effectToggle.set(true);
//    }
//    if(key == '3'){
//        drawDepth.set(true);
//        effectToggle.set(false);
//    }
//
//}
//
//
//
//void effectChangeListener(ofAbstractParameter& e){
//    cout<< "cambio"<<endl;
//}
//
////--------------------------------------------------------------
//void ofApp::keyReleased(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){
//
//
//
//
//    //Right Click, for saving a calibration keyframe
//    if(button == 2){
//
//        if(calibrationMode){
//            Keyframe k(averageDepthInFrame, scaleFactor, translateX, translateY);
//            calibrator.addNewKeyframe(k);
//            calibrator.saveDataToFile();
//            k.toString();
//        }
//
//    }
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){
//
//}
