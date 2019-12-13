#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxRealSense2.h"
#include "ofxCv.h"
#include "Calibrator.h"
#include "ofxCenteredTrueTypeFont.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    
    
    long calculateAverageDepthInFrame();
    ofPixels& getThresholdPixels();
    
    ofImage generateNoiseEffect();
    ofImage generateSolidRainbowEffect();
    ofImage generateAroundSubjectBoxEffect();
    std::string getRandomString();
    std::string activeMessage;
    
    ofxCenteredTrueTypeFont font;
    
    int safeMouseX;
    int safeMouseY;
    
    Calibrator calibrator;
    
    ofxRealSense2::Context rsContext;
    std::shared_ptr<ofxRealSense2::Device> rsDevice;
    bool deviceConnected = false;
    
    
    
    float videoWidth;
    float videoHeight;
    float windowWidth;
    float windowHeight;
    
    ofFbo fbo;
    
    
    ofxPanel guiPanel;
    
    ofParameter<int> translateX;
    ofParameter<int> translateY;
    ofParameter<float> scaleFactor;
    
    ofParameter<int> nearBandThreshold;
    ofParameter<int> farBandThreshold;
    ofParameter<bool> drawDepth;
    
    ofParameter<bool> calibrationMode;
    ofParameter<bool> playMode;
    
    
    
    long averageDepthInFrame;
    
    bool drawPanel = true;
    
    ofImage thresholdImage;
    ofImage backgroundImage;
    
    ofParameter<int> blurAmount;
    
    ofParameterGroup effectGroup;
    ofParameter<bool> effectToggle;
    ofParameter<int> effectNumber;

    int prevEffectNumber = 1;
    
    
    
    
    
    
};
