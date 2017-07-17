#include "convexTrailParticleManager.h"

//------------------------------------------------------------------
convexTrailParticleManager::convexTrailParticleManager() {
}

//------------------------------------------------------------------
convexTrailParticleManager::~convexTrailParticleManager() {
}

//------------------------------------------------------------------
void convexTrailParticleManager::setup(int _numParticles) {

	numParticles = _numParticles;
	currentMode = CONVEXTRAIL_PARTICLE_MODE_NOISE_WALKER;
	currentModeStr = "CONVEXTRAIL_PARTICLE_MODE_NOISE_WALKER";
	resetAll();

	//External Interactive Things
	//Mouse Debug
	uniqueStrenghtVal = ofRandom(CONVEXTRAIL_MIN_STRENGHT_DETECTED, CONVEXTRAIL_MAX_STRENGHT_DETECTED);

	//events
    //ofAddListener(eventWallsFxAnimation::onNewConfigurationEnemies, this, &wallsParticleManager::listenerOnNewConfigEnemies);

	posXIO = 0; // POSX_IO;
	posYIO = 0; //POSY_IO;
	scaleFactorIO = 1;// SCALE_FACTOR_IO;


}


//------------------------------------------------------------------
void convexTrailParticleManager::update() {

	//UPdate Particles and Attactros

	for (unsigned int i = 0; i < p.size(); i++) {
		p[i].setMode(currentMode);
		p[i].update();
	}

	updateRoundsComplete();

	if (bAttractosrMoving) {
		//lets add a bit of movement to the attract points
		for (unsigned int i = 0; i < attractPointsWithMovement.size(); i++) {
			attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
			attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
		}
	}


	//Then update that particles into a Interactive Object

	updateIObjects();
	updateMouseDebugInteraction(0, 0, 1);

}

//------------------------------------------------------------------
void convexTrailParticleManager::draw() {

	//Particles , Attractors and connections
	if (bVisibleParticles) {
		drawParticlesAndAttractors(posXIO, posYIO);
	}

	//Draw resulting Interactive Objects
	drawAllInteractiveObjects(posXIO, posYIO, scaleFactorIO);

}

//-----------------------------------------------------------------------------
void convexTrailParticleManager::drawAllInteractiveObjects(int _posx, int _posy, float _scale) {

	ofPushMatrix();
	ofTranslate(CONVEXTRAIL_SIZE_WIN_W + 2, 0, 0);



	ofPushMatrix();
	ofPushStyle();

	ofTranslate(_posx, _posy, 0);

	ofNoFill();
	ofSetColor(ofColor::lightPink);
	ofDrawRectangle(0, 0, _scale, _scale);

	ofSetColor(ofColor::red);
	for (int i = 0; i < myInteractiveObjectsVector.size(); i++) {
		drawInteractiveObject(myInteractiveObjectsVector[i], _scale);
	}

	ofPopStyle();
	ofPopMatrix();

	ofPopMatrix();

}

//------------------------------------------------------------------------------
void convexTrailParticleManager::drawParticlesAndAttractors(int _posx, int _posy) {

	ofPushMatrix();
	ofPushStyle();
	ofTranslate(_posx, _posy, 0);

	//Draw Rect area
	ofNoFill();
	ofSetColor(ofColor::white);
	ofDrawRectangle(0, 0, CONVEXTRAIL_SIZE_WIN_W, CONVEXTRAIL_SIZE_WIN_H);
	ofFill();

	drawNodeConnetions();


	//{c} Updating Next Nodes to draw with different colors
	//Not really necesary to be done. Just dont draw it.
	theNextNodesId.clear();

	for (unsigned int i = 0; i < p.size(); i++) {
		theNextNodesId.push_back(p[i].getIdNextNode()); //at least the last NextNodeId Detected
		p[i].draw();
	}


	if (currentMode == CONVEXTRAIL_PARTICLE_MODE_NOISE_WALKER) {
		for (unsigned int i = 0; i < attractPoints.size(); i++) {

			bool baNextNodeActive = false;
			ofColor nextColor;

			for (int j = 0; j < theNextNodesId.size(); j++) {
				if (i == theNextNodesId[j]) {
					baNextNodeActive = true;
				}
			}

			if (baNextNodeActive) {
				float auxHueValue = ofMap(i, 0, theNextNodesId.size(), 0, 200);
				nextColor.setHsb(auxHueValue, 255, 255);
				ofSetColor(nextColor);
			}
			else ofSetColor(190);

			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], attractPointsSizes[i]);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	ofPopStyle();
	ofPopMatrix();
}

//--------------------------------------------------------------
void convexTrailParticleManager::drawNodeConnetions() {
	ofPolyline lineConnections;


	ofPushStyle();
	ofSetColor(ofColor::aliceBlue);

	//Update Vertexes //TODO do this just each time Nodes modif?
	for (int i = 0; i < attractPointsWithMovement.size(); i++) {
		lineConnections.addVertex(attractPointsWithMovement[i]);
	}

	lineConnections.draw();

	ofPopStyle();
}


