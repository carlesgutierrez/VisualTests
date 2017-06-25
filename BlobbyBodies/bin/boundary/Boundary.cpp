#include "Boundary.h"


Boundary::Boundary(){
}

void Boundary::init(float x_,float y_, float w_, float h_) {
  x = x_;
  y = y_;
  w = w_;
  h = h_;

  // Define the polygon
  b2PolygonShape sd;

  // Figure out the box2d coordinates
  float box2dW;
  float box2dH;
  // We're just a box
  sd.setAsBox(box2dW, box2dH);

  // Create the body
  b2BodyDef bd;

  // = new BodyDef();
  bd.type = BodyType.STATIC;
  bd.position.set(box2d.coordPixelsToWorld(x,y));
  b = box2d.createBody(bd);

  // Attached the shape to the body using a Fixture
  b.createFixture(sd,1);
}

// Draw the boundary, if it were at an angle we'd have to do something fancier
void display() {
  ofSetColor(0);
  ofFill();
  //rectMode(CENTER);
  ofDrawRectangle(x,y,w,h);
}
