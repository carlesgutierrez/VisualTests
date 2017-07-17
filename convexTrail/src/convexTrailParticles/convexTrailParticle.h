#pragma once
#include "ofMain.h"

///////////////////////////////////////////
//Interactive Objects Things
#define CONVEXTRAIL_MIN_STRENGHT_DETECTED 2000000
#define CONVEXTRAIL_MAX_STRENGHT_DETECTED 20000000



class ConvexTrailInteractionObject {
public:

	int64_t id;
	ofVec2f normPosFilter;
	ofVec2f normPosWarping;
	int speedKm;
    int strength;

};

/////////////////////////////////////////////
//TODO ?
#define CONVEXTRAIL_SIZE_WIN_W 231
#define CONVEXTRAIL_SIZE_WIN_H 1332
#define CONVEXTRAIL_MAX_ATTRACTORS 4
#define CONVEXTRAIL_MARGIN_ATTRACTORS 10

enum convexTrailParticleMode{
	CONVEXTRAIL_PARTICLE_MODE_NOISE_WALKER = 0,
	CONVEXTRAIL_PARTICLE_MODE_NOISE_SNOW_DIR
};

struct ConvexTrailInteractiveObjectConfig {
    //extra params for load&save and Configuration
    convexTrailParticleMode currentMode = CONVEXTRAIL_PARTICLE_MODE_NOISE_WALKER;
    bool bLimitWalls = false;
    float velocityEnemies = 0.3;
    float percentPerlinNoise = 0.5;
    int numDesiredEnemies = 0;
};

class convexTrailParticle {

	public:
		convexTrailParticle();
		
		//Setters
		void setMode(convexTrailParticleMode newMode);	
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
		
		convexTrailParticleMode mode;

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