//--------------------------------------------------------------
void convexTrailParticleManager::randomizeAttractor(int idAttractor) {

	if (idAttractor < attractPoints.size()) {
		attractPoints[idAttractor] = ofPoint(ofRandom(CONVEXTRAIL_MARGIN_ATTRACTORS, CONVEXTRAIL_SIZE_WIN_W - CONVEXTRAIL_MARGIN_ATTRACTORS), ofRandom(CONVEXTRAIL_MARGIN_ATTRACTORS, CONVEXTRAIL_SIZE_WIN_H - CONVEXTRAIL_MARGIN_ATTRACTORS));
		attractPointsSizes[idAttractor] = (int)ofRandom(minRangeRadius, maxRangeRadius);

		attractPointsWithMovement = attractPoints;//TODO check if withMovement can be used or not necessary

		for (unsigned int i = 0; i < p.size(); i++) {
			p[i].setAttractPoints(&attractPointsWithMovement);
			p[i].bRoundComplete = false;
		}
	}



}

//--------------------------------------------------------------
void convexTrailParticleManager::initEnemies(int numDesiredEnemies, convexTrailParticleMode _mode, float _velocityEnemies, float _percentPerlinNoise, bool _bLimitWalls) {
    if (numParticles != numDesiredEnemies) {
        numParticles = numDesiredEnemies;
		resetNumParticles(numParticles);
	}
	
	currentMode = (convexTrailParticleMode) _mode;
    for (unsigned int i = 0; i < p.size(); i++) {
        p[i].setMode(currentMode);
    }

    myVelocityControl = _velocityEnemies;
    for (unsigned int i = 0; i < p.size(); i++) {
        p[i].velocityControl = myVelocityControl;
    }

     myPercentNoiseControl = _percentPerlinNoise;
    for (unsigned int i = 0; i < p.size(); i++) {
        p[i].percentNoiseControl = myPercentNoiseControl;
    }

    bLimitWalls = _bLimitWalls;
    for (unsigned int i = 0; i < p.size(); i++) {
        p[i].bLimitWalls = bLimitWalls;
    }

    //Update the Config Struct
	myInteractiveOjectsConfig.currentMode = currentMode;
	myInteractiveOjectsConfig.velocityEnemies = myVelocityControl;
	myInteractiveOjectsConfig.percentPerlinNoise = myPercentNoiseControl;
    myInteractiveOjectsConfig.bLimitWalls = bLimitWalls;
}

//--------------------------------------------------------------
void convexTrailParticleManager::resetNumParticles(int _numParticles) {
	p.resize(_numParticles);
	p.assign(_numParticles, convexTrailParticle());
	resetParticles();
}
//--------------------------------------------------------------
void convexTrailParticleManager::resetParticles() {
	for (unsigned int i = 0; i < p.size(); i++) {
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		p[i].setAttractPointsSizes(&attractPointsSizes);
		p[i].reset();

		if (bLimitWalls)p[i].bLimitWalls = true;
	}
}

//--------------------------------------------------------------
void convexTrailParticleManager::resetAll() {

	//these are the attraction points used in the forth demo 
	attractPoints.clear();
	attractPointsSizes.clear();
	for (int i = 0; i < CONVEXTRAIL_MAX_ATTRACTORS; i++) {
		attractPoints.push_back(ofPoint(ofMap(i, 0, CONVEXTRAIL_MAX_ATTRACTORS, CONVEXTRAIL_MARGIN_ATTRACTORS, CONVEXTRAIL_SIZE_WIN_W - CONVEXTRAIL_MARGIN_ATTRACTORS), ofRandom(CONVEXTRAIL_MARGIN_ATTRACTORS, CONVEXTRAIL_SIZE_WIN_H - 10)));
		attractPointsSizes.push_back((int)ofRandom(minRangeRadius, maxRangeRadius));
	}

	attractPointsWithMovement = attractPoints;

	resetNumParticles(numParticles);

}


//--------------------------------------------------------------
void convexTrailParticleManager::updateRoundsComplete() {

	bool bANewRoundDone4All = true;
	int lowerNodeId = 10000000;


	for (int i = 0; i < p.size(); i++) {
		bANewRoundDone4All *= p[i].bRoundComplete;

		if (lowerNodeId > p[i].getIdNextNode()) {
			lowerNodeId = p[i].getIdNextNode();
		}
	}
	/*
	if (bGameResetLastIdVisitedOnceAllVisited) {
		//PLay diferent game roles here
		if (bANewRoundDone4All == true && p.size() > 0) {//Randomize just the LowerId
			randomizeAttractor(lowerNodeId);
		}
	}
	else if (bGameResetAllOnceAllVisited) {
		if (bANewRoundDone4All == true && p.size() > 0) {//Randomize all of them
			for (int i = 0; i < p.size(); i++) {
				randomizeAttractor(i);
			}
		}
	}*/
	if (bANewRoundDone4All == true && p.size() > 0) {//Randomize all of them
		for (int i = 0; i < p.size(); i++) {
			randomizeAttractor(i);
		}
	}

}




