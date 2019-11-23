#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxRealSense2.h"
#include "ofxGui.h"

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
    
    
    
    ofxCv::ObjectFinder objectFinder;
    
    ofxRealSense2::Context rsContext;
    
    ofTexture colorPixels;
    
    ofCamera cam;
    ofxPanel guiPanel;
    ofParameter<float> camTilt;
    ofParameter<bool> drawDepthTex;
    
    ofParameter<glm::vec3> camPosition;
    ofParameter<float> camTruck;
    ofParameter<float> camBoom;
    ofParameter<float> camDolly;
    ofParameter<bool> orientCamera;
    ofParameter<glm::vec3> camLookAt;
    ofParameter<float> camPan;
//    ofParameter<float> camTilt;
    ofParameter<float> camRoll;
    
    ofParameter<bool> useCamera;
    
    
    
		
};
