#include "Blob.h"

Blob::Blob(){};

void Blob::init(int _id, float _radius, float _bodyRadius, float _totalPoints, ofxBox2d _box2d){

  // Create the empty
  //skeleton = new ArrayList<Body>();

  // Let's make a volume of joints!
  //ConstantVolumeJointDef cvjd = new ConstantVolumeJointDef();

  // Where and how big is the blob
  ofVec2f center;
  center.set(ofRandom(ofGetWidth()/2-50, ofGetWidth()/2+50), ofRandom(ofGetHeight()-400, ofGetHeight()));//new Vec2(ofGetWidth()/2, ofGetHeight()/2);
  radius = _radius;
  totalPoints = _totalPoints; //20;
  bodyRadius = _bodyRadius; //12;
  bAlive = true;
  id = _id;


  // first we add just a few circles
	for (int i=0; i<3; i++) {
		shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
		circle.get()->setPhysics(3.0, 0.53, 0.1);
		circle.get()->setup(_box2d.getWorld(), ofGetWidth()/2, 100+(i*20), 8);
		circles.push_back(circle);
	}

	// now connect each circle with a joint
	for (int i=0; i<circles.size(); i++) {

		shared_ptr<ofxBox2dJoint> joint = shared_ptr<ofxBox2dJoint>(new ofxBox2dJoint);

		if(i == 0) {
			joint.get()->setup(_box2d.getWorld(), circles[circles.size()-1].get()->body, circles[i].get()->body);
		}
		else {
			joint.get()->setup(_box2d.getWorld(), circles[i-1].get()->body, circles[i].get()->body);
		}

		joint.get()->setLength(25);
		joints.push_back(joint);
	}

  for (int i = 0; i < totalPoints; i++) {
  // Look polar to cartesian coordinate transformation!
    float theta = ofMap(i, 0, totalPoints, 0, TWO_PI);
    float x = center.x + radius * sin(theta);
    float y = center.y + radius * cos(theta);

  // Make each individual body
    b2BodyDef bd;
    bd.type = b2_dynamicBody;

    bd.fixedRotation = true; // no rotation!
    bd.position.Set(x, y);
    b2Body body;// = _box2d.createBody(bd);
    
  // The body is a circle
    b2CircleShape cs;
    cs.m_radius = bodyRadius;

  // Define a fixture
    b2FixtureDef fd;
    //fd.shape = cs;

  // For filtering out collisions
  //fd.filter.groupIndex = -2;

  // Parameters that affect physics
    fd.density = 1;

  // Finalize the body
    body.CreateFixture(fd);
  // Add it to the volume
    //cvjd.addBody(body);


  // Store our own copy for later rendering
    skeleton.push_back(body);
}

};

void Blob::display(){

  // Draw the outline
/*   beginShape();
   noFill();
   stroke(0);
   strokeWeight(1);
   for (Body b : skeleton) {
     Vec2 pos = box2d.getBodyPixelCoord(b);
     vertex(pos.x, pos.y);
   }
   endShape(CLOSE);

   // Draw the individual circles
   for (Body b : skeleton) {
     // We look at each body and get its screen position
     Vec2 pos = box2d.getBodyPixelCoord(b);
     // Get its angle of rotation
     float a = b.getAngle();
     pushMatrix();
     translate(pos.x, pos.y);
     rotate(a);
     fill(175);
     stroke(0);
     strokeWeight(1);
     ellipse(0, 0, bodyRadius*2, bodyRadius*2);
     popMatrix();
   }

   //recalc this center
   centroid = calcCentroidSkeleton(skeleton);

   //draw the center
   ellipse(centroid.x, centroid.y, bodyRadius*2, bodyRadius*2);
*/

};
