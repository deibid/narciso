#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxRealSense2.h"
#include "ofxCv.h"
#include "Calibrator.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    
    int safeMouseX;
    int safeMouseY;
//
//    float videoWidth;
//    float videoHeight;
//    float windowWidth;
//    float windowHeight;
//
//    glm::mat4 mat;
    
    ofShortPixels maskPixels(ofShortPixels pixels, ofShortPixels mask);
    
    
    Calibrator calibrator;
    
    ofxRealSense2::Context rsContext;
    ofxPanel guiPanel;
    
    ofParameter<int> translateX;
    ofParameter<int> translateY;
    ofParameter<float> scaleFactor;
    
    ofParameter<int> nearBandThreshold;
    ofParameter<int> farBandThreshold;
    ofParameter<bool> drawDepth;
    
    ofParameter<bool> calibrationMode;
    long averageDepthInFrame;
    
    bool drawPanel = true;
    
    ofImage thresholdImage;
    
    
    
    
};
