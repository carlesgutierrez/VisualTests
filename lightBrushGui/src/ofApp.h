#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define howManyColors 3

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

		void updateTimer(float nextvalue);
		void updateBrush();
		///////
		//ColorBrush
		Boolean bTimerActive = false;
		Boolean bClearBk = true;
		int timerActive = 0;
		float colorhue = 100;
		ofVec2f  posBrush;
		ofVec2f  dimBrush;

		///////
		//Noise1d
		float xoff = 0.0;
		float xincrement = 0.001;

		//

		ofColor myColors[howManyColors];
		ofColor myBackGroundColor1;

		/////
		//GUI
		ofxPanel gui;
		ofxFloatSlider sliderValue_Color;
		ofxFloatSlider sliderValue_IncMov;


};
