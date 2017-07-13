#pragma once
#include "ofMain.h"

///////////////////////////////////////////
//Interactive Objects Things
#define LIGHTBRUSH_MIN_STRENGHT_DETECTED 2000000
#define LIGHTBRUSH_MAX_STRENGHT_DETECTED 20000000



class LightBrushInteractionObject {
public:

	int64_t id;
	ofVec2f normPosFilter;
	ofVec2f normPosWarping;
	int speedKm;
    int strength;

};

/////////////////////////////////////////////
//TODO ?
#define LIGTHLAMP_SIZE_WIN_W 231
#define LIGHTLAMP_SIZE_WIN_H 1332
#define LIGHTLAMP_MAX_ATTRACTORS 4
#define LIGHTLAMP_MARGIN_ATTRACTORS 10

enum lightBrushParticleMode{
	LIGHTBRUSH_PARTICLE_MODE_NOISE_WALKER = 0,
	LIGHTBRUSH_PARTICLE_MODE_NOISE_SNOW_DIR
};

struct LightBrushInteractiveObjectConfig {
    //extra params for load&save and Configuration
    lightBrushParticleMode currentMode = LIGHTBRUSH_PARTICLE_MODE_NOISE_WALKER;
    bool bLimitWalls = false;
    float velocityEnemies = 0.3;
    float percentPerlinNoise = 0.5;
    int numDesiredEnemies = 0;
};

class LightBrushParticle {

	public:
		LightBrushParticle();
		
		//Setters
		void setMode(lightBrushParticleMode newMode);	
		void setAttractPoints( vector <ofPoint> * attract );
		void setAttractPointsSizes(vector <int> * _nodePointsSizes);
		void setPerlinParameters(float _param2d, float _param3d);

		void reset();
		void update();
		void draw();		
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
		lightBrushParticleMode mode;

		//Control Parameter Vars
		float velocityControl = 0.1;
		float percentNoiseControl = 0.7;
		float perlinNoiseParam2d = 0.04;
		float perlinNoiseParam3d = 0.2;

		//Moving arround Attractors
		
		int minDistance = 10;
		vector <ofPoint> * nodePoints;
		vector <int> * nodeSizes;

		ofPoint updateDirToGo();
		int getIdNextNode();
		int idNextNode = 0;
		bool bMouseInteraction = false;


		//Logic game
		void resetRounComplete();
		bool bRoundComplete = false;
		bool bLimitWalls = false;

};
