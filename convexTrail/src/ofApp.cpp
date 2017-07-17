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

//--------------------------------------------------------------
void ofApp::update(){

	fbo.begin();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);//OF_BLENDMODE_ADD

	//Draw just background Color i've you wish
	ofSetColor(myBackGroundColor, alphaBkColor);
	ofFill();
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	int auxBlendMode = ModeBlend;
	ofEnableBlendMode((ofBlendMode)auxBlendMode);//OF_BLENDMODE_ADD

	//Draw something
	drawConvexHull();

	fbo.end();
}

//--------------------------------------------------------------
void ofApp::drawConvexHull() {
	ofFill();

	// draw Bk points
	ofSetColor(0);
	for (int i = 0; i<pointsBk.size(); i++) {
		ofCircle(pointsBk[i], 2);
	}

	// draw hull
	ofSetColor(myActionColor, alphaActionColor);
	ofBeginShape();
	for (int i = 0; i<hull1.size(); i++) {
		ofCurveVertex(hull1[i]);
	}
	ofEndShape();

	// draw past hull
	ofSetColor(0, 255, 0, alphaActionColor);
	ofBeginShape();
	for (int i = 0; i<hull2.size(); i++) {
		ofCurveVertex(hull2[i]);
	}
	ofEndShape();
}


//--------------------------------------------------------------
void ofApp::draw(){

	//Draw Fbo Info
	fbo.draw(0, 0);

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
	ImGui::ColorEdit3("myBackGroundColor", (float*)&myBackGroundColor);
	ImGui::SliderInt("alphaBkColor", &alphaBkColor, 0, 4);
	ImGui::ColorEdit3("myActionColor", (float*)&myActionColor);
	ImGui::SliderInt("alphaActionColor", &alphaActionColor, 1, 255);


	ImGui::SliderInt("Distance Threshold", &distanceThreshold, 10, 1000);

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
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	//save last convexhull
	hull2 = hull1;

	//calc new convexhull
	hull1.clear();
	updateClosePoints(x, y, distanceThreshold, pointsBk, closePoints);
	hull1 = convexHull.getConvexHull(closePoints);

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
