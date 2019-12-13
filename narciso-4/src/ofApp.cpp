#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    

    //With calibrated settings for other screen
//    ofSetWindowPosition(1508, 45);
//    ofSetWindowShape(1470,930);
    
    //for Planar screen, vertical
    ofSetWindowPosition(-1080,0);
    ofSetWindowShape(1080,1920);
    rsContext.setup(true);
    
//    ofSetFrameRate(10);
    
    translateX.set("Translate X",0,-1000,1000);
    translateY.set("Translate Y",0,-1000,1000);
    scaleFactor.set("Scale",1.0f, -5.0f, 10.0f);
    drawDepth.set("Show Depth",false);
    nearBandThreshold.set("Near Depth",200,0,9000);
    farBandThreshold.set("Far Depth",1000,0,9000);
    calibrationMode.set("Calibration Mode",false);
    playMode.set("Play Mode",false);
    
    
    effectGroup.setName("Effects");
    effectToggle.set("EffectToggle",true);
    effectNumber.set("Effect Number",2,1,9);
    effectGroup.add(effectToggle);
    effectGroup.add(effectNumber);

    
    guiPanel.setup("Options","settings.json");
    guiPanel.add(translateX);
    guiPanel.add(translateY);
    guiPanel.add(scaleFactor);
    guiPanel.add(drawDepth);
    guiPanel.add(nearBandThreshold);
    guiPanel.add(farBandThreshold);
    guiPanel.add(calibrationMode);
    guiPanel.add(playMode);
    guiPanel.add(blurAmount.set("Blur",0,0,100));
    guiPanel.add(effectGroup);
    
    
    
    
    rsDevice = rsContext.getDevice(0);
    if(rsDevice){
        deviceConnected = true;
    }
    
    if(deviceConnected){
        guiPanel.add(rsDevice->params);
        rsDevice->holeFillingEnabled = true;
        rsDevice->holeFillingMode = 1;
        rsDevice->alignMode = 2;
    }
    
    
    thresholdImage.allocate(360,640,OF_IMAGE_GRAYSCALE);
    ofBackground(0);
    
    calibrator.readFile();
    
    
    ofFboSettings fboSettings;
    fboSettings.width = 360;
    fboSettings.height = 640;
    fbo.allocate(fboSettings);
    
    font.load("TurretRoad-Regular.ttf",16,true,true,true,0.f);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    rsContext.update();
    
    if(deviceConnected){
        //inverted video dimensions to account for the fliped image (vertical mirror)
        videoWidth = rsDevice->getColorTex().getHeight();
        videoHeight = rsDevice->getColorTex().getWidth();
        windowWidth = ofGetWindowWidth();
        windowHeight = ofGetWindowHeight();
        
        calculateAverageDepthInFrame();
        
        if(playMode){
               
            Keyframe k = calibrator.getScaleKeyframes(averageDepthInFrame);
            scaleFactor.set(k.scale);
            translateX.set(k.translateX);
            translateY.set(k.translateY);
               
               
        }
        if(!effectToggle){
            blurAmount = 0;
        }else{
            blurAmount = 12;
        }
           
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    //VERY dirty exceptional case. This is to see the text on the absolute coordinates.
    if(effectNumber ==8){
        
        if(effectNumber != prevEffectNumber){
            activeMessage = getRandomString();
            prevEffectNumber = effectNumber;
        }
        
        
        ofBackground(0);
        ofRectMode(OF_RECTMODE_CENTER);
//        ofDrawBitmapStringHighlight(activeMessage, ofGetWidth()/2,ofGetHeight()/2);
        font.drawStringCentered(activeMessage, ofGetWidth()/2,200);
        
        return;
    }
    
    if(deviceConnected){
    
        //Draw setup
        glm::mat4 mat;
        mat = glm::translate(mat,glm::vec3((windowWidth-videoWidth*scaleFactor)/2,
                                           (windowHeight-videoHeight*scaleFactor)/2,
                                           0.f));
        mat = glm::scale(mat,glm::vec3(scaleFactor, scaleFactor, 1.f));
        mat = glm::translate(mat,glm::vec3(translateX, translateY, 0.f));
    
        
        ofPushMatrix();
        ofMultMatrix(mat);
//        ofDrawRectangle(0, 0, 50, 50);
        glm::vec4 globalMouse(ofGetMouseX(),ofGetMouseY(),0.f,1.f);
        glm::vec4 localMouse = glm::inverse(mat)*globalMouse;
        
        safeMouseX = ofClamp(localMouse.x, 0,videoWidth);
        safeMouseY = ofClamp(localMouse.y,0, videoHeight);
        //Draw setup

    
        //raw depth data from the camera
        ofShortPixels rawDepthPix = rsDevice->getRawDepthPix();
        
        //pixels containing the depth mask with the depth pixel value
        ofPixels& thresholdPix  = getThresholdPixels();
        
        
        
        switch(effectNumber){
            case 1:{
                thresholdImage.update();
                ofxCv::medianBlur(thresholdImage,blurAmount);
                thresholdImage.update();
                thresholdImage.draw(videoWidth,0,-videoWidth,videoHeight);
                break;
            }
            case 2:{
                
                ofPixels pxs = rsDevice->getColorPix();
                pxs.rotate90(1);
                ofImage img;
                img.setFromPixels(pxs);
                img.draw(videoWidth,0,-videoWidth,videoHeight);
                break;
            }
                
            case 3:{
                ofImage noiseImage = generateNoiseEffect();
                noiseImage.draw(videoWidth,0,-videoWidth,videoHeight);
                break;
            }
                
            case 4:{
                ofImage solidRainbowImage = generateSolidRainbowEffect();
                solidRainbowImage.draw(videoWidth,0,-videoWidth,videoHeight);
                break;
            }
            
            case 5:{
            
                if(ofRandom(0,1000)>900){
                    ofImage noiseImage = generateNoiseEffect();
                    noiseImage.draw(videoWidth,0,-videoWidth,videoHeight);
                }else{
                    ofBackground(0);
                }
                break;
            }
                
            case 6:{
                
                ofPushStyle();
                ofBackground(30, 100, 100);
                ofPopStyle();
                
//                    ofImage aroundSubjectBoxEffectImage = generateAroundSubjectBoxEffect();
//                    aroundSubjectBoxEffectImage.draw(videoWidth,0,-videoWidth,videoHeight);
                break;
            }
            case 7:{
                backgroundImage.draw(videoWidth,0,-videoWidth,videoHeight);
                break;
             }
            }
                
        }
        
        
        
        
        ofPopMatrix();
        if(drawPanel)guiPanel.draw();
        return;
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
        Keyframe k = calibrator.getScaleKeyframes(averageDepthInFrame);
        k.toString();
//        cout<<"your result is -> "<<k.depth<<" depth at:   "<<k.scale<<"  scale" <<endl;
    }
    
    if(key == 'k'){
        
        //get the ofParameter data and calculated depth whenever we add a keyframe to the calibration data.
        if(calibrationMode){
            Keyframe k(averageDepthInFrame, scaleFactor, translateX, translateY);
            calibrator.addNewKeyframe(k);
            calibrator.saveDataToFile();
            k.toString();
        }
    }
    
    if(key == 'f'){
//        calibrator.readFile();
    }
    
    if(key =='l'){
//        calibrator.saveDataToFile();
    }
    
    if(key == 'q'){
        cout<<"Width "<<ofGetWindowWidth()<<endl;
        cout<<"Height "<<ofGetWindowHeight()<<endl;
        cout<<"X "<<ofGetWindowPositionX()<<endl;
        cout<<"Y "<<ofGetWindowPositionY()<<endl;
        cout<<"videoWidth "<<videoWidth<<endl;
        cout<<"videoHeight "<<videoHeight<<endl;
    }
    
    if(key == 's'){
        ofPixels backgroundPixels =  rsDevice->getColorPix();
        backgroundPixels.rotate90(1);
        backgroundImage.setFromPixels(backgroundPixels);
    }
    if(key == '1'){
        effectNumber = 1;
    }
    if(key =='2'){
        effectNumber = 2;
    }
    if(key == '3'){
        effectNumber = 3;
    }
    if(key == '4'){
        effectNumber = 4;
    }
    if(key == '5'){
        effectNumber = 5;
    }
    if(key =='6'){
        effectNumber = 6;
    }
    if(key =='7'){
        effectNumber = 7;
    }
    if(key =='8'){
        effectNumber = 8;
        prevEffectNumber = 1;
    }
    
}



