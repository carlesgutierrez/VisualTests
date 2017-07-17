#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
	ofSetFrameRate(50);

	resetBkPoints();


	//---------fbo
	ofFbo::Settings settings;
	settings.height = ofGetHeight();
	settings.width = ofGetWidth();
	settings.useStencil = true;
	settings.internalformat = GL_RGB32F_ARB;
	cout << "The the maximum number of MSAA samples that your graphic card supports is " << endl;
	int maxSamples = fbo.maxSamples();
	cout << maxSamples << endl;
	settings.numSamples = maxSamples;
	fbo.allocate(settings);


	fbo.begin();
	ofClear(255, 0);
	fbo.end();

	//Interaction Y class
	myInteractiveDataClass.setup(2); //Set just one particle   //TODO 3? 0  Hue, 1 Sat , And 2 Value


	//------------GUI
	myMainGui.setup();

}

//-------------------------------------------------------------
void ofApp::resetBkPoints() {
	pointsBk.clear();
	//pointsBk.resize(NUMPOINTSBK);

	for (int i = 0; i < NUMPOINTSBK; i++)
	{
		ofPoint auxPoint = ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
		pointsBk.push_back(auxPoint);
		
	}
}

//-------------------------------------------------------------
void ofApp::updateInteractiveData(vector<shared_ptr<ConvexTrailInteractionObject>> _myInteractiveObjects, ofPoint & valId0, float &valId1) {

	for (int i = 0; i < _myInteractiveObjects.size(); i++)
	{
		float thisRadius = 5;
		ofVec2f mLoc = _myInteractiveObjects[i]->normPosFilter;

		//TODO
		//Do Something with this data
		//update Next pos omnly with fisrt element
		if (i == 0) {
			valId0.x = mLoc.x;
			valId0.y = mLoc.y;
		}
		if (i == 1) {
			//More Interactivity? 
			valId1 = ofMap(mLoc.y, 0, 1, 0.3, 1); // just size Hull
		}

	}

}

//-----------------------------------------------------------
void ofApp::updateConvexTrailWithInteractiveObjects() {

	float x, y;
	float sizeHull;
	ofPoint myNewLoc;
	updateInteractiveData(myInteractiveDataClass.myInteractiveObjectsVector, myNewLoc, sizeHull); //Updates n value
	x = myNewLoc.x * ofGetWidth();
	y = myNewLoc.y * ofGetHeight();//rescaling
	radialDistThreshold2Hull = sizeHull*150;

	/////////////////////////////////////////
	//Prepare swaping
	vector<ofPoint> swapHull;
	swapHull = hull1;


	////////////////////////////////////////////////
	//calc new convexhull
	hull1.clear();
	updateClosePoints(x, y, radialDistThreshold2Hull, pointsBk, closePoints);
	hull1 = convexHull.getConvexHull(closePoints);
	polyHull1.clear();
	polyHull1.addVertices(hull1);

	//That might consume CPU but might create be more singular 
	if (polyHull2.getCentroid2D().distance(polyHull1.getCentroid2D()) > distanceMoveThreshold) {
		//save last convexhull if there is a significant diference
		hull2 = swapHull;
		polyHull2.clear();
		polyHull2 = polyHull1;
	}
	else {
		//cout << "too close" << endl;
	}
}

//--------------------------------------------------------------
void ofApp::update(){

	////////////////////////////////////////
	updateConvexTrailWithInteractiveObjects();
	myInteractiveDataClass.update();
	//////////////////////////////////////

	fbo.begin();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);//OF_BLENDMODE_ADD

	//Draw just background Color i've you wish
	ofSetColor(myBackGroundColor, alphaBkColor);
	ofFill();
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	int auxBlendMode = ModeBlend;
	ofEnableBlendMode((ofBlendMode)auxBlendMode);//OF_BLENDMODE_ADD


	//////////////////
	//Draw something
	drawAllConvexHulls();

	fbo.end();


}

//NOT REALLY USEFULL GRAPHICALLY TALKING YET
//-------------------------------------------------------------
bool ofApp::newHullTrail(vector<ofPoint> _hull1, vector<ofPoint> _hull2, int maxMachPoints, vector<ofPoint>&  _hullTrail) {
	
	bool bNewTrailHull = false;
	vector<ofPoint> resultingMatchPointsHulls;

	ofPoint auxCentroidHull1;
	float incPrecision = 0.01;
	ofPolyline auxPolyHull1;
	auxPolyHull1.addVertices(_hull1);
	ofPolyline auxPolyHull2;
	auxPolyHull2.addVertices(_hull2);


	int counterMatchPoints = 0;
	for (int i = 0; i < auxPolyHull1.size(); i++) {
		if(auxPolyHull2.size()>0){
			if (auxPolyHull2.inside(_hull1[i])) {
				counterMatchPoints++;
				if (counterMatchPoints <= maxMachPoints) {//just get the ninimum matches
					resultingMatchPointsHulls.push_back(_hull1[i]);
					bNewTrailHull = true;
				}
				else {
					resultingMatchPointsHulls.clear();
					bNewTrailHull = false;
					return bNewTrailHull;//stop looking for new hull train: too much matches.
				}
			}
		}
	}


	//All in, even twice....convexHull Algoritm will filter repeated points
	for (int i = 0; i < auxPolyHull2.size(); i++) {
		if (auxPolyHull1.size()>0) {
			if (auxPolyHull1.inside(_hull2[i])) {
				counterMatchPoints++;
				if (counterMatchPoints <= maxMachPoints) {//just get the ninimum matches
					//if(_hull2[i])
					resultingMatchPointsHulls.push_back(_hull2[i]);
					bNewTrailHull = true;
				}
				else {
					resultingMatchPointsHulls.clear();
					bNewTrailHull = false;
					return bNewTrailHull;//stop looking for new hull train: too much matches.
				}
			}
		}
	}

	if (bNewTrailHull) {
		resultingMatchPointsHulls.push_back(auxPolyHull1.getCentroid2D());
		resultingMatchPointsHulls.push_back(auxPolyHull2.getCentroid2D());
		//cout << "new hull detected  = " << resultingMatchPointsHulls.size() << endl;
		_hullTrail = convexHullTrail.getConvexHull(resultingMatchPointsHulls);
	}

	return bNewTrailHull;
}


