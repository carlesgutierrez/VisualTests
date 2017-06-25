#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  // setup world
  box2d.init();
  box2d.setFPS(60);
  box2d.setGravity(0, -1);

  bounds.set(5, 5, ofGetWidth()-5, ofGetHeight()-5);

  box2d.createBounds(bounds);
  box2d.registerGrabbing();

  myBlob.init(0,50,1,10,box2d);
}

//--------------------------------------------------------------
void ofApp::update(){

  	box2d.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

  myBlob.display();


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
