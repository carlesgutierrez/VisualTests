#include "convexTrailParticle.h"

//------------------------------------------------------------------
convexTrailParticle::convexTrailParticle(){
	nodePoints = NULL;
}

//------------------------------------------------------------------
void convexTrailParticle::setMode(convexTrailParticleMode newMode){
	mode = newMode;
}

//------------------------------------------------------------------
void convexTrailParticle::setAttractPoints(vector <ofPoint> * _nodePoints) {
	nodePoints = _nodePoints;
}

//------------------------------------------------------------------
void convexTrailParticle::setAttractPointsSizes(vector <int> * _nodePointsSizes) {
	nodeSizes = _nodePointsSizes;	
}

//------------------------------------------------------------------
void convexTrailParticle::setPerlinParameters(float _param2d, float _param3d) {
	perlinNoiseParam2d = _param2d;
	perlinNoiseParam3d = _param3d;
}

//------------------------------------------------------------------
void convexTrailParticle::reset(){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-1000, 1000);//TODO checking this ranges 
	
	ofPoint ranDomPos = ofPoint(ofRandom(10, CONVEXTRAIL_SIZE_WIN_W - 10), ofRandom(10, CONVEXTRAIL_SIZE_WIN_H - 10));
	pos = ranDomPos;
	
	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
	
	frc   = ofPoint(0,0,0);
	
	scale = ofRandom(0.5, 1.0);
	
	if( mode == CONVEXTRAIL_PARTICLE_MODE_NOISE_SNOW_DIR){
		drag  = ofRandom(0.97, 0.99);
		vel.y = fabs(vel.y) * 3.0; //make the particles all be going down
	}else{
		drag  = ofRandom(0.97, 0.998);	
	}
}

//------------------------------------------------------------------
void convexTrailParticle::resetRounComplete() {
	bRoundComplete = false;
}

//------------------------------------------------------------------
int convexTrailParticle::getIdNextNode() {
	return idNextNode;
}

//------------------------------------------------------------------
ofPoint convexTrailParticle::updateDirToGo() {

	ofPoint ptr = nodePoints->at(idNextNode);

	if (!bMouseInteraction) {
		//Inc idNextNode if it has been visited so closed
		if (ptr.distance(pos) < minDistance) {
			
			idNextNode++;
			if (idNextNode > nodePoints->size() - 1) {
				idNextNode = 0;
				bRoundComplete = true;
			}
		}
	}
	//MOuse interaction
	else {
		ptr = ofPoint(ofGetMouseX(), ofGetMouseY());
	}

	return ptr;
}

//------------------------------------------------------------------
void convexTrailParticle::update(){

	//1 - APPLY THE FORCES BASED ON WHICH MODE WE ARE IN 
	
	if( mode == CONVEXTRAIL_PARTICLE_MODE_NOISE_WALKER){
		//1D Noise moving particle 

		ofPoint attractPt = updateDirToGo();

		frc = attractPt - pos; // we get the attraction force/vector by looking at the mouse pos relative to our pos
		float moveNoiseX = frc.normalize().x; //by normalizing we disregard how close the particle is to the attraction point
		float moveNoiseY = frc.normalize().y; //by normalizing we disregard how close the particle is to the attraction point

		frc.x =  moveNoiseX * (1 - percentNoiseControl) + ofSignedNoise(pos.y * perlinNoiseParam2d, ofGetElapsedTimef()*perlinNoiseParam3d, uniqueVal) * percentNoiseControl;
		frc.y =  moveNoiseY * (1 - percentNoiseControl) + ofSignedNoise(pos.x * perlinNoiseParam2d, ofGetElapsedTimef()*perlinNoiseParam3d, uniqueVal) * percentNoiseControl;

		vel *= drag;
		vel += frc * velocityControl;
	}
	else if( mode == CONVEXTRAIL_PARTICLE_MODE_NOISE_SNOW_DIR){
		//lets simulate falling snow 
		//the fake wind is meant to add a shift to the particles based on where in x they are
		//we add pos.y as an arg so to prevent obvious vertical banding around x values - try removing the pos.y * 0.006 to see the banding
		float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);

		frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
		frc.y = ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;

		vel *= drag;
		vel += frc * velocityControl; //0.4


		//Y borders
		if (pos.y + vel.y > CONVEXTRAIL_SIZE_WIN_H) {
			pos.y -= CONVEXTRAIL_SIZE_WIN_H;
		}

		//X borders
		if (pos.x + vel.x > CONVEXTRAIL_SIZE_WIN_W) {
			pos.x -= CONVEXTRAIL_SIZE_WIN_W;
		}
		else if (pos.x + vel.x < 0) {
			pos.x += CONVEXTRAIL_SIZE_WIN_W;
		}
	}
	
	//2 - UPDATE OUR POSITION
	pos += vel; 
	
	
	//3- Check WALLS
	if (bLimitWalls) {
		if( pos.x > CONVEXTRAIL_SIZE_WIN_W ){
			pos.x = CONVEXTRAIL_SIZE_WIN_W;
			vel.x *= -1.0;
		}else if( pos.x < 0 ){
			pos.x = 0;
			vel.x *= -1.0;
		}
		if( pos.y > CONVEXTRAIL_SIZE_WIN_H ){
			pos.y = CONVEXTRAIL_SIZE_WIN_H;
			vel.y *= -1.0;
		}
		else if( pos.y < 0 ){
			pos.y = 0;
			vel.y *= -1.0;
		}	
	}
		
}

//------------------------------------------------------------------
void convexTrailParticle::draw(){

	if( mode == CONVEXTRAIL_PARTICLE_MODE_NOISE_WALKER){
		ofSetColor(255, 63, 180);
	}
	else if( mode == CONVEXTRAIL_PARTICLE_MODE_NOISE_SNOW_DIR){
		ofSetColor(103, 160, 237);
	}
			
	ofDrawCircle(pos.x, pos.y, scale * 4.0);
}