void effectChangeListener(ofAbstractParameter& e){
    cout<< "cambio"<<endl;
}

//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
    
    
    //Right Click, for saving a calibration keyframe
    if(button == 2){
        
        if(calibrationMode){
            Keyframe k(averageDepthInFrame, scaleFactor, translateX, translateY);
            calibrator.addNewKeyframe(k);
            calibrator.saveDataToFile();
            k.toString();
        }
        
    }
    
}



long ofApp::calculateAverageDepthInFrame(){
    
    long numPixelsInRange = 0;
    long sumOfPixelsInRange = 0;
    averageDepthInFrame = 0;
    
    ofShortPixels rawDepthPix = rsDevice->getRawDepthPix();
    
    ofPixels& thresholdPix  = thresholdImage.getPixels();
    
        
    for(int y=0; y<rawDepthPix.getHeight(); y++){
        for(int x = 0; x<rawDepthPix.getWidth();x++){
           
            int depth = rawDepthPix.getColor(x, y).r;
            if(depth <= farBandThreshold && depth >= nearBandThreshold){
                numPixelsInRange++;
                sumOfPixelsInRange += depth;
            }
        }
    }
    //avoid division over 0 error
    if(numPixelsInRange >0){
      averageDepthInFrame = sumOfPixelsInRange/numPixelsInRange;
    }
    
}


