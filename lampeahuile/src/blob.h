#include "ofMain.h"
#include "ofxTriangleMesh.h"

class variateur {
  public:
    float mini, vitesse, angle, val, diff;

    variateur();
    void init(float mini1, float maxi1, float etapes, float depart);
    void avance();
};


class blob {

  public:

    void dessine(bool bRot, ofColor _couleur, float _valPropRespY, float _valPropRespX, float _valPlusAngles, bool _bFilled, float _lineWidth, bool _usePolylineMethods, int _polySmooth, int _polyResampled, bool _beTriangleMesh);

	//Draw mesh triangles with distances
	void updateAndDrawTriangleMesh(const ofPolyline & line, ofColor mainColor, ofColor highlightColor);

	//Draw raw polylines with normals
	void drawWithNormals(const ofPolyline & polyline);

	float minimum_distance(ofPoint v, ofPoint w, ofPoint p);

    blob();
    void init(float ix, float ig);

    float x, y, vX, vY;
    vector<float> angles;
    vector<variateur> rayons;
    int n;
    ofColor couleur;
    variateur respiration;


};
