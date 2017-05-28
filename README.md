# ofxKMeans-TSNE
A version of ofxTSNE using k-means clustering and containing examples with 3D embeddings.

## About
ofxKMeans-TSNE is a tool written with openFrameworks integrating [k-means](https://projecteuclid.org/download/pdf_1/euclid.bsmsp/1200512992 "Some Methods for classification and Analysis of Multivariate Observations") clustering with [t-SNE](https://lvdmaaten.github.io/publications/papers/JMLR_2008.pdf "Visualizing Data using t-SNE") data.

t-SNE is a dimensionality reducing algorithm that facilitates the visualization of high-dimensional data by mapping each element to a location on a two or three-dimensional plot. Although visually, it's easy to distinguish one group of points from another, the groups carry no semantic meaning. One might want to iterate through all the points and delineate boundaries, looking at each element and assigning it to a particular cluster. ofxKMeans-TSNE does this by adding the raw t-SNE data from ofxTSNE to a k-means clusterer from ofxLearn.

## Requirements
1) **Your own set of images.** Scrape them online or turn to your last vacation! If you don't have an image set readily available, ofxTSNE contains a python script that will download images from an existing database.
2) **openFrameworks and respective addons.** This has been tested and is working with [openFrameworks](https://openframeworks.cc/download "openFrameworks") 0.9.8. Download the latest stable release, along with the *master* branches of the following addons:
* [ofxTSNE](https://github.com/genekogan/ofxTSNE "ofxTSNE")
* [ofxCcv](https://github.com/kylemcdonald/ofxCcv "ofxCcv")
* [ofxLearn](https://github.com/genekogan/ofxLearn "ofxLearn")
* [ofxAssignment](https://github.com/kylemcdonald/ofxAssignment "ofxAssignment")
* ofxGui (core addon for openFrameworks)

## Use
1) Clone the master branches of the above repositories into your `/openFrameworks/addons` directory.
2) Clone this repository where it is most convenient for you.
3) Using `projectGenerator`, import this repository and click **Update** to generate the project files.
4) Download the image net classifier with `./download-imagenet.sh` (can also copy and paste if the files are already downloaded from using ofxCcv).

## Examples
### 3D Assigned Images
![3D assigned images](https://github.com/tespin/ofxKMeans-TSNE/blob/master/documentation-images/3d-assigned-images/3d-assigned-images-01.png)
With `example-3D-assigned-images`, images are put through a trained convolutional neural network, becoming encoded as a 4096-dimension feature vector. After being encoded, the t-SNE algorithm 'groups' them together before applying k-means clustering, at which point each element is formally assigned to a cluster. Each image is then assigned to a point in a 3D grid. 

The example is initialized to use 588 images (`NUMIMAGES`) and 6 clusters (`NUMCLUSTERS`), with grid dimensions of 12 x 7 x 7 (corresponding to `nx`, `ny`, and `nz`). Feel free to play around with these values.

## To Do
* Include examples for unassigned 3D images, and possibly examples using 2D embeddings.
* Finish documentation for 3D assigned images.
* Write out encodings to a data file that can be read from to reduce iteration time.
* Refine data structures, memory management, const-ify some methods.
* Constrain random colors so that they are not equal / close to each other or the background color.
* Fix gui so that it is visible when there are 10+ clusters. 