ofPixels& ofApp::getThresholdPixels(){
    
    ofShortPixels rawDepthPix = rsDevice->getRawDepthPix();
    rawDepthPix.rotate90(1);
    
    ofPixels& thresholdPix  = thresholdImage.getPixels();
//    thresholdPix.rotate90(1);
    
    
    
    for(int y=0; y<rawDepthPix.getHeight(); y++){
        for(int x = 0; x<rawDepthPix.getWidth();x++){
            
            int depth = rawDepthPix.getColor(x, y).r;
            if(depth <= farBandThreshold && depth >= nearBandThreshold){
                
                float normPix = ofNormalize(depth, 0, 9000);
                int val;
                val = 255 - 255*normPix;
                thresholdPix.setColor(x, y, ofColor(val));
                
            }else{
                thresholdPix.setColor(x, y, ofColor(0));
            }
        }
    }
    
    return thresholdPix;
    
}

ofImage ofApp::generateNoiseEffect(){
    
    ofImage img;
    img.allocate(videoWidth,videoHeight,OF_IMAGE_GRAYSCALE);
    ofPixels& pixels = img.getPixels();
    ofPixels& thresholdPix  = getThresholdPixels();
    
    
    for(int y=0; y<thresholdPix.getHeight(); y++){
        for(int x = 0; x<thresholdPix.getWidth();x++){
            
            int depth = thresholdPix.getColor(x, y).r;
            if(depth != 0){
                pixels.setColor(x, y, ofColor(ofRandom(0,255)));
            }else{
                pixels.setColor(x, y, ofColor(0));
            }
        }
    }
    return img;
}
    
ofImage ofApp::generateSolidRainbowEffect(){
     
     ofImage img;
     img.allocate(videoWidth,videoHeight,OF_IMAGE_COLOR);
    
     ofPixels& pixels = img.getPixels();
     ofPixels& thresholdPix  = getThresholdPixels();

    
    for(int i = 0; i<thresholdPix.size(); i++){
        int depth = thresholdPix.getColor(i).r;
        int subpix = i+i*(pixels.getNumChannels()-1);
        
        
        
        if(depth != 0){
        
            float n = sin(ofGetElapsedTimeMillis()/10.0);
            int r = 184 + ofMap(n,0,1,-20,20);
            int g = 51 + ofMap(n,0,1,-20,20);
            int b = 95 + ofMap(n,0,1,-20,20);
            
            try{
                pixels.setColor(subpix, r);
                pixels.setColor(subpix+1, g);
                pixels.setColor(subpix+2, b);
            }catch(const std::exception &e){
                
            }
            
        }else{
            try{
                pixels.setColor(subpix, 0);
                pixels.setColor(subpix+1, 0);
                pixels.setColor(subpix+2, 0);
            }catch(const std::exception &e){
                
            }
        }
    }
     return img;
 }



//This effect needs to actually work
ofImage ofApp::generateAroundSubjectBoxEffect(){
    
    ofImage img;
//    img.allocate(videoWidth,videoHeight,OF_IMAGE_COLOR);
//    fbo.begin();
//    ofBackground(0);
//    ofSetColor(100,100,200);
//    ofDrawRectangle(0, 0, videoWidth, videoHeight);
//    fbo.end();
//
//
//    ofShortPixels rawDepthPix = rsDevice->getRawDepthPix();
//    rawDepthPix.rotate90(1);
//    ofPixels thresholdPix  = thresholdImage.getPixels();
//    for(int y=0; y<rawDepthPix.getHeight(); y++){
//        for(int x = 0; x<rawDepthPix.getWidth();x++){
//            int depth = rawDepthPix.getColor(x, y).r;
//            if(depth <= farBandThreshold && depth >= nearBandThreshold){
//                thresholdPix.setColor(x, y, ofColor(0));
//            }else{
//                thresholdPix.setColor(x, y, ofColor(255));
//            }
//        }
//    }
//
//    fbo.getTexture();
//    ofPixels res;
//    ofPixels texturePix;
//    fbo.readToPixels(texturePix);
//
//
//    ofxCv::bitwise_and(texturePix, thresholdPix, res);
//
    
    
    
    return img;
    
}


std::string ofApp::getRandomString(){
    
    std::vector<std::string> messages = {
      "you smell nice",
      "uno, dos, tres, cuatro, cinco",
      "tell me, what do you see?",
      "mirror, mirror..... who's gonna save the world?",
      "a single strand of spaghetti is called a spaghetto",
      "do you have a cigarette?",
      "hi,",
      "bless you",
      "alguna vez te han dicho que te aman?",        
    };
    
    return messages[ofRandom(messages.size())];
    
    
}
    
    

