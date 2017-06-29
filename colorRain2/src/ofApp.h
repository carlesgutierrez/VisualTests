#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define howMany 300
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

    void updateColors(int tail);
	void updateParticles();
    void drawParticle(float _x, float _y, float _speed);

    float x[howMany];
    float y[howMany];
    float speed[howMany];
	ofVec2f dir;
	ofVec2f pos[howMany];
	ofVec2f vel;
	float angle;

    bool bClearBk = true;
    ofColor myColors[howManyColors];
    ofColor myBackGroundColor1;

    ofxPanel gui;
	ofxIntSlider drawMode;
    ofxIntSlider tail;
	int last_tail;
	ofxFloatSlider sizeProportion;
	ofxIntSlider defaultSize;
	ofxToggle setSmoothing; //

    ofFbo fbo;


};
