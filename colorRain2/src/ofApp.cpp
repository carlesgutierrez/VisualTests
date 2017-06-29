#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){

  ofSetFrameRate(50);

  updateColors(tail);//tail legnth param
  myBackGroundColor1 = myColors[ int( ofRandom(howManyColors))];

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
	gui.add(setSmoothing.setup(("SetSmoothing",true)));
    gui.add(tail.setup("tail", 30, 0, 100));
	last_tail = tail;
	gui.add(drawMode.setup("drawMode", 0, 0, 2));
	
	gui.add(sizeProportion.setup("sizeProportion", 1, 0, 1));
	gui.add(defaultSize.setup("defaultSize", 5, 0, 50));

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
void ofApp::updateParticles() {
	int i = 0;

	while (i < howMany) {

		ofSetColor(10, 182, 203, 80 * speed[i]);
		ofFill();
		drawParticle(x[i], y[i], speed[i]);
		x[i] += speed[i] / 4;


		if (x[i] > fbo.getWidth()) {
			x[i] = 0;
		}
		i += 1;
	}
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

	if (bClearBk) {
		myBackGroundColor1 = myColors[int(ofRandom(howManyColors))];
		bClearBk = false;
	}

    ofSetColor(myBackGroundColor1);
    ofFill(); // That was used to mix colors from background and drops
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());

  
	updateParticles();

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
