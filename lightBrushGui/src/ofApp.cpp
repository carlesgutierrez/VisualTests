#include "ofApp.h"

//--------------------------------------------
void ofApp::updateTimer(float nextvalue) {

  float distMovement = ofDist(0, posBrush.y, 0, nextvalue);

  //println("distMovement = " + str(distMovement));
  //ofDrawBitmapString("distMovement = " + ofToString(distMovement), 10,100);

  if (distMovement > 5) {
    timerActive = 1;
  } else if (distMovement > 10) {
    timerActive = 2;
  } else {
    timerActive = 0;
  }
}

//-----------------
void ofApp::updateBrush() {
  // Get a noise value based on xoff and scale it according to the window's width
  float n = ofNoise(xoff)*float(ofGetHeight());
  // With each cycle, increment xoff
  xoff += sliderValue_IncMov;

  updateTimer(n);

  //Update Color Brush
  //float newColorValue = timerActive + colorhue;//map(n, 0, height, 0, 360);

  float newColorValue;
  newColorValue = fmod(sliderValue_Color+colorhue, 100);
  //ofDrawBitmapString("newColorValue = " + ofToString(newColorValue), 10,130);

  colorhue = newColorValue;
  //Update Y pos
  posBrush.y = n;
}

//--------------------------------------------------------------
void ofApp::setup(){

  //Stroke(0, 20);

  ofEnableSmoothing();       //smooth();
  ofSetBackgroundAuto(false);
  ofEnableAlphaBlending();

  posBrush.set(5, ofGetWidth()*.5 );
  dimBrush.set(ofGetWidth()*0.95, ofGetHeight()/8 );

  //for (int i=0; i<howManyColors; i++) {
  //myColors[0] = ofColor(18, 15, 72);// Fiery rose
  //myColors[1] = ofCcolor(162, 28, 88);// Pale Robin
  //myColors[2] = ofCcolor(354, 62, 99, 200);// Fiery rose
  //}

  myColors[0] = ofColor(184,164,156);//(18, 15, 72);  // Fiery rose
  myColors[1] = ofColor(162,224,206);//(162, 28, 88); // Pale Robin
  myColors[2] = ofColor(245,214,152);//(40, 38, 96);  // Tuscan//}

  myBackGroundColor1 = myColors[int(ofRandom(howManyColors))];


  //------------GUI

    gui.setup();
    gui.add(sliderValue_Color.setup("sliderValue_Color", 0.01, 0, 1));
    gui.add(sliderValue_IncMov.setup("sliderValue_IncMov", 0.001, 0, 0.1));

    //---------fbo

  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F_ARB);

  fbo.begin();
    ofBackground( 255, 255, 255 );
  fbo.end();

}

//--------------------------------------------------------------
void ofApp::update(){

  fbo.begin();
  if (bClearBk) {
     bClearBk = false;
     myBackGroundColor1 = myColors[int(ofRandom(howManyColors))];
     ofBackground(myBackGroundColor1);
   }

   updateBrush();

   // Base its hue by the rectangle movement
   //float newColorValue = colorhue+weight+timerActive*0.5;
   //println("Color Is "+str(newColorValue));
   ofColor c = ofColor::fromHsb(colorhue, 255, 255, 3);
   ofSetColor(c); // add 30 an alpha blended background
   ofFill();
   //stroke(colorhue, 100, 100, 30);

   //line(mouseX, mouseY, pmouseX, pmouseY);
   ofDrawRectangle(posBrush.x, posBrush.y, dimBrush.x, dimBrush.y);
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
  if (key == 'c') {
    bClearBk = true;
  }
  //else if (key == '+') {
  //  colorhue = colorhue+3;
  //  if (colorhue>360) colorhue = 0;
  //} else if (key == '-') {
  //  colorhue = colorhue-3;
  //  if (colorhue<0) colorhue = 360;
  //}

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
  //if (bTimerActive == false) {
  //  bTimerActive = true;
  //  timerActive = 0;
  //}

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