//---------------------------------------------------------------
void convexTrailParticleManager::drawGui() {

	ImGui::Text("Noise Particles");

  	ImGui::PushItemWidth(70);

    if (ImGui::SliderFloat("Vel Control ##convexTrailParticleManager", &myVelocityControl, 0.001, 0.1)) {
		for (unsigned int i = 0; i < p.size(); i++) {
			p[i].velocityControl = myVelocityControl;
		}
	}

    if (ImGui::SliderFloat("% Noise control ##convexTrailParticleManager", &myPercentNoiseControl, 0, 1)) {
		for (unsigned int i = 0; i < p.size(); i++) {
			p[i].percentNoiseControl = myPercentNoiseControl;
		}
	}

    if (ImGui::Checkbox("Inside Walls Limit ##convexTrailParticleManager", &bLimitWalls)) {
        for (unsigned int i = 0; i < p.size(); i++) {
            p[i].bLimitWalls = bLimitWalls;
        }
    }

	if (ImGui::Button("Reset All ##convexTrailParticleManager")) {
		resetAll();
	}

    ImGui::PopItemWidth();
}

//External and Interactive Objects
//--------------------------------------------
shared_ptr<ConvexTrailInteractionObject> convexTrailParticleManager::makeIObjectVector() {
	auto p = std::make_shared<ConvexTrailInteractionObject>();
	return p;
}

//-----------------------------------------------
void convexTrailParticleManager::updateMouseDebugInteraction(int _translatex, int _translatey, float _scale) {

	if (bMouseDebuggin) {
		shared_ptr<ConvexTrailInteractionObject> auxIObject = makeIObjectVector();

		auxIObject->id = -1375;
		auxIObject->normPosFilter.x = (float)ofGetMouseX() / (float)ofGetWidth();
		auxIObject->normPosFilter.y = (float)ofGetMouseY() / (float)ofGetHeight();
		//auxIObject->normPosWarping = auxIObject->normPosFilter; //Not used
		auxIObject->speedKm = 0;
		auxIObject->strength = uniqueStrenghtVal*ofNoise(ofGetElapsedTimef()*0.2);//not used
		myInteractiveObjectsVector.push_back(auxIObject);
	}

}

//-----------------------------------------------
void convexTrailParticleManager::updateIObjects() {

	myInteractiveObjectsVector.clear();

	for (int i = 0; i < p.size(); i++) {
		//create new object that reMap his position into [0..1]
		shared_ptr<ConvexTrailInteractionObject> auxIObject1 = makeIObjectVector();

		auxIObject1->id = i;
		auxIObject1->normPosFilter.x = ofMap(p[i].pos.x, 0, CONVEXTRAIL_SIZE_WIN_W + CONVEXTRAIL_MARGIN_ATTRACTORS, 0.000000f, 1.0000000);
		auxIObject1->normPosFilter.y = ofMap(p[i].pos.y, 0, CONVEXTRAIL_SIZE_WIN_H + CONVEXTRAIL_MARGIN_ATTRACTORS, 0.000000f, 1.0000000);
		auxIObject1->speedKm = 0;//TODO Check if vel can be updated and used. 
		auxIObject1->strength = uniqueStrenghtVal*ofNoise(ofGetElapsedTimef()*0.2); //not used
		myInteractiveObjectsVector.push_back(auxIObject1);
	}

    //Here config data is being udpated
    myInteractiveOjectsConfig.bLimitWalls = bLimitWalls;
    myInteractiveOjectsConfig.currentMode = currentMode;
    myInteractiveOjectsConfig.percentPerlinNoise = myPercentNoiseControl;
    myInteractiveOjectsConfig.velocityEnemies = myVelocityControl;
}

//--------------------------------------------------------------
void convexTrailParticleManager::drawInteractiveObject(shared_ptr<ConvexTrailInteractionObject> _InteractiveObject, float _scale) {
	ofDrawCircle(_InteractiveObject->normPosFilter.x*_scale, _InteractiveObject->normPosFilter.y*_scale, 5);
	//float strenghSize = ofMap(_InteractiveObject->strength, MIN_STRENGHT_DETECTED, MAX_STRENGHT_DETECTED, MIN_CIRCLE_STRENGHT_BLOB_SIZE*(1 / mixerScale), MAX_CIRCLE_STRENGHT_BLOB_SIZE*(1 / mixerScale));
	//ofDrawCircle(_InteractiveObject->normPosFilter.x, _InteractiveObject->normPosFilter.y, 2 * mixerScale, strenghSize);
}
