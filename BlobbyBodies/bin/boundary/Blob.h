#include "ofMain.h"
#include "ofxBox2d.h"

class Blob {


  public:

    vector <shared_ptr<b2Body> > skeleton;
    float bodyRadius;  // The radius of each body that makes up the skeleton
    float radius;      // The radius of the entire blob
    float totalPoints; // How many points make up the blob
    //adding some extra control
    ofVec2f centroid;
    bool bAlive;
    int id = -1;
    // The Spring that will attach to the skeleton
    //Spring spring;

    // We should modify this constructor to receive arguments
    // So that we can make many different types of blobs
    Blob();

    void init(int _id, float _radius, float _bodyRadius, float _totalPoints, ofxBox2d _box2d);
    void applyForce(ofVec2f _force);
    ofVec2f calcCentroidSkeleton(vector<b2Body> _skeleton);
    void display();
    int isOutScreen(b2Body _body);
    bool blobOut();

};
