#include "ofMain.h"
#include "ofxBox2d.h"

class Boundary {
  public:
    // A boundary is a simple rectangle with x,y,width,and height
    float x;
    float y;
    float w;
    float h;

    // But we also have to make a body for box2d to know about it
    b2Body b;

    Boundary();

    void init(float x_,float y_, float w_, float h_);

    // Draw the boundary, if it were at an angle we'd have to do something fancier
    void display();

};
