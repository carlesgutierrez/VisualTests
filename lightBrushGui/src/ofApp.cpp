#include "ofApp.h"

//--------------------------------------------
float ofApp::updateTimer(float nextvalue) {

  float timerActive = 0;

  distMovement = ofDist(0, posBrush.y, 0, nextvalue);

  if (distMovement < 0) {
	  //cout << "can be neg" << endl;
  }

  if (distMovement > hightMoveDist) {
    timerActive = incMinValue;
  } else if (distMovement > midMoveDist) {
    timerActive = incMaxValue;
  } else {
	//Set 0 changes
    timerActive = 0;
  }

  return timerActive;
}

//-----------------------------------------------------
ofColor ofApp::updateColorAction(int _modeColorAction, ofColor _colorAction, float _yNormPos1, float _yNormPos2) {
	
	float incrementedValue1;
	float incrementedValue2;

	//General modif checking posBrush.y
	incrementedValue1 = _yNormPos1*ofGetHeight();
	float counterIncrement = updateTimer(incrementedValue1);
	
	if (_modeColorAction == 1) {
		ofColor auxColor = _colorAction;
		float auxMapped = ofMap(_yNormPos1, 0, 1, 0, 1);
		
		incrementedValue1 = _yNormPos1 * 360;//Scaling to be able to treat it as integuer range at [0..360]
		if (incrementedValue1 < 0) incrementedValue1 = 0;

		//apply incrementedValue1
		//to pick color gradient updatingTimer
		float auxInc = singedInc*counterIncrement + colorhue;
		if (auxInc > 350 || auxInc < 10) {
			singedInc *= -1;
		}
		float newColorValue = fmod(auxInc, 360);
		float normNewColorIndex = newColorValue /360;
		colorhue = newColorValue;

		auxColor = myGradientColor.getColorAtPercent(normNewColorIndex);

		//Apply incrementValue2
		//to BrigtnessValue
		incrementedValue2 = _yNormPos2 * 255;
		colorBrightNess = incrementedValue2;
		auxColor.setBrightness(incrementedValue2);
		if (auxColor.getSaturation() == 0) {
			ofLogVerbose() << "GOT COLOR BLACK DAMMMM";
		}


		return auxColor;
	}
	else {
		//Update Color Hue by Y Distance to next position

		incrementedValue2 = _yNormPos2*255;
		if (incrementedValue2 < 1) incrementedValue2 = 1;//brigtness can not be 0

		//ColorHue set by incrementedValue1
		float auxInc = singedInc*counterIncrement + colorhue;
		if (auxInc > 280 || auxInc < 10)singedInc *= -1;
		float newColorValue = fmod(auxInc, 360);
		colorhue = newColorValue;

		//BrigtnessValue
		colorBrightNess = incrementedValue2;

		//Update my color with the Interactive Values
		ofColor auxColor = _colorAction;
		auxColor.setHue(colorhue);
		auxColor.setBrightness(incrementedValue2);
		if (auxColor.getSaturation() == 0) {
			ofLogVerbose() << "GOT COLOR BLACK DAMMMM";
		}
		return auxColor;
	}


}
//-----------------
void ofApp::updateBrush() {
  // Get a noise value based on xoff and scale it according to the window's width
	float valId1; //next pos
	float valId2;

	if (noiseInteractionMethod == LIGHTBRUSH_NOISEMODE_WALKERS) {
		updateInteractiveData(myInteractiveDataClass.myInteractiveObjectsVector, valId1, valId2); //Updates n value
	}
	else {
		valId1 =  signedNoiseData[0] * float(ofGetHeight()); //Rescale
	}
	
  myActionColor = updateColorAction(modeColorAction, myActionColor, valId1, valId2);

  //Update Y pos
  posBrush.y = valId1*ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetFrameRate(50);
  //Stroke(0, 20);

  ofEnableSmoothing();       //smooth();
  ofSetBackgroundAuto(false);
  ofEnableAlphaBlending();

  posBrush.set(0, ofGetWidth()*.5 );
  dimBrush.set(ofGetWidth(), ofGetHeight()/8 );

  //Interaction Y class
  myInteractiveDataClass.setup(2); //Set just one particle   //TODO 3? 0  Hue, 1 Sat , And 2 Value

  //Init Colors
  myBackGroundColor = ofColor(162, 28, 88, 0);// Pale Robin
  myActionColor = ofColor(354, 62, 99, 200);// Fiery rose
  
  //Set main colors to move inside
  myGradientColor.reset();
  myGradientColor.addColor(ofColor(myCompositionColor1));
  myGradientColor.addColor(ofColor(myCompositionColor2));
  myGradientColor.addColor(ofColor(myCompositionColor3));

  //Easings for brightness
  ofSetColor(bInvertEasing * 255);
  for (size_t i = 0; i<easings.size(); i++) {
	  plots[i].setMode(OF_PRIMITIVE_LINE_STRIP);
	  for (int x = 0; x < ofGetWidth(); x++) {
		  auto y = ofxeasing::map(x, 0.f, ofGetWidth(), 0.f, ofGetHeight(), easings[i]);
		  plots[i].addVertex(ofVec3f(x, ofGetHeight() - y)); // invert y to account for OF y grows downwards
	  }
  }


  //------------GUI
  myMainGui.setup();

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

  fbo.begin();
  ofClear(255, 0);
  fbo.end();


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


//-------------------------------------------------------------
void ofApp::updateInteractiveData(vector<shared_ptr<LightBrushInteractionObject>> _myInteractiveObjects, float &valId0, float &valId1) {
	
	for (int i = 0; i < _myInteractiveObjects.size(); i++)
	{
		float thisRadius = 5;
		ofVec2f mLoc = _myInteractiveObjects[i]->normPosFilter;

		//TODO
		//Do Something with this data
		//update Next pos omnly with fisrt element
		if (i == 0) {
			valId0 = mLoc.y;
		}
		if (i == 1) {
			//Aply some easing factors
			if(bInvertEasing)mLoc.y = 1 - mLoc.y; //Lets invert that values to treat black at the end of easing
			
			float easingValApplied = ofxeasing::map(mLoc.y, 0.f, 1.f, 0.f, 1.f, easings[selectedEasingId]);

			//Update var
			valId1 = easingValApplied;
		}

	}

}

//--------------------------------------------------------------
void ofApp::update(){

 if (noiseInteractionMethod == LIGHTBRUSH_NOISEMODE_WALKERS) {
	 //Interactive sensor
	 myInteractiveDataClass.update();
 }
 else {
	 //Signed Noise Method
	 updateSignedNoiseDemo();
 }
  
  
  fbo.begin();

  ofEnableBlendMode(OF_BLENDMODE_ALPHA);//OF_BLENDMODE_ADD
 
  //Draw just background Color i've you wish
  ofSetColor(myBackGroundColor, alphaBkColor);
  ofFill();
  ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

  int auxBlendMode = ModeBlend;
  ofEnableBlendMode((ofBlendMode)auxBlendMode);//OF_BLENDMODE_ADD

  //Update color and position brush
   updateBrush();

   //Draw the Color LIght Rectanble Brush with some alpha for softer end.
   //Draw final Color Rectangle
   ofColor c = myActionColor;
  
   ofSetColor(c); // add 30 an alpha blended background
   ofFill();
   ofDrawRectangle(posBrush.x, posBrush.y, dimBrush.x, sizeBrush);
  fbo.end();

  ofDisableAlphaBlending();

}

//----------------------------------------------
void ofApp::resetColorGradient() {
	myGradientColor.reset();
	myGradientColor.addColor(ofColor(myCompositionColor1));
	myGradientColor.addColor(ofColor(myCompositionColor2));
	myGradientColor.addColor(ofColor(myCompositionColor3));
}

//--------------------------------------------------------------
void ofApp::draw(){

	myGradientColor.drawDebug(0, 0, ofGetWidth(), ofGetHeight());

	//ofSetBackgroundColor(100);
  fbo.draw(0, 0);



  // ------------ GUI
  ofSetColor(255);
  myMainGui.begin();

  //Interaction Mode Gui Options
  ImGui::PushItemWidth(70);
  ImGui::SliderInt("noiseInteractionMethod", &currentInteractionMethod, 0, 1);
  noiseInteractionMethod = (lightBrushNoiseMode)currentInteractionMethod;
  if (noiseInteractionMethod == LIGHTBRUSH_NOISEMODE_WALKERS) {
	  myInteractiveDataClass.drawGui();
  }
  else {
	  ImGui::Text("Noise 1d Method");
	  ImGui::SliderFloat("Step Noise", &noiseStep, 0.001, 0.02);

	  ImGui::SliderFloat("Amount Noise", &noiseAmount, 0, 1);

  }
  ImGui::PopItemWidth();

  ImGui::PushItemWidth(140);

  //Color Gui Options
  ImGui::Separator();
  ImGui::ColorEdit3("myBackGroundColor", (float*)&myBackGroundColor);
  ImGui::SliderInt("alphaBkColor", &alphaBkColor, 0, 4);
  ImGui::ColorEdit3("myActionColor", (float*)&myActionColor);
  ImGui::SliderInt("alphaActionColor", &alphaActionColor, 1, 255);

  if (ImGui::Checkbox("Invert Easing", &bInvertEasing)) {
	  plots.clear();
	  plots.resize(easings.size());
	  //ofSetColor(bInvertEasing*255);
	  for (size_t i = 0; i<easings.size(); i++) {
		  plots[i].setMode(OF_PRIMITIVE_LINE_STRIP);
		  for (int x = 0; x < ofGetWidth(); x++) {
			  auto y = ofxeasing::map(x, 0.f, ofGetWidth(), 0.f, ofGetHeight(), easings[i]);
			  if(!bInvertEasing)plots[i].addVertex(ofVec3f(x, ofGetHeight() - y)); // invert y to account for OF y grows downwards
			  else plots[i].addVertex(ofVec3f(x, y));
		  }
	  }
  }
  ComboCinder("Easing brightness", &selectedEasingId, easingNames, easingNames.size());
  
  ImGui::Separator();
  if (ImGui::ColorEdit3("myCompositionColor1", (float*)&myCompositionColor1))resetColorGradient();
  if(ImGui::ColorEdit3("myCompositionColor2", (float*)&myCompositionColor2))resetColorGradient();
  if(ImGui::ColorEdit3("myCompositionColor3", (float*)&myCompositionColor3))resetColorGradient();
  ImGui::PopItemWidth();

  //Color Gui Options
  ImGui::PushItemWidth(70);
  ImGui::Text("Color Options");
  ImGui::SliderInt("hightMoveDist", &hightMoveDist, 0, 10);
  ImGui::SameLine();
  ImGui::SliderInt("IncMinValue", &incMinValue, 1, 4);
  ImGui::SliderFloat("CurrentDist=", &distMovement, 0, 10);
  ImGui::SliderInt("midMoveDist", &midMoveDist, 0, 10);
  ImGui::SameLine();
  ImGui::SliderInt("IncMaxValue", &incMaxValue, 1, 4);
      
  ImGui::Text("Blending Options");
  float auxSizeBrush = ofGetHeight() / 8;
  ImGui::SliderInt("Size Brush", &sizeBrush, 1, auxSizeBrush);
  ImGui::SliderInt("ModeBlend", &ModeBlend, 0, 2);


  static bool bDrawDebug = false;
  ImGui::Checkbox("Draw Debug Info", &bDrawDebug);

  if (bDrawDebug) {
	  //INTERACTIVE DATA GUI
	  if (noiseInteractionMethod == LIGHTBRUSH_NOISEMODE_WALKERS) {
		  //Interactive walkers
		   myInteractiveDataClass.draw();

	  }

	  //Draw plots
	  auto x = 0;
	  auto y = 0;
	  ofPushMatrix();
	  ofSetColor(bInvertEasing * 255);
	  ofTranslate(x, y);
	  plots[selectedEasingId].draw();
	  ofPopMatrix();
	

	  //Draw Control Colors Values
	  ofSetColor(255);
	  ofDrawBitmapString("Fps " + ofToString(ofGetFrameRate(), 1), 10, 10);
	  ofDrawBitmapString("newColorValue = " + ofToString(colorhue), 10, 30);
	  ofDrawBitmapString("colorBrightNess = " + ofToString(colorBrightNess), 10, 50);
	  
  }

  ImGui::PopItemWidth();


  myMainGui.end();

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
