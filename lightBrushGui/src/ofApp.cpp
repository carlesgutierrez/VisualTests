#include "ofApp.h"

//--------------------------------------------
void ofApp::updateTimer(float nextvalue) {

  float distMovement = ofDist(0, posBrush.y, 0, nextvalue);

  //println("distMovement = " + str(distMovement));
  //ofDrawBitmapString("distMovement = " + ofToString(distMovement), 10,100);

  if (distMovement < 0) {
	  cout << "can be neg" << endl;
  }

  if (distMovement > hightMoveDist) {
    timerActive = 1;
  } else if (distMovement > midMoveDist) {
    timerActive = 2;
  } else {
	//Set Slow Vel
    timerActive = 0;
  }
}

//-----------------
void ofApp::updateBrush() {
  // Get a noise value based on xoff and scale it according to the window's width
  float n = signedNoiseData[0] *float(ofGetHeight());

  //Update Color Hue by Calc Distance to next noise value
  updateTimer(n);

  float auxInc = singedInc*timerActive + colorhue;
  if (auxInc > 280 || auxInc < 10)singedInc *= -1;
  float newColorValue = fmod(auxInc,360);
  colorhue = newColorValue;

  //Update Y pos
  posBrush.y = n;
}

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetFrameRate(50);
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

  //Init Colors
  myBackGroundColor = ofColor(162, 28, 88, 0);// Pale Robin
  myActionColor = ofColor(354, 62, 99, 200);// Fiery rose

  //------------GUI

	gui.setup();
	
	float auxSizeBrush = ofGetHeight() / 8;
	gui.add(sizeBrush.setup("Size Bursh", auxSizeBrush, 0, auxSizeBrush));
	gui.add(alphaActionColor.setup("alphaActionColor", 10, 0, 255));
	gui.add(alphaBkColor.setup("alphaBkColor", 1, 0, 100));
	gui.add(ModeBlend.setup("ModeBlend", 1, 0, 5));
	
	gui.add(sliderValue_Color.setup("sliderValue_Color", 0.001, 0.0001, 0.1));
	gui.add(sliderValue_IncMov.setup("sliderValue_IncMov", 0.001, 0.0001, 0.002));
	gui.add(myBackGroundColor.setup("myBackGroundColor", myBackGroundColor, ofColor(0, 0), ofColor(255, 100)));
	gui.add(myActionColor.setup("myActionColor", myActionColor, ofColor(0, 0), ofColor(255, 255)));
	gui.add(modeDrawFloors.setup("modeDrawFloors", 1, 0, 2));

	gui.add(noiseStep.setup("noiseStep", 0.002, 0.001, 0.02));
	gui.add(noiseAmount.setup("noiseAmount", 1, 0, 1));
	gui.add(hightMoveDist.setup("hightMoveDist", 5, 0, 10));
	gui.add(midMoveDist.setup("midMoveDist", 2, 0, 10));
	//ImGui::SliderFloat("noiseStep", &noiseStep, 0.005, 0.1);
	//ImGui::SliderFloat("noiseAmount", &noiseAmount, 0, 1);

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
  fboBack.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F_ARB);

  fbo.begin();
  ofClear(255, 0);
  fbo.end();

  fboBack.begin();
  ofClear(255, 0);
  fboBack.end();

}

//--------------------------------------------------------------
void ofApp::setupSignedNoiseDemo() {

	for (int i = 0; i<howManyHistoryNoise; i++) {
		signedNoiseData[i] = 0;
	}

	radialNoiseCursor = 0.0;
}

//--------------------------------------------------------------
void ofApp::updateSignedNoiseDemo() {

	// Shift all of the old data forward through the array
	for (int i = (howManyHistoryNoise - 1); i>0; i--) {
		signedNoiseData[i] = signedNoiseData[i - 1];
	}

	// Compute the latest data, and insert it at the head of the array.
	// Here is where ofSignedNoise is requested.
	signedNoiseData[0] = noiseAmount * ofMap(ofSignedNoise(radialNoiseCursor), -1, 1, 0, 1);
	radialNoiseCursor += noiseStep;
}

//--------------------------------------------------------------
void ofApp::update(){

  updateSignedNoiseDemo();

  fbo.begin();

  ofEnableBlendMode(OF_BLENDMODE_ALPHA);//OF_BLENDMODE_ADD
  if (modeDrawFloors > 0) {
	  //filter(BLUR, 0.5);
	  drawFloors(myBackGroundColor, modeDrawFloors, bInvertPaletteColors, false);
  }
  else {
	  ofSetColor(myBackGroundColor, alphaBkColor);
	  ofFill(); // That was used to mix colors from background and drops
	  ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
  }

  int auxBlendMode = ModeBlend;
  ofEnableBlendMode((ofBlendMode)auxBlendMode);//OF_BLENDMODE_ADD

   updateBrush();

   // Base its hue by the rectangle movement
   //float newColorValue = colorhue+weight+timerActive*0.5;
   //println("Color Is "+str(newColorValue));
   ofColor c = ofColor::fromHsb(colorhue, 255, 255, alphaActionColor);
   ofSetColor(c); // add 30 an alpha blended background
   ofFill();
   //stroke(colorhue, 100, 100, 30);

   //line(mouseX, mouseY, pmouseX, pmouseY);
   ofDrawRectangle(posBrush.x, posBrush.y, dimBrush.x, sizeBrush);
  fbo.end();

  ofDisableAlphaBlending();

}

//--------------------------------------------------------------
void ofApp::draw(){

  fbo.draw(0,0);

  // ------------ GUI
  gui.draw();

  ofSetColor(255);
  ofDrawBitmapString("Fps " + ofToString(ofGetFrameRate(), 1), 10, 10);
  ofDrawBitmapString("newColorValue = " + ofToString(colorhue), 10, 30);

}

//--------------------------
void ofApp::drawFloors(ofColor _mainColor, int _modedrawFloors, bool _invertOrder, bool _bRotated) {

	ofFill();

	ofVec2f posFloor;
	ofVec2f dimFloor;

	ofPushMatrix();
	if (_bRotated) {
		posFloor.set(0, ofGetWidth() / 8);
		dimFloor.set(ofGetHeight(), ofGetWidth() / 8); // 10 H
		ofTranslate(0, ofGetHeight());
		ofRotate(-90);
	}
	else {
		posFloor.set(0, ofGetHeight() / 8);
		dimFloor.set(ofGetWidth(), ofGetHeight() / 8); // 10 H
	}

	for (int i = 0; i<8; i++) {
		setScaledColor(_mainColor, i, 0, 8, _modedrawFloors, _invertOrder); //ofColor baseColor, int idStep, int minSteps, int maxSteps, int mode, bool invertOrder) {

		ofDrawRectangle(posFloor.x, posFloor.y * i, dimFloor.x, dimFloor.y);
	}
	ofPopMatrix();

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
