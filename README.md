# ofxKMeans-TSNE
A version of ofxTSNE using k-means clustering and containing examples with 3D embeddings.

## About
ofxKMeans-TSNE is a tool written with openFrameworks integrating [k-means](https://projecteuclid.org/download/pdf_1/euclid.bsmsp/1200512992 "Some Methods for classification and Analysis of Multivariate Observations") clustering with [t-SNE](https://lvdmaaten.github.io/publications/papers/JMLR_2008.pdf "Visualizing Data using t-SNE") data.

t-SNE is a dimensionality reducing algorithm that facilitates the visualization of high-dimensional data by mapping each element to a location on a two or three-dimensional plot. Although it's easy to visually distinguish one group of points from another, the groups carry no semantic meaning and cannot be directly accessed as a cluster. To address this, one might want to iterate through all the points and delineate boundaries, looking at each element and assigning it to a particular cluster. ofxKMeans-TSNE does this by adding the raw t-SNE data from ofxTSNE to a k-means clusterer from ofxLearn.

## Requirements
1) **Your own set of images.** Scrape them online or use the ones from your last vacation! The documentation for these examples use an image sequence from the film *A Scanner Darkly*, so there is no restriction on the kinds of images you can use. If you don't have an image set readily available, ofxTSNE contains a python script that will download images from an existing academic database.
2) **openFrameworks and the addons listed below.** This has been tested and is working with [openFrameworks](https://openframeworks.cc/download "openFrameworks") 0.9.8. Download the latest stable release, along with the *master* branches of the following addons:
* [ofxTSNE](https://github.com/genekogan/ofxTSNE "ofxTSNE")
* [ofxCcv](https://github.com/kylemcdonald/ofxCcv "ofxCcv")
* [ofxLearn](https://github.com/genekogan/ofxLearn "ofxLearn")
* [ofxAssignment](https://github.com/kylemcdonald/ofxAssignment "ofxAssignment")
* ofxGui (core addon for openFrameworks)

## Use
1) Clone the master branches of the above repositories into your `/openFrameworks/addons` directory.
2) Clone this repository wherever it will be most convenient.
3) Using `projectGenerator`, import the example and click **Update** to generate the project files.
4) Download the image net classifier with `./download-imagenet.sh` (can also copy and paste if the files are already downloaded from using ofxCcv).

## Examples
### 3D Unassigned Images
![3D unassigned images](https://github.com/tespin/ofxKMeans-TSNE/blob/master/documentation-images/3d-unassigned-images/3d-unassigned-images-01.png)
When using the `example-3D-unassigned-images` example, the images are put through a trained convolutional neural network and are encoded as a 4096-dimension feature vector. Then, each element is put through the t-SNE algorithm to be 'grouped' together before k-means clustering is applied. At this point, each element is formally assigned to a cluster.

`NUMIMAGES` and `NUMCLUSTERS` initializes at 512 images and 5 clusters, but these numbers are arbitrary and can be changed (although I've found that 5-6 clusters corresponds pretty well with this number of images in terms of accuracy).

### 3D Assigned Images
![3D assigned images](https://github.com/tespin/ofxKMeans-TSNE/blob/master/documentation-images/3d-assigned-images/3d-assigned-images-01.png)
The process in `example-3D-assigned-images` is similar to the unassigned example, except after being encoded and clustered together, each image is then assigned to a point in a 3D grid before being rendered.

This example is initialized to use 588 images (`NUMIMAGES`) and 6 clusters (`NUMCLUSTERS`), with grid dimensions of 12 x 7 x 7 (corresponding to `nx`, `ny`, and `nz`). Feel free to play around with these values. 
