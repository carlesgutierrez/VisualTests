#include "ofApp.h"

//------------------------------------------------------------
void ofApp::setupParticles() {

	//TODO define Direction and Velocity. Set radom pos too

	for (int i = 0; i < howMany; i++) {
		float x = ofRandom(0, ofGetWidth()-0);
		float y = ofRandom(0, ofGetHeight()-0);
		speed[i] = ofRandom(1, 5);

		pos[i] = ofVec2f(x, y);
		vel[i] = ofVec2f(1, 0);
		//vel[i].rotate(radAngle, pos[i]);
	}

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
	signedNoiseData[0] = noiseAmount * ofSignedNoise(radialNoiseCursor);
	radialNoiseCursor += noiseStep;
}




//--------------------------------------------------------------
void ofApp::setup(){

  ofSetFrameRate(50);

  setupSignedNoiseDemo();

  setupParticles();

  //------------GUI
    gui.setup();
	
	gui.add(applyNoise.setup("applyNoise", false));
	gui.add(noiseStep.setup("noiseStep", 0.002, 0.005, 0.1));
	gui.add(noiseAmount.setup("noiseAmount", 1, 0, 1));
	gui.add(deltaX.setup("deltaX", +0.1, -1, 1));
	gui.add(deltaY.setup("deltaY", 1, -1, 1));
	gui.add(drawModeSize.setup("drawModeSize", 0, 0, 1));
	gui.add(drawModeColors.setup("drawModeColors", 0, 0, 1));
	gui.add(sizeProportion.setup("sizeProportion", 1, 0, 1));
	gui.add(defaultSize.setup("defaultSize", 5, 0, 50));
	gui.add(speedProportion.setup("speedProportion", 1, 0, 2));
	gui.add(interpolationVel.setup("interpolationVel", 0.5, 0, 1));
	gui.add(bRandomX.setup("bRandomX", false));

	//gui colors
	setupSomeInitColors();
	gui.add(colorParticle.setup("color Particle", colorParticle, ofColor(0, 0), ofColor(255, 255)));
	gui.add(colorBk.setup("color Background", colorBk, ofColor(0, 0), ofColor(255, 100)));
	//updateColorsBk(tail);//set some transparency
  //---------fbo

  //fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F_ARB); //GL_RGB32F_ARB

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



}

//------------------------

void ofApp::setupSomeInitColors() {

	ofColor myColorsParticles[howManyColors];
	myColorsParticles[0] = ofColor(184, 164, 156, 255);//(18, 15, 72);  // Fiery rose
	myColorsParticles[1] = ofColor(162, 224, 206, 255);//(162, 28, 88); // Pale Robin
	myColorsParticles[2] = ofColor(245, 214, 152, 255);//(40, 38, 96);  // Tuscan//}

	colorParticle = myColorsParticles[(int)ofRandom(howManyColors)];

	colorBk = ofColor(100, 100, 100, 30);//dafault bk color with 30 transparency : This will create the particle tail
}

//-----------------------------------------------------------
ofColor ofApp::updateColorSyte(int i) {

	ofColor auxColor;

	if (drawModeColors == 0) {
		//Use size for Alpha
		float transparencySpeed = 80 * speed[i];
		auxColor = ofColor(colorParticle, transparencySpeed);
	}
	else if (drawModeColors == 1) {
		//Use direct color alpha from Gui
		auxColor = colorParticle;
	}
	else if (drawModeColors == 2) {
		//TODO work in diferent Colors pallete
		//myFinalColor.setHsb()
	}

	return auxColor;
}

//-------------------------------------------------------------
void ofApp::updateDrawParticles() {
	int i = 0;
	ofEnableAlphaBlending();

	//while (i < howMany) {
	for(int i = 0; i < howMany; i++){

		ofColor myFinalParticleColor = updateColorSyte(i);
		
		ofSetColor(myFinalParticleColor);
		ofFill();
		drawParticle(pos[i].x, pos[i].y, speed[i]);

		//new method to move that particles
		if (applyNoise) {
			vel[i].x = deltaX*speed[i] * speedProportion;
			vel[i].y = deltaY*speed[i] * speedProportion;
			//ofVec2f perpendicularVel = vel[i].getPerpendicular();
			//vel[i].y += noiseRangeDelta * signedNoiseData[0];
			vel[i].rotate(signedNoiseData[0]*45);
		}
		else {
			vel[i].x = deltaX*speed[i] * speedProportion;
			vel[i].y = deltaY*speed[i] * speedProportion;
		}
		ofVec2f NextPos;
		NextPos.x = pos[i].x + vel[i].x;
		NextPos.y = pos[i].y + vel[i].y;
		pos[i].interpolate(NextPos, interpolationVel);
		
		//aply out of boundaries
		if (pos[i].x > ofGetWidth()+gap) {
			pos[i].x = -gap;
		}
		else if (pos[i].x < -gap) {
			pos[i].x = ofGetWidth();
		}
		if (pos[i].y > ofGetHeight()+ gap) {
			pos[i].y = -gap;
			//TODO add random X?
			if(bRandomX)pos[i].x = ofRandom(-gap, ofGetWidth() -gap);
		}
		else if (pos[i].y < -gap) {
			pos[i].y = ofGetHeight()+ gap;
			//TODO add random X?
		}
		//TODO Change this to udpate Position by applying VEL and DIR
	}

	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){

	updateSignedNoiseDemo();

  fbo.begin();

	ofSetCircleResolution(100);

    ofSetColor(colorBk);
    ofFill(); // That was used to mix colors from background and drops
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());

  
	updateDrawParticles();

 fbo.end();


}




//------------------
void ofApp::drawParticle(float _x, float _y, float _speed) {

	if (drawModeSize == 0) {
		//Draw Drop by speed
		ofDrawCircle(_x, _y, _speed*sizeProportion*defaultSize, _speed*sizeProportion*defaultSize);
	}
	else if (drawModeSize == 1) {
		//Draw All Drop same Sizes
		ofDrawCircle(_x, _y, defaultSize*sizeProportion, defaultSize*sizeProportion);
	}
	else {
	}

	//Draw Line
	//float midPointX = _x;
	//float midPointY = _y;
	//line(midPointX, _y, sliderValue, sliderValue);
}


//--------------------------------------------------------------
void ofApp::draw(){

	float scaledFboW = fbo.getWidth();
	float scaledFboH = fbo.getHeight();

    fbo.draw(0,0, scaledFboW, scaledFboH);

    // ------------ GUI
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	static bool bSmooth = false;

  if (key == ' ') {
	 setupSomeInitColors();
  }
  else if (key == 's') {
	  bSmooth = !bSmooth;
	  if (!bSmooth)ofEnableSmoothing;
	  else ofDisableSmoothing();
	  cout << "There is no difference Smooth or not smooth. now is :" << bSmooth << endl;
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