//--------------------------------------------------------------
void ofApp::drawConvexHull(vector<ofPoint> _myHull) {
	
	ofBeginShape();
	for (int i = 0; i<_myHull.size(); i++) {
		if(bRoundVertexes)ofCurveVertex(_myHull[i]);
		else ofVertex(_myHull[i]);
	}
	ofEndShape();
}


//--------------------------------------------------------------
void ofApp::drawAllConvexHulls() {
	ofFill();

	// draw past hull
	ofSetColor(myActionColor2, alphaActionColor);
	drawConvexHull(hull2);

	// draw hull
	ofSetColor(myActionColor1, alphaActionColor);
	drawConvexHull(hull1);

	/* NOT USEFULL YET Too Ungly Results by just drawing the new result contour
	bool bNewHull = newHullTrail(hull1, hull2, maxMatchInternalHullPoint, trailHull);
	if (bNewHull) {
		ofSetColor(0, 255, 0, alphaActionColor);
		drawConvexHull(trailHull);
	}*/
	
}


//--------------------------------------------------------------
void ofApp::draw(){


	//Draw Fbo Info
	fbo.draw(0, 0);

	// draw Bk points
	//ofSetColor(0);
	//for (int i = 0; i<pointsBk.size(); i++) {
	//	ofCircle(pointsBk[i], 2);
	//}

	//Draw Gui
	myMainGui.begin();
	drawGui();
	myMainGui.end();

    // get area of convex hull
    float area = convexHull.getArea(hull1);
    ofDrawBitmapString("area = "+ofToString(area), 5, 20);
}

//--------------------------------------------------------------
void ofApp::drawGui() {

	myInteractiveDataClass.drawGui();
	ImGui::Checkbox("bDegubMode", &bDegubMode);
	if (bDegubMode) {
		myInteractiveDataClass.draw();
	}

	ImGui::Separator();

	ImGui::ColorEdit3("myBackGroundColor", (float*)&myBackGroundColor);
	ImGui::SliderInt("alphaBkColor", &alphaBkColor, 0, 4);
	ImGui::ColorEdit3("myActionColor1", (float*)&myActionColor1);
	ImGui::ColorEdit3("myActionColor2", (float*)&myActionColor2);
	ImGui::SliderInt("alphaActionColor", &alphaActionColor, 1, 255);
	ImGui::Checkbox("bRoundVertexes", &bRoundVertexes);
	

	ImGui::SliderInt("Radial Dist Threshold Hull", &radialDistThreshold2Hull, 10, 1000);
	ImGui::SliderInt("distance Move Threshold", &distanceMoveThreshold, 10, 1000);
	

	//ImGui::SliderInt("Match Points Hull Trails", &maxMatchInternalHullPoint, 10, 1000);

	ImGui::Text("Blending Options");
	ImGui::SliderInt("ModeBlend", &ModeBlend, 0, 2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------
void ofApp::updateClosePoints(int _myPosX, int _myPosY, int distance, vector<ofPoint> _bkPoints, vector<ofPoint>& _closePoints) {
	
	_closePoints.clear();

	for (int i = 0; i < _bkPoints.size(); i++) {
		float auxDist = ofDist(_myPosX, _myPosY, _bkPoints[i].x, _bkPoints[i].y);

		if (auxDist < distance){
			_closePoints.push_back(_bkPoints[i]);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){


}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){


	/////////////////////////////////////////
	//Prepare swaping
	vector<ofPoint> swapHull;
	swapHull = hull1;


	////////////////////////////////////////////////
	//calc new convexhull
	hull1.clear();
	updateClosePoints(x, y, radialDistThreshold2Hull, pointsBk, closePoints);
	hull1 = convexHull.getConvexHull(closePoints);
	polyHull1.clear();
	polyHull1.addVertices(hull1);

	//That might consume CPU but might create be more singular 
	if (polyHull2.getCentroid2D().distance(polyHull1.getCentroid2D()) > distanceMoveThreshold) {
		//save last convexhull if there is a significant diference
		hull2 = swapHull;
		polyHull2.clear();
		polyHull2 = polyHull1;
	}
	else {
		//cout << "too close" << endl;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
	

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
