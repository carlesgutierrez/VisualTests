#include "ofMain.h"
#include "ofxBox2d.h"


class Blob {
  public:
    vector <b2Body> skeleton;
        //vector <shared_ptr<b2Body> > skeleton;
    float bodyRadius;  // The radius of each body that makes up the skeleton
    float radius;      // The radius of the entire blob
    float totalPoints; // How many points make up the blob

    ofVec2f centroid;
    bool bAlive;
    int id = -1;


    vector		<shared_ptr<ofxBox2dCircle> >	circles;		  //	default box2d circles
    vector		<shared_ptr<ofxBox2dJoint> >		joints;				  //	joints

    Blob();

    void init(int _id, float _radius, float _bodyRadius, float _totalPoints, ofxBox2d _box2d);
    void display();

};
