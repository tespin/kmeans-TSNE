#pragma once

#include "ofMain.h"
#include "ofxCcv.h"
#include "ofxTSNE.h"
#include "ofxAssignment.h"
#include "ofxLearn.h"
#include "ofxGui.h"
#include "Element.h"

//#define NUMIMAGES 1500
//#define NUMCLUSTERS 12

#define NUMIMAGES 512
#define NUMCLUSTERS 5

//#define NUMIMAGES 512
//#define NUMCLUSTERS 25

struct ClusterGui
{
    ofxPanel gui;
    ofParameter<bool> drawImages;
    ofParameter<bool> drawPointCloud;
    int column;
    
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void initGui();
    void setupGui();
    void drawGui();
    
    void scan_dir_imgs(ofDirectory dir);
    void calcCamPos();
    
    std::vector<ClusterGui> clustersGui;
    
    ofxCcv ccv;
    
    ofxTSNE tsne;
    std::vector<ofVec3f> tsnePoints;
    
    ofxLearnKMeans clusterer;
    std::vector<double> instances[NUMIMAGES];
    std::vector<int> clusters;
    ofColor colors[NUMCLUSTERS];
    
    ofEasyCam cam;
    
    std::vector<ofFile> imageFiles;
    std::vector<ofImage> images;
    std::vector<std::vector<float> > encodings;
    std::vector<std::vector<ofxCcv::Classification> > results;
    std::vector<std::vector<double> > tsneVecs;
    
    std::vector<Element> elementVector;
    std::vector<ofVec3f> posVector;
    
    ofSpherePrimitive sphere;
    
    ofVec3f camPos;
    int w, h, d;
    float perplexity, theta;
    float scale;
};
