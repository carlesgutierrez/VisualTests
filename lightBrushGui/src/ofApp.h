#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define howManyColors 3
#define howManyHistoryNoise 400

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void drawFloors(ofColor _mainColor, int _modedrawFloors, bool _invertOrder, bool _bRotated);

		void setScaledColor(ofColor baseColor, int idStep, int minSteps, int maxSteps, int mode, bool invertOrder);

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

		//Local funcs
		void updateTimer(float nextvalue);
		void updateBrush();

		void setupSignedNoiseDemo();
		void updateSignedNoiseDemo();

		///////
		//ColorBrush
		ofxIntSlider hightMoveDist;
		ofxIntSlider midMoveDist;
		ofxFloatSlider noiseStep;
		ofxFloatSlider noiseAmount;
		float signedNoiseData[howManyHistoryNoise];
		float radialNoiseCursor;
		bool bTimerActive = false;
		bool bClearBk = true;
		int timerActive = 0;
		float colorhue = 100;
		ofVec2f  posBrush;
		ofVec2f  dimBrush;

		///////
		//Noise1d
		float xoff = 0.0;
		float xincrement = 0.001;

		//
		ofxIntSlider sizeBrush;
		int singedInc = 1;
		ofxIntSlider ModeBlend;
		bool bInvertPaletteColors = false;
		//int modeDrawFloors;
		ofxIntSlider modeDrawFloors;
		//ofColor myBackGroundColor;
		ofxColorSlider myBackGroundColor;
		//ofColor myActionColor;
		ofxColorSlider myActionColor;
		ofxIntSlider alphaActionColor;
		ofxIntSlider alphaBkColor;

		/////
		//GUI
		ofxPanel gui;
		ofxFloatSlider sliderValue_Color;
		ofxFloatSlider sliderValue_IncMov;
		

		ofFbo fbo;
		ofFbo fboBack;

};
