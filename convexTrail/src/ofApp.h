#pragma once

#include "ofMain.h"
#include "ofxConvexHull.h"
#include "ofxImGui.h"
#include "convexTrailParticleManager.h"

#define NUMPOINTSBK 300

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
	void updateClosePoints(int _myPosX, int _myPosY, int distance, vector<ofPoint> _bkPoints, vector<ofPoint>& _closePoints);

	//Colors Interaction
	ImVec4 myBackGroundColor = ofColor(10, 10, 10, 255);
	ImVec4 myActionColor1 = ofColor(255, 0, 255, 255);
	ImVec4 myActionColor2 = ofColor(255, 0, 255, 255);
	int ModeBlend = 1;
	int alphaActionColor = 150;
	int alphaBkColor = 3;

	//////////////////////////////////
	//Convex Hull
	void resetBkPoints(); //bk points where to find main hulls

	void updateInteractiveData(vector<shared_ptr<ConvexTrailInteractionObject>> _myInteractiveObjects, ofPoint & valId, float & valId1);

	void updateConvexTrailWithInteractiveObjects();

	void drawGui();
	void drawAllConvexHulls();
	bool newHullTrail(vector<ofPoint> _hull1, vector<ofPoint> _hull2, int maxMachPoints, vector<ofPoint>&  _hullTrail);
	void drawConvexHull(vector<ofPoint> _myHull);
	
	//local vars
	int radialDistThreshold2Hull = 100;
	int distanceMoveThreshold = 100;
	int maxMatchInternalHullPoint = 3;
	ofxConvexHull convexHullTrail;
    ofxConvexHull convexHull;
    vector<ofPoint> pointsBk;
	vector<ofPoint> closePoints;

	vector<ofPoint> hull1;
	ofPolyline polyHull1;
	vector<ofPoint> hull2;
	ofPolyline polyHull2;
	vector<ofPoint> trailHull;

	//
	bool bDegubMode = true;
	bool bRoundVertexes = false;

	///Interactive Class
	convexTrailParticleMode noiseInteractionMethod = CONVEXTRAIL_PARTICLE_MODE_NOISE_WALKER;
	convexTrailParticleManager myInteractiveDataClass;

	////
	//GUI
	//ofxImGui gui;
	ofxImGui::Gui myMainGui;

	//FBO
	ofFbo fbo;

};
