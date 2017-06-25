#include "Blob.h"


Blob::Blob(){

};

void Blob::init(int _id, float _radius, float _bodyRadius, float _totalPoints) {

  // Create the empty

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

  // Initialize all the points
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
    b2Body body;// = box2d.createBody(bd);

    // The body is a circle
    b2CircleShape cs;
    cs.m_radius = bodyRadius;

    // Define a fixture
    b2FixtureDef fd;
    fd.shape = cs;

    // For filtering out collisions
    //fd.filter.groupIndex = -2;

    // Parameters that affect physics
    fd.density = 1;

    // Finalize the body
    body.createFixture(fd);
    // Add it to the volume
    //cvjd.addBody(body);


    // Store our own copy for later rendering
    skeleton.add(body);

  }

  // These parameters control how stiff vs. jiggly the blob is
  //cvjd.frequencyHz = 10.0f;
  //cvjd.dampingRatio = 1.0f;

  // Put the joint thing in our world!
  //box2d.world.createJoint(cvjd);

};
