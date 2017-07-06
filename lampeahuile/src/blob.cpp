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

  n = floor(ofRandom(8, 20)); //10 works too
  float depart=ofRandom(90);
  //angles=new float[n];
  //rayons=new variateur[n];
  float dec = 360.0/n;
  int minR = 40;
  int maxR = 70;
  float raydebase = ofRandom(minR, maxR);//random(20,100);
  vY = -ofRandom(maxR -raydebase)*0.01;
  //vX=ofRandom(-0.03, 0.03);
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


//----------------------------------------------------
void blob::dessine(bool bRotated, ofColor _couleur, float _valPropRespX, float _valPropRespY, float _valPlusAngles, bool _bFilled, float _lineWidth, bool _usePolylineMethods, int _polySmooth, int _polyResampled, bool _beTriangleMesh) {

	if (bRotated) {
		ofPushMatrix();
		ofTranslate(0, ofGetHeight());
		ofRotate(-90);
	}

  float fx=0, fy=0, fx2=0, fy2=0, fx3=0, fy3=0;
  y += respiration.val*_valPropRespY;// 0.05;
  y+=vY;
  bool rien=true;
  respiration.avance();

  vX = _valPropRespX*0.1;
  x += _valPropRespX;// ofRandom(-_valPropRespX, _valPropRespX) + vX; // 0.4

  ofBeginShape();
  ofSetColor(_couleur);
  if (_bFilled) ofFill();
	else ofNoFill();
	
ofSetLineWidth(_lineWidth);

  float rotationPlus = _valPlusAngles; // ofRandom(-_valPlusAngles, _valPlusAngles); //0.01
  
  bool bPolyMode = _usePolylineMethods;
  ofPolyline cur;
  ofxTriangleMesh myTriangleMesh;

  for (int a=0; a<n; a++) {
    angles[a]+= rotationPlus;
    rayons[a].avance();
    float rad=angles[a] ;
    float ix=cos(rad)*(rayons[a].val+respiration.val);
    float ig=sin(rad)*(rayons[a].val-respiration.val);
   
	ofVec2f initPoint = ofVec2f(x + ix, y + ig);
	if(!bPolyMode)ofCurveVertex(initPoint.x, initPoint.y);
	else cur.addVertex(initPoint);
    
	if (_valPropRespY < 0) {
		if ((y - ig) < ofGetWidth()) {
			rien = false;
		}
	}
	else {
		if ((y + ig)>0) {
			rien = false;
		}
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
  if (!bPolyMode) {
	  ofCurveVertex(fx, fy);
	  ofCurveVertex(fx2, fy2);
	  ofCurveVertex(fx3, fy3);
	  ofEndShape(true);
  }
  else {
	  cur.addVertex(fx, fy);
	  //cur.addVertex(fx2, fy2);
	  //cur.addVertex(fx3, fy3);
	  //if (!_beTriangleMesh)cur.setClosed(true);
	  //cur.addVertex(cur[0]);
	  ofPolyline auxPol;
	  if (_polyResampled > 1) {
		  auxPol = cur;
		  //auxPol = cur.getResampledByCount(_polyResampled).getSmoothed(_polySmooth);
		  //auxPol = auxPol.getResampledBySpacing(_polyResampled);
	  }
	  else auxPol = cur;
	  
	  if (_beTriangleMesh) updateAndDrawTriangleMesh(auxPol, ofColor::orangeRed, ofColor::aquamarine);
	  else drawWithNormals(auxPol); 
  }





  if (rien==true) {
	  if (!bRotated) {
		  if (_valPropRespY > 0) {
			  y = ofGetHeight() + 200;
			  x = ofRandom(-20, ofGetWidth() + 20);
		  }
		  else {
			  y = 0 - 200;
			  x = ofRandom(-20, ofGetWidth() + 20);
		  }
	  }
	  else {
		 // y = ofGetWidth() + 200;
		 // x = ofRandom(-20, ofGetHeight() + 20);

		if (_valPropRespY > 0) {
			y = ofGetWidth() + 200;
			x = ofRandom(-20, ofGetHeight() + 20);
		}
		else {
			y = 0 - 200;
			x = ofRandom(-20, ofGetHeight() + 20);
		}
	  }
  }

  if (bRotated) {
	  ofPopMatrix();
  }
}

//--------------------------------------------------------------
void blob::updateAndDrawTriangleMesh(const ofPolyline& line, ofColor mainColor, ofColor highlightColor) {

	ofxTriangleMesh mesh;
	ofPolyline lineRespaced;

	if (line.size() > 2) {
		lineRespaced = line;

		// add the last point (so when we resample, it's a closed polygon)
		//lineRespaced.addVertex(lineRespaced[0]);
		// resample
		//lineRespaced = lineRespaced.getResampledBySpacing(20);
		// I want to make sure the first point and the last point are not the same, since triangle is unhappy: 
	//lineRespaced.getVertices().erase(lineRespaced.getVertices().begin());
		// if we have a proper set of points, mesh them: 
		if (lineRespaced.size() > 5) {

			// angle constraint = 33
			// size constraint = -1 (don't constraint triangles by size);

			mesh.triangulate(lineRespaced, 33, -1);


			// this is an alternative, constrain on size not angle: 
			//mesh.triangulate(lineRespaced, -1, 10);  

			// see ofxTriangleMesh.h for info. 

		}
	}


	//////////////////////////////////////////////////////
	//Update Distances
	vector < float > distances;
	vector < float > closestAngle;

	vector < ofPoint > pts = mesh.outputPts;

	distances.clear();
	closestAngle.clear();

	for (auto pt : pts) {

		float minDist = 10000;
		float minAngle = 0;
		for (int i = 0; i < lineRespaced.getVertices().size(); i++) {

			ofPoint a = lineRespaced[i];
			ofPoint b = lineRespaced[(i + 1) % lineRespaced.size()];
			float dist = minimum_distance(a, b, pt);
			if (dist < minDist) {
				minDist = dist;
				minAngle = atan2((b - a).y, (b - a).x);
			}
		}
		//        for (auto origPt : line.getVertices()){
		//            float dist = (origPt - pt).length();
		//            if (dist < minDist){
		//                minDist = dist;
		//            }
		//
		//
		//        }
		distances.push_back(minDist);
		closestAngle.push_back(minAngle);
	}

	///////////////////////////////////////////////////////
	//draw Mesh
	//mesh.draw();

	if (line.size() > 2) {
		ofMesh temp;

		temp.setMode(OF_PRIMITIVE_TRIANGLES);

		temp.addVertices(mesh.outputPts);

		float angToMatch = ofGetElapsedTimef();

		for (int i = 0; i < distances.size(); i++) {


			ofPoint up(cos(angToMatch), sin(angToMatch), 0);
			float ang = closestAngle[i];
			ofPoint dir(cos(ang), sin(ang), 0);

			float mix = up.dot(dir);

			if (mix < 0) mix = fabs(mix);
			//cout << mix << endl;

			//mix = ofMap(mix, -1,1, 0,1, true);

			float scale = ofMap(distances[i], 0, ofGetMouseX(), 1, 0, true) * mix;

			ofPoint a;
			a.set(mainColor.r, mainColor.g, mainColor.b);

			ofPoint b;
			b.set(highlightColor.r, highlightColor.g, highlightColor.b);

			ofPoint c = scale * b + (1 - scale) * a;

			temp.addColor(ofColor(c.x, c.y, c.z)); // TRY TO ADD TRANSPARENCY

		}

		for (int i = 0; i < mesh.triangles.size(); i++) {
			temp.addIndex(mesh.triangles[i].index[0]);
			temp.addIndex(mesh.triangles[i].index[1]);
			temp.addIndex(mesh.triangles[i].index[2]);
		}

		temp.draw();
	}
	
}

//--------------------------------------------------------------
void blob::drawWithNormals(const ofPolyline& _polyline) {

	ofPolyline polyline = _polyline;
	//polyline.getArea();

	// add the last point (so when we resample, it's a closed polygon)
	//polyline.addVertex(polyline[0]);
	//polyline.setClosed(true);

	for (int i = 0; i< (int)polyline.size()-1; i++) { // set -1 to avoid last repeatNext, but issues when smoothing
		bool repeatNext = i == (int)polyline.size() - 1;

		const ofPoint& cur = polyline[i];
		const ofPoint& next = repeatNext ? polyline[0] : polyline[i + 1];

		float angle = atan2f(next.y - cur.y, next.x - cur.x) * RAD_TO_DEG;
		float distance = cur.distance(next);

		if (repeatNext) {
			ofSetColor(255, 0, 255);
		}
		glPushMatrix();
		glTranslatef(cur.x, cur.y, 0);
		ofRotate(angle);
		ofDrawLine(0, 0, 0, distance);
		ofDrawLine(0, 0, distance, 0);
		glPopMatrix();
	}
}

//--------------------------------------------------------------
float blob::minimum_distance(ofPoint v, ofPoint w, ofPoint p) {
	// Return minimum distance between line segment vw and point p
	const float l2 = (v - w).lengthSquared();  // i.e. |w-v|^2 -  avoid a sqrt
	if (l2 == 0.0) return (p - v).length();   // v == w case
											  // Consider the line extending the segment, parameterized as v + t (w - v).
											  // We find projection of point p onto the line.
											  // It falls where t = [(p-v) . (w-v)] / |w-v|^2
	const float t = (p - v).dot(w - v) / l2;
	if (t < 0.0) return (p - v).length();       // Beyond the 'v' end of the segment
	else if (t > 1.0) return (p - w).length();  // Beyond the 'w' end of the segment
	const ofPoint projection = v + t * (w - v);  // Projection falls on the segment
	return (p - projection).length();
}
