#pragma once

#include "ofMain.h"
#include "blob.h"
#include "ofxGui.h"

#define nBlob 10
#define nPussiere 20

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

		void drawFloors();

		void setupSomeInitColors();

		blob blobs[nBlob];
		poussiere poussieres[nPussiere];

		//float transparency;
		ofxPanel gui;
		ofxColorSlider myBackGroundColor1;
		ofxColorSlider myBlobsColor1, myBlobsColor2;

		ofVec2f posFloor;
		ofVec2f dimFloor;

		ofFbo fbo;


};
