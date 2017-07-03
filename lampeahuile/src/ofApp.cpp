#include "ofApp.h"

//--------------------------
void ofApp::drawFloors() {

	//fs
	posFloor.set(5, ofGetWidth() / 8);
	dimFloor.set(ofGetHeight()*0.95, ofGetWidth() / 8); // 10 H

	ofSetColor(100,200);   //stroke(255, 100);
	ofNoFill();

	ofPushMatrix();
	ofTranslate(0, ofGetHeight());
	ofRotate(-90);
	for (int i=0; i<8; i++) {
		ofDrawRectangle(posFloor.x, posFloor.y * i, dimFloor.x, dimFloor.y);
	}
	ofPopMatrix();
}

//------------------------------------------------------------
void ofApp::setupSomeInitColors() {
	//myBackGroundColor1 = color(18,15,72);// Fiery rose(18,15,72) // Pale Robin(162, 28, 88);
	myBackGroundColor1 = ofColor(184, 164, 156, 40);
	//myBackGroundColor2 = color(182,25,98);//


	//myBlobsColor1 = ofColor::fromHsb(354, 62, 99, 200);//color(75, 47, 94, 200); // Fiery rose(18,15,72);
	//myBlobsColor2 = ofColor::fromHsb(351, 72, 89, 200); // Fiery rose(18,15,72);

	myBlobsColor1 = ofColor(252, 96, 112, 255);//color(75, 47, 94, 200); // Fiery rose(18,15,72);
	myBlobsColor2 = ofColor(227, 64, 88, 255);
}


//--------------------------------------------------------------
void ofApp::setup(){

  ofEnableSmoothing();
  //ofSetBackgroundAuto(false);
  ofEnableAlphaBlending();

  ofSetColor(255,100);   //stroke(255, 100);
  ofNoFill();
  //strokeWeight(1);


  for (int a=0; a<nBlob; a++) {
    blobs[a].init(ofRandom(-10, ofGetHeight()+10), ofRandom(-10, ofGetHeight()+100));
  }

  for (int a=0; a<nPussiere; a++) {
    poussieres[a].init();
  }



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
  settings.numSamples = 2;// maxSamples;
  fbo.allocate(settings);

  //------------GUI
  gui.setup();

  //Colors Gui
  setupSomeInitColors();
  gui.add(myBackGroundColor1.setup("color Background", myBackGroundColor1, ofColor(0, 0), ofColor(255, 255)));
  gui.add(myBlobsColor1.setup("color Blob", myBlobsColor1, ofColor(0, 0), ofColor(255, 255)));

  
}

//--------------------------------------------------------------
void ofApp::update(){

  fbo.begin();

  ofSetColor(myBackGroundColor1);
  ofFill(); // That was used to mix colors from background and drops
  ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());

  /*
  ofSetColor(myBlobsColor2);
  for (int a=0; a<nPussiere; a++) {
    ofNoFill();
    poussieres[a].dessine(); 
  }*/

 
  ofNoFill();
  for (int a=0; a<nBlob; a++) {
    blobs[a].dessine(true, myBlobsColor1); ////true means 90º rotati
  }

  //filter(BLUR, 0.5);

  //drawFloors();
  fbo.end();

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
