# ofxKMeans-TSNE
A version of ofxTSNE using k-means clustering and containing examples with 3D embeddings.

## About
ofxKMeans-TSNE is a tool written with openFrameworks integrating [k-means](https://projecteuclid.org/download/pdf_1/euclid.bsmsp/1200512992 "Some Methods for classification and Analysis of Multivariate Observations") clustering with [t-SNE](https://lvdmaaten.github.io/publications/papers/JMLR_2008.pdf "Visualizing Data using t-SNE") data.

t-SNE is a dimensionality reducing algorithm that facilitates the visualization of high-dimensional data by mapping each element to a location on a two or three-dimensional plot. Visually, it becomes easy to distinguish one group of points from another. If images are fed to the algorithm, one can parse out groups with shared colors, shapes, etc. Unfortunately, the groups in and of themselves carry no semantic meaning. One might want to iterate through all the points and delineate boundaries, looking at each element and assigning it to a particular cluster. ofxKMeans-TSNE does this by adding the raw t-SNE data from ofxTSNE to a k-means clusterer from ofxLearn.

## Requirements
This uses the most recent openFrameworks release, along with the *master* branches of the following addons:
* [ofxTSNE](https://github.com/genekogan/ofxTSNE "ofxTSNE")
* [ofxCcv](https://github.com/kylemcdonald/ofxCcv "ofxCcv")
* [ofxLearn](https://github.com/genekogan/ofxLearn "ofxLearn")
* [ofxAssignment](https://github.com/kylemcdonald/ofxAssignment "ofxAssignment")
* ofxGui (core addon for openFrameworks)

## Use
1) Clone the master branches of the above repositories into your '/openFrameworks/addons' directory.
2) Clone this repository where it is most convenient for you.
3) Using 'projectGenerator', import this repository and click **Update** to generate the project files.
4) Download the image net classifier with './download-imagenet.sh' (can also copy and paste if the files are already downloaded from using ofxCcv).

## Examples
### 3D Assigned Images
![3D assigned images](https://github.com/tespin/ofxKMeans-TSNE/blob/master/documentation-images/3d-assigned-images/3d-assigned-images-01.png)

## To Do
* Include examples for unassigned 3D images, and possibly examples using 2D embeddings.
* Finish documentation for 3D assigned images.
* Add a 'Use' section' in readme.
* Write out encodings to a data file that can be read from to reduce iteration time.
* Refine data structures, memory management, const-ify some methods.
* Constrain random colors so that they are not equal / close to each other or the background color.
* Fix gui so that it is visible when there are 10+ clusters. 
