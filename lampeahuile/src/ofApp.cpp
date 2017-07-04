#include "ofApp.h"

//------------------------------------------------------------
void ofApp::setupSomeInitColors() {
	//myBackGroundColor1 = color(18,15,72);// Fiery rose(18,15,72) // Pale Robin(162, 28, 88);
	myBackGroundColor = ofColor(184, 164, 156, 10);
	//myBackGroundColor2 = color(182,25,98);//


	//myBlobsColor1 = ofColor::fromHsb(354, 62, 99, 200);//color(75, 47, 94, 200); // Fiery rose(18,15,72);
	//myBlobsColor2 = ofColor::fromHsb(351, 72, 89, 200); // Fiery rose(18,15,72);

	myBlobsColor = ofColor(252, 96, 112, 255);//color(75, 47, 94, 200); // Fiery rose(18,15,72);
	myBlobsColor2 = ofColor(227, 64, 88, 255);
}


//--------------------------------------------------------------
void ofApp::setup(){

  ofEnableSmoothing();

  //fs
  posFloor.set(5, ofGetHeight()/8);
  dimFloor.set(ofGetWidth()*0.95, ofGetHeight()/8); // 10 H

  //-----fbo
  ofFbo::Settings settings;
  settings.height = ofGetHeight();
  settings.width = ofGetWidth();
  settings.useStencil = true;
  settings.internalformat = GL_RGB32F_ARB;
  cout << "The the maximum number of MSAA samples that your graphic card supports is " << endl;
  int maxSamples = fbo.maxSamples();
  cout << maxSamples << endl;
  settings.numSamples = 2;// maxSamples; //May affect to the performance too
  fbo.allocate(settings);

  //------------GUI
  gui.setup();

  //Colors Gui
  setupSomeInitColors();
  gui.add(myBackGroundColor.setup("color Background", myBackGroundColor, ofColor(0, 1), ofColor(255, 100)));
  //gui.add(fboTail.setup("fbo Tail", 10, 1, 30));
  gui.add(modeDrawFloors.setup("modeDrawFloors", 0, 0, 2));
  gui.add(myBlobsColor.setup("color Blob", myBlobsColor, ofColor(0, 0), ofColor(255, 255)));
  gui.add(myBlobPropRespirationX.setup("Blob Vel X", 0.04, -0.2, 0.2));
  gui.add(myBlobPropRespirationY.setup("Blob Vel Y", 0.05, -0.2, 0.2));
  gui.add(myBlobValPlusAngles.setup("Blob Rot", 0.0, -0.05, 0.05));
  gui.add(bRotated.setup("Gfx rotated"));

  //Blobs Setup
  for (int a = 0; a<nBlob; a++) {
	 // blobs[a].init(ofRandom(-10, ofGetHeight() + 10), ofRandom(-10, ofGetHeight() + 100));
	  blobs[a].init(ofRandom(-ofGetHeight()*0.25, +ofGetHeight()*0.25), -200);
  }

}

//--------------------------------------------------------------
void ofApp::update(){

  ofEnableAlphaBlending();

	  fbo.begin();

	  if (modeDrawFloors > 0) {
		  //filter(BLUR, 0.5);
		  drawFloors(myBackGroundColor, modeDrawFloors, false);
	  }
	  else {
		  ofSetColor(myBackGroundColor);
		  ofFill(); // That was used to mix colors from background and drops
		  ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
	  }
	

	  ofNoFill();
	  for (int a=0; a<nBlob; a++) {
		blobs[a].dessine(bRotated, myBlobsColor, myBlobPropRespirationX, myBlobPropRespirationY, myBlobValPlusAngles); ////true means 90º rotati
	  }


	  fbo.end();

  ofDisableAlphaBlending();

}

//----------------------------------------
void ofApp::setScaledColor(ofColor baseColor, int idStep, int minSteps, int maxSteps, int mode, bool invertOrder) {

	float mapColorModif;
	if (invertOrder) mapColorModif = ofMap(idStep, minSteps, maxSteps, 0, 1);
	else mapColorModif = ofMap(idStep, minSteps, maxSteps, 1, 0);

	ofColor auxNewColor = baseColor;
	float h, s, v;
	baseColor.getHsb(h, s, v);

	if (mode == 1) { //Hue
		auxNewColor.setHsb(h*mapColorModif, s, v, baseColor.a);
	}
	else if (mode == 2) {//Sat
		auxNewColor.setHsb(h, s*mapColorModif, v, baseColor.a);
	}
	else if (mode == 3) {//Value
		auxNewColor.setHsb(h, s, v*mapColorModif, baseColor.a);
	}
	else {
		//Do not set Color
		return;
	}


	ofSetColor(auxNewColor, auxNewColor.a);
}

//--------------------------
void ofApp::drawFloors(ofColor _mainColor, int _modedrawFloors, bool _invertOrder) {

	posFloor.set(0, ofGetWidth() / 8);
	dimFloor.set(ofGetHeight(), ofGetWidth() / 8); // 10 H

	ofFill();
		
	ofPushMatrix();
	ofTranslate(0, ofGetHeight());
	ofRotate(-90);
	for (int i = 0; i<8; i++) {
		setScaledColor(_mainColor, i, 0, 8, _modedrawFloors, _invertOrder); //ofColor baseColor, int idStep, int minSteps, int maxSteps, int mode, bool invertOrder) {
			
		ofDrawRectangle(posFloor.x, posFloor.y * i, dimFloor.x, dimFloor.y);
	}
	ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::draw(){

  fbo.draw(0,0);

  // ------------ GUI
  gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
