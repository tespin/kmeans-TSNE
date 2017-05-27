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
    if (_image.getWidth() > _image.getHeight())
    {
        _image.crop((_image.getWidth()-_image.getHeight()) * 0.5, 0, _image.getHeight(), _image.getHeight());
    }
    else if (_image.getHeight() > _image.getWidth())
    {
        _image.crop(0, (_image.getHeight()-_image.getWidth()) * 0.5, _image.getWidth(), _image.getWidth());
    }
    
    _image.resize(_w, _h);
    
//    for (int i = 0; i < images.size(); i++)
//    {
//        if (images[i].getWidth() > images[i].getHeight())
//        {
//            images[i].crop((images[i].getWidth()-images[i].getHeight()) * 0.5, 0, images[i].getHeight(), images[i].getHeight());
//        }
//        else if (images[i].getHeight() > images[i].getWidth())
//        {
//            images[i].crop(0, (images[i].getHeight()-images[i].getWidth()) * 0.5, images[i].getWidth(), images[i].getWidth());
//        }
//        images[i].resize(w, h);
//    }
    
    image = _image;
}

ofImage& Element::getImage()
{
    return image;
}
