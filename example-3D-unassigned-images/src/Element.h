//
//  Element.hpp
//  example-3D-assigned-images
//
//  Created by Tristan Espinoza on 5/23/17.
//
//

#pragma once

#include "ofMain.h"

class Element
{
public:
    
    void assignClusterIndex(int& _clusterIndex);
    int getClusterIndex();
    
    void setVertex(ofVec3f& _vertex);
    ofVec3f getVertex();
    
    void setImage(ofImage& _image, int _w, int _h);
    ofImage& getImage();
    
    int clusterIndex;
    ofVec3f vertex;
    ofImage image;
    
};
