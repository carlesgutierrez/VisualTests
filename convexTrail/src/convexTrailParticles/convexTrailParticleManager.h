#pragma once
#include "ofMain.h"
//#include "Constants.h"
#include "ConvexTrailParticle.h"
#include "ofxImGui.h"


class convexTrailParticleManager {

	public:
	
		convexTrailParticleManager();
		~convexTrailParticleManager();

		void setup(int _numParticles);
		void update();
		void draw();		

		//Drawers
		void drawNodeConnetions();
		void drawParticlesAndAttractors(int x, int y);
		
		
		//Modes
		convexTrailParticleMode currentMode;
		string currentModeStr;
        bool bVisibleParticles = true;
		bool bLimitWalls = false;
		bool bAttractosrMoving = false;
		//bool bGameResetLastIdVisitedOnceAllVisited = false;
		//bool bGameResetAllOnceAllVisited = true;
		bool bMouseDebuggin = false;

		//Particle Parameters
		float myPerlin1dControl = 0.04;
		float myPerlin2dControl = 0.2;
		float myVelocityControl = 0.1;
		float myPercentNoiseControl = 0.5;
		int minRangeRadius = 7;
		int maxRangeRadius = 14;

		//Data
		vector <convexTrailParticle> p;
		vector <ofPoint> attractPoints;
		vector <int> attractPointsSizes;
		vector <ofPoint> attractPointsWithMovement;
		vector <int> theNextNodesId;

		//Resets
		int numParticles = 1;
		void resetNumParticles(int _numParticles);
		void resetAll();
		void resetParticles();
		void randomizeAttractor(int idAttractor);
		void initEnemies(int numDesiredEnemies, convexTrailParticleMode _mode, float _velocityEnemies, float _percentPerlinNoise, bool _bLimitWalls);
		void updateRoundsComplete();

		//Events


		//Gui
		void drawGui();
		//ofxImGui myGui;
        float scaleFactorIO;
        int posXIO;
        int posYIO;

		//External Interctive Things
		vector<shared_ptr<ConvexTrailInteractionObject>> myInteractiveObjectsVector;
        ConvexTrailInteractiveObjectConfig myInteractiveOjectsConfig;

		shared_ptr<ConvexTrailInteractionObject> makeIObjectVector();
		void drawInteractiveObject(shared_ptr<ConvexTrailInteractionObject> _InteractiveObject, float _scale);
		void drawAllInteractiveObjects(int posx, int posy, float scale);

		void updateIObjects();
		void updateMouseDebugInteraction(int _translatex, int _translatey, float _scale);
		float uniqueStrenghtVal;
};
