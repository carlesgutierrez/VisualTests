#include "ofApp.h"

//--------------------------
void ofApp::drawFloors() {

  ofSetColor(100,200);   //stroke(255, 100);
  ofNoFill();

  for (int i=0; i<8; i++) {
    ofDrawRectangle(posFloor.x, posFloor.y * i, dimFloor.x, dimFloor.y);
  }
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

  //myBackGroundColor1 = color(18,15,72);// Fiery rose(18,15,72) // Pale Robin(162, 28, 88);
  myBackGroundColor1 = ofColor(184,164,156);
  //myBackGroundColor2 = color(182,25,98);//


  //myBlobsColor1 = ofColor::fromHsb(354, 62, 99, 200);//color(75, 47, 94, 200); // Fiery rose(18,15,72);
  //myBlobsColor2 = ofColor::fromHsb(351, 72, 89, 200); // Fiery rose(18,15,72);

  myBlobsColor1 = ofColor(252, 96, 112,0.8);//color(75, 47, 94, 200); // Fiery rose(18,15,72);
  myBlobsColor2 = ofColor(227, 64, 88,0.8);

  //fs
  posFloor.set(5, ofGetHeight()/8);
  dimFloor.set(ofGetWidth()*0.95, ofGetHeight()/8); // 10 H

  //-----fbo
  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F_ARB);
  fbo.begin();
  ofBackground( 255, 255, 255 );
  fbo.end();

}

//--------------------------------------------------------------
void ofApp::update(){

  fbo.begin();

  ofBackground(myBackGroundColor1);

  for (int a=0; a<nPussiere; a++) {
    ofSetColor(0, 200);
    ofNoFill();
    poussieres[a].dessine();
  }

  ofSetColor(255, 100);
  ofNoFill();
  for (int a=0; a<nBlob; a++) {
    blobs[a].dessine();
  }

  //filter(BLUR, 0.5);

  drawFloors();
  fbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){

  fbo.draw(0,0);


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
