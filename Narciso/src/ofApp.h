#pragma once

#include "ofMain.h"
#include "ofxRealSense2.h"
#include "ofxPanel.h"

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
    
    
    ofxRealSense2::Context rsContext;
    ofParameter<float> scaleZ;
    ofxPanel guiPanel;
    
    
    const int INIT_WIDTH = 1920;
    const int INIT_HEIGHT = 1200;
    
    
		
};
