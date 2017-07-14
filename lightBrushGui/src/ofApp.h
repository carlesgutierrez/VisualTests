#pragma once

#include "ofMain.h"
#include "LigthBrushParticleManager.h"
#include "ofxImGui.h"
#include "ofxColorGradient.h"
#include "ofxEasing.h"
#include "imGuiUtils.h"

#define howManyColors 3
#define howManyHistoryNoise 400

enum lightBrushNoiseMode {
	LIGHTBRUSH_NOISEMODE_1D = 0,
	LIGHTBRUSH_NOISEMODE_WALKERS
};

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

		//Local funcs
		void resetColorGradient();
		float updateTimer(float nextvalue);
		ofColor updateColorAction(int _modeColorAction, ofColor _colorAction, float _yNormPos1, float _yNormPos2);
		void updateBrush();

		void setupSignedNoiseDemo();
		void updateSignedNoiseDemo();

		void updateInteractiveData(vector<shared_ptr<LightBrushInteractionObject>> _myInteractiveObjects, float &Ypos, float & auxColorComponent);

		///////
		//ColorBrush
		int modeColorAction = 1;
		float distMovement = 0;
		int hightMoveDist = 5;
		int midMoveDist = 2;
		float noiseStep= 0.002;
		float noiseAmount = 1;
		float signedNoiseData[howManyHistoryNoise];
		float radialNoiseCursor;
		
		ofxColorGradient<ofColor> myGradientColor;
		float colorhue = 100;
		float colorBrightNess = 255;
		ofVec2f  posBrush;
		ofVec2f  dimBrush;

		///////
		//Interaction Sensor
		
		lightBrushNoiseMode noiseInteractionMethod = LIGHTBRUSH_NOISEMODE_WALKERS;
		int currentInteractionMethod = noiseInteractionMethod;
		LigthBrushParticleManager myInteractiveDataClass;

		int sizeBrush = ofGetHeight()/8;
		int incMinValue = 1;
		int incMaxValue = 2;
		int singedInc = 1;
		int ModeBlend = 1;
		bool bInvertPaletteColors = false;

		//////
		//Colors Interaction
		ImVec4 myBackGroundColor = ofColor(10, 10, 10, 255);
		ImVec4 myActionColor = ofColor(255, 0, 255, 255);

		ImVec4 myCompositionColor1 = ofColor::red;
		ImVec4 myCompositionColor2 = ofColor::green;
		ImVec4 myCompositionColor3 = ofColor::blue;

		int alphaActionColor = 150;
		int alphaBkColor = 3;

		/////
		//Easing Vars
		int selectedEasingId = 0;
		bool bInvertEasing = false;
		std::vector<ofxeasing::function> easings{
			ofxeasing::linear::easeOut,
			ofxeasing::quad::easeOut,
			ofxeasing::cubic::easeOut,
			ofxeasing::quart::easeOut,
			ofxeasing::quint::easeOut,
			ofxeasing::circ::easeOut,
			ofxeasing::sine::easeOut,
			ofxeasing::exp::easeOut,
			ofxeasing::elastic::easeOut,
			ofxeasing::bounce::easeOut,
			ofxeasing::back::easeOut,
		};
		std::vector<std::string> easingNames{
			"linear",
			"quad",
			"cubic",
			"quart",
			"quint",
			"circ",
			"sine",
			"exp",
			"elastic",
			"bounce",
			"back",
		};
		std::vector<ofVboMesh> plots{ easings.size() };

		/////
		//GUI
		//ofxImGui gui;
		ofxImGui::Gui myMainGui;
		

		ofFbo fbo;

};
