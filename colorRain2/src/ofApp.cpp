#include "ofApp.h"


//------------------------

void ofApp::updateColors(int tail){

  myColors[0] = ofColor(184,164,156,tail);//(18, 15, 72);  // Fiery rose
  myColors[1] = ofColor(162,224,206,tail);//(162, 28, 88); // Pale Robin
  myColors[2] = ofColor(245,214,152,tail);//(40, 38, 96);  // Tuscan//}

}


//------------------
void ofApp::drawParticle(float _x, float _y, float _speed) {
      //Draw Drop
      ofDrawCircle(_x, _y, _speed, _speed);
      //Draw Line
      //float midPointX = _x;
      //float midPointY = _y;
      //line(midPointX, _y, sliderValue, sliderValue);
}


//--------------------------------------------------------------
void ofApp::setup(){



  updateColors(slider);//tail legnth param
  myBackGroundColor1 = myColors[ int( ofRandom(howManyColors))];

  ofBackground(myBackGroundColor1);

  //ofNoStroke();
  ofEnableSmoothing();       //smooth();
  ofSetBackgroundAuto(false);
  ofEnableAlphaBlending();
  int i = 0;
  while (i<howMany) {
    x[i] = ofRandom(0, ofGetWidth());
    y[i] = ofRandom(0, ofGetHeight());
    speed[i] = ofRandom(1, 5);
    i +=1;
  }

  //------------GUI

    gui.setup();
    gui.add(slider.setup("slider", 30, 0, 255));

}



//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    if (bClearBk) {
      updateColors(slider);
      bClearBk = false;
      myBackGroundColor1 = myColors[int(ofRandom(howManyColors))];
    }

    ofSetColor(myBackGroundColor1);
    ofFill(); // That was used to mix colors from background and drops
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    int i = 0;

    while (i < howMany) {

      ofSetColor(10, 182, 203, 80*speed[i]);
      ofFill();
      drawParticle(x[i], y[i], speed[i]);
      y[i] += speed[i]/4;


      if (y[i] > 1000) {
        y[i] = 0;
      }
      i +=1;
    }

    // ------------ GUI
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  if (key == ' ') {
    bClearBk = true;
  }
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
