//
//  Element.cpp
//  example-3D-assigned-images
//
//  Created by Tristan Espinoza on 5/23/17.
//
//

#include "Element.h"

void Element::assignClusterIndex(int& _clusterIndex)
{
    clusterIndex = _clusterIndex;
}

int Element::getClusterIndex()
{
    return clusterIndex;
}

void Element::setVertex(ofVec3f& _vertex)
{
    vertex = _vertex;
}

ofVec3f Element::getVertex()
{
    return vertex;
}

void Element::setImage(ofImage& _image, int _w, int _h)
{
    // resize image here
    if (_image.getWidth() > _image.getHeight())
    {
        _image.crop((_image.getWidth()-_image.getHeight()) * 0.5, 0, _image.getHeight(), _image.getHeight());
    }
    else if (_image.getHeight() > _image.getWidth())
    {
        _image.crop(0, (_image.getHeight()-_image.getWidth()) * 0.5, _image.getWidth(), _image.getWidth());
    }
    
    _image.resize(_w, _h);
    
    image = _image;
}

ofImage& Element::getImage()
{
    return image;
}
