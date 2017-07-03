#include "ofMain.h"

class variateur {
  public:
    float mini, vitesse, angle, val, diff;

    variateur();
    void init(float mini1, float maxi1, float etapes, float depart);
    void avance();
};


class blob {

  public:

    void dessine(bool bRot);

    blob();
    void init(float ix, float ig);

    float x, y, vX, vY;
    vector<float> angles;
    vector<variateur> rayons;
    int n;
    ofColor couleur;
    variateur respiration;


};

class poussiere {
  public:
    float x, y;

    poussiere();
    void init();
    void dessine();
};
