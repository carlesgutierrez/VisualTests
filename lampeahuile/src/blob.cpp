#include "blob.h"
#include <math.h>

//--------
variateur::variateur() {

}

//-------------
void variateur::init(float mini1, float maxi1, float etapes, float depart){
  val=mini;
  angle=depart;
  mini=mini1;
  diff=maxi1-mini1;
  vitesse=360.0/etapes;
}

//-------------------
void variateur::avance() {
  angle+=vitesse;
  float rad = (cos(angle/(180.0/PI))+1)/2;
  val= mini+rad*diff;
}

//---------------

blob::blob() {

  //couleur =  ofColor(227, 64, 88);//color(354, 62, 99, 200);//color(351, 72, 89, 200) //TODO Check why not work assign a color already defined

  n = floor(ofRandom(8, 20)); //10 works too
  float depart=ofRandom(90);
  //angles=new float[n];
  //rayons=new variateur[n];
  float dec = 360.0/n;
  float raydebase = ofRandom(40, 70);//random(20,100);
  vY=-ofRandom(100-raydebase)*0.01;
  vX=ofRandom(-0.03, 0.03);
  respiration.init(ofRandom(-25, -15), 3, 300, ofRandom(100, 300));
  ////  minray=raydebase*0.1; maxray=minray+raydebase*0.1;
  for (int a=0; a<n; a++) {
    angles.push_back((a*dec)/(180.0/PI));
    variateur r;
    r.init(raydebase+ofRandom(raydebase/17), raydebase+ ofRandom(raydebase/30, raydebase/20), ofRandom(120, 160), ofRandom(360));
    rayons.push_back(r);
  }
}
//-------------

void blob::init(float ix, float ig){
  x =ix;
  y =ig;


}


//--------------

void blob::dessine(bool bRotated, ofColor _couleur) {

	if (bRotated) {
		ofPushMatrix();
		ofTranslate(0, ofGetHeight());
		ofRotate(-90);
	}

  float fx=0, fy=0, fx2=0, fy2=0, fx3=0, fy3=0;
  y+=respiration.val*0.05;
  y+=vY;
  bool rien=true;
  respiration.avance();
  x+=ofRandom(-0.4, 0.4)+vX;

  ofBeginShape();
  ofSetColor(_couleur);
  ofFill();
  //fill(_couleur);
  float plus=ofRandom(-0.01, 0.01);
  for (int a=0; a<n; a++) {
    angles[a]+=plus;
    rayons[a].avance();
    float rad=angles[a] ;
    float ix=cos(rad)*(rayons[a].val+respiration.val);
    float ig=sin(rad)*(rayons[a].val-respiration.val);
    ofCurveVertex(x+ix, y+ig);
    if ((y+ig)>0) {
      rien=false;
    }
    if (a==0) {
      fx = x+ix;
      fy = y+ig;
    }
    if (a==1) {
      fx2 = x+ix;
      fy2 = y+ig;
    }
    if (a==2) {
      fx3 = x+ix;
      fy3 = y+ig;
    }
  }
  ofCurveVertex(fx, fy);
  ofCurveVertex(fx2, fy2);
  ofCurveVertex(fx3, fy3);
  ofEndShape(true);

  if (rien==true) {
	  if (!bRotated) {
		  y = ofGetHeight() + 200;
		  x = ofRandom(-20, ofGetWidth() + 20);
	  }
	  else {
		  y = ofGetWidth() + 200;
		  x = ofRandom(-20, ofGetHeight() + 20);
	  }
  }

  if (bRotated) {
	  ofPopMatrix();
  }
}

//-----------

poussiere::poussiere() {
  y=ofRandom(ofGetHeight());
  init();
}

//----------------
void poussiere::init() {
  x=ofRandom(ofGetHeight());
}

//-------
void poussiere::dessine() {
  y+=ofRandom(0.3, 2);
  x+=ofRandom(-1, 1);
  if (y>ofGetHeight()+10) {
    y=-10;
    init();
  }
  //ofPoint(x, y);
  //ofDrawCircle(x,y,1);
}
