#pragma once

#include "ofMain.h"
#include "ofxConvexHull.h"
#include "ofxImGui.h"

#define NUMPOINTSBK 100

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


	//local Func
		void drawGui();
	void drawConvexHull();
	//Colors Interaction
	ImVec4 myBackGroundColor = ofColor(10, 10, 10, 255);
	ImVec4 myActionColor = ofColor(255, 0, 255, 255);
	int ModeBlend = 1;
	int alphaActionColor = 150;
	int alphaBkColor = 3;

	//////////////////////////////////
	//Convex Hull
	void resetBkPoints();
	void updateClosePoints(int _myPosX, int _myPosY, int distance, vector<ofPoint> _bkPoints, vector<ofPoint>& _closePoints);

	//local vars
	int distanceThreshold = 500;
    ofxConvexHull convexHull;
    vector<ofPoint> pointsBk;
	vector<ofPoint> closePoints;

	vector<ofPoint> hull1;
	vector<ofPoint> hull2;

	////
	//GUI
	//ofxImGui gui;
	ofxImGui::Gui myMainGui;

	//FBO
	ofFbo fbo;

};
