#include "ofApp.h"

//------------------------------------------------------------
void ofApp::setupParticles() {

	//TODO define Direction and Velocity. Set radom pos too

	for (int i = 0; i < howMany; i++) {
		float x = ofRandom(10, ofGetWidth()-10);
		float y = ofRandom(10, ofGetHeight()-10);
		speed[i] = ofRandom(1, 5);

		pos[i] = ofVec2f(x, y);
		vel[i] = ofVec2f(1, 0);
		//vel[i].rotate(radAngle, pos[i]);
	}

}

//--------------------------------------------------
void ofApp::setAngle2Velocity(float angle) {
	float radAngle = ofDegToRad(angle);
	for (int i = 0; i < howMany; i++) {
		vel[i] = ofVec2f(1, 0);
		vel[i].rotate(radAngle, pos[i]);
	}
}

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetFrameRate(50);

  updateColors(tail);//tail legnth param
  myBackGroundColor1 = myColors[ int( ofRandom(howManyColors))];

 
  setupParticles();

  //------------GUI

    gui.setup();
	gui.add(setSmoothing.setup(("SetSmoothing",true)));
    gui.add(tail.setup("tail", 30, 0, 100));
	last_tail = tail;
	gui.add(bRandomX.setup("bRandomX", true));
	gui.add(angleSlider.setup("angleSlider", 0, 0, 360));
	gui.add(deltaX.setup("deltaX", 0, -1, 1));
	gui.add(deltaY.setup("deltaY", 1, -1, 1));
	gui.add(drawMode.setup("drawMode", 0, 0, 2));
	
	gui.add(sizeProportion.setup("sizeProportion", 1, 0, 1));
	gui.add(defaultSize.setup("defaultSize", 5, 0, 50));

	gui.add(interpolationVel.setup("interpolationVel", 0.25, 0, 1));

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

  myBackGroundColor1 = myColors[int(ofRandom(howManyColors))];
  updateColors(tail);

}


//------------------------

void ofApp::updateColors(int tail) {

	myColors[0] = ofColor(184, 164, 156, tail);//(18, 15, 72);  // Fiery rose
	myColors[1] = ofColor(162, 224, 206, tail);//(162, 28, 88); // Pale Robin
	myColors[2] = ofColor(245, 214, 152, tail);//(40, 38, 96);  // Tuscan//}

}

//-------------------------------------------------------------
void ofApp::updateDrawParticles() {
	int i = 0;
	ofEnableAlphaBlending();

	//while (i < howMany) {
	for(int i = 0; i < howMany; i++){

		ofSetColor(10, 182, 203, 80 * speed[i]);
		ofFill();
		drawParticle(pos[i].x, pos[i].y, speed[i]);
		//x[i] += speed[i] / 4;

		//new method to move that particles
		ofVec2f NextPos;
		//deltaX = deltaX + speed[i] / 4;
		//deltaY += speed[i] / 4;
		NextPos.x = pos[i].x + deltaX;//+ speed[i] / 4; //+ vel[i]
		NextPos.y = pos[i].y + deltaY;//- 1;
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

  fbo.begin();

	ofSetCircleResolution(100);

    if (last_tail != tail) {
	  last_tail = tail;
	  updateColors(tail);
	  myBackGroundColor1 = myColors[int(ofRandom(howManyColors))];
    }

	if (last_angle != angleSlider) {
		last_angle = angleSlider;
		setAngle2Velocity(angleSlider);
	}

	if (bClearBk) {
		myBackGroundColor1 = myColors[int(ofRandom(howManyColors))];
		bClearBk = false;
	}

    ofSetColor(myBackGroundColor1);
    ofFill(); // That was used to mix colors from background and drops
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());

  
	updateDrawParticles();

    fbo.end();




}




//------------------
void ofApp::drawParticle(float _x, float _y, float _speed) {

	if (drawMode == 0) {
		//Draw Drop by speed
		ofDrawCircle(_x, _y, _speed*sizeProportion*defaultSize, _speed*sizeProportion*defaultSize);
	}
	else if (drawMode == 1) {
		//Draw Drop
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
