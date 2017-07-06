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

		void setScaledColor(ofColor baseColor, int idStep, int minSteps, int maxSteps, int mode, bool invertOrder); //TODO With Floats will add mode detail

		void drawFloors(ofColor _mainColor, int _modedrawFloors, bool _invertOrder);

		void setupSomeInitColors();

		blob blobs[nBlob];

		//float transparency;
		ofxPanel gui;
		ofxToggle bRotated = true;
		ofxColorSlider myBackGroundColor;
		ofxColorSlider myBlobsColor, myBlobsColor2;
		ofxToggle bInvertPaletteColors = false;
		//ofxFloatSlider fboTail;

		ofxFloatSlider myBlobPropRespirationX;
		ofxFloatSlider myBlobPropRespirationY;
		ofxFloatSlider myBlobValPlusAngles;
		ofxFloatSlider myBlobLinewidth;
		ofxToggle	usePolylineMethods;
		ofxIntSlider myBlobSmooth;
		ofxIntSlider myBlobResampled;
		ofxToggle	myBlobBeFilled;
		ofxToggle	myBlobBeTriangleMesh;
		ofxIntSlider modeDrawFloors = 0;
		ofVec2f posFloor;
		ofVec2f dimFloor;

		ofFbo fbo;


};
