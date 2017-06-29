#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define howMany 300
#define howManyColors 3

class ofApp : public ofBaseApp{

public:
	void setupParticles();
	void setAngle2Velocity(float angle);
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
	void updateDrawParticles();
    void drawParticle(float _x, float _y, float _speed);

    float x[howMany];
    float y[howMany];
    float speed[howMany];
	ofVec2f dir;
	ofVec2f pos[howMany];
	ofVec2f vel[howMany];
	float angle;
	int gap = 30;

    bool bClearBk = true;
    ofColor myColors[howManyColors];
    ofColor myBackGroundColor1;

    ofxPanel gui;
	ofxIntSlider drawMode;

	ofxIntSlider angleSlider;
	int last_angle;
    ofxIntSlider tail;
	int last_tail;
	ofxFloatSlider sizeProportion;
	ofxFloatSlider interpolationVel;
	ofxIntSlider defaultSize;
	ofxToggle setSmoothing; //
	ofxToggle bRandomX;
	ofxFloatSlider deltaX;
	ofxFloatSlider deltaY;

    ofFbo fbo;

	//TODO1 un color de fondo y 2 colores de particulas
	//TODO1 Colores en un Array, y al ser generada le asignas un color. 
	//TODO2 trayectora con Angulo.


};
