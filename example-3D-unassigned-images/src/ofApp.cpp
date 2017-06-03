#include "ofApp.h"

const string allowed_ext[] = {"jpg", "png", "gif", "jpeg"};

void ofApp::scan_dir_imgs(ofDirectory dir)
{
    ofDirectory new_dir;
    
    // size is equal to # of files in directory
    int size = dir.listDir();
    
    // for every file
    for (int i = 0; i < size; i++)
    {
        if (dir.getFile(i).isDirectory())
        {
            new_dir = ofDirectory(dir.getFile(i).getAbsolutePath());
            new_dir.listDir();
            new_dir.sort();
            scan_dir_imgs(new_dir);
        }
        else if (std::find(std::begin(allowed_ext), std::end(allowed_ext), dir.getFile(i).getExtension()) != std::end(allowed_ext))
        {
            imageFiles.push_back(dir.getFile(i));
        }
    }
}

void ofApp::setup()
{
    ofSetVerticalSync(true);
    
    string imageDir = "/Users/tespin/Documents/openFrameworks/apps/myApps/00_BatchFeatureEncoder/bin/data/image-set-a-scanner-darkly-2";
    
    if (imageDir == "")
    {
        ofLog(OF_LOG_ERROR, "You haven't specified a directory! Exiting ...");
        ofExit();
        return;
    }
    
    w = 256;
    h = 256;
    d = 256;
    
    perplexity = 50;
    theta = 0.4;
    
    scale = 2;
    
    // get images from directory
    ofLog() << "Gathering images...";
    ofDirectory dir = ofDirectory(imageDir);
    scan_dir_imgs(dir);
    ofLog() << imageFiles.size() << " images";
    
    // check that there are enough images in directory
    if (imageFiles.size() < NUMIMAGES)
    {
        ofLog(OF_LOG_ERROR, "There are less images in the directory than specified (Number of images="+ofToString((NUMIMAGES))+"). Exiting to save you trouble...");
        ofExit(); // not enough images!
        return;
    }
    
    // populate element vector
    for (int i = 0; i < NUMIMAGES; i++)
    {
        Element element;
        elementVector.push_back(element);
    }
    
    // load images
    for (int i = 0; i < NUMIMAGES; i++)
    {
        if (i % 20 == 0) ofLog() << " - loading image " << i << " / " << NUMIMAGES << " (" << dir.size() << " in dir)";
        images.push_back(ofImage());
        images.back().load(imageFiles[i].getAbsolutePath());
        
        elementVector[i].setImage(images[i], w, h);
    }
    
    // setup ccv
    ccv.setup("image-net-2012.sqlite3");
    
    // encode images with ccv
    ofLog() << "Encoding images...";
    for (int i = 0; i < images.size(); i++)
    {
        if (i % 20 == 0) ofLog() << " - encoding image " << i << " / " << images.size();
        std::vector<float> encoding = ccv.encode(images[i], ccv.numLayers()-1);
        encodings.push_back(encoding);
    }
    
    // run t-SNE and load image points to imagePoints
    ofLog() << "Run t-SNE on images...";
    tsneVecs = tsne.run(encodings, 3, perplexity, theta, true);
    
    // add raw t-SNE data to k-means clusterer
    for (int i = 0; i < NUMIMAGES; i++)
    {
        instances[i].push_back(tsneVecs[i][0]);
        instances[i].push_back(tsneVecs[i][1]);
        instances[i].push_back(tsneVecs[i][2]);
        clusterer.addSample(instances[i]);
    }
    
    // set up clustering and train
    clusterer.setNumClusters(NUMCLUSTERS);
    clusterer.train();
    clusters = clusterer.getClusters();
    
    // assign each instance to a cluster
    for (int i = 0; i < clusters.size(); i++)
    {
        elementVector[i].assignClusterIndex(clusters[i]);
    }
    
    for (int i = 0; i < NUMCLUSTERS; i++)
    {
        colors[i] = ofColor(ofRandom(255), ofRandom(255), ofRandom(255)) ;
    }
    
    // populate vector of verts
    for (int i = 0; i < tsneVecs.size(); i++)
    {
        float x = ofMap(tsneVecs[i][0], 0, 1, 0, scale * ofGetWidth());
        float y = ofMap(tsneVecs[i][1], 0, 1, 0, scale * ofGetHeight());
        float z = ofMap(tsneVecs[i][2], 0, 1, 0, scale * 1000);
        
        ofVec3f pos(x, y, z);
        posVector.push_back(pos);
    }
    
    calcCamPos();
    
    // assign each element its pos
    for (int i = 0; i < elementVector.size(); i++)
    {
        elementVector[i].setVertex(posVector[i]);
    }
    
    cam.setAutoDistance(false);
    cam.setNearClip(0.1);
    cam.setFarClip(50000);
    cam.setPosition(camPos);
    
    sphere.setRadius(50);
    
    initGui();
    setupGui();
}

void ofApp::update()
{
    // reset camera to nondefault position -- better to implement virtual method in ofCamera
    ofVec3f newCamPos = cam.getPosition();
    ofVec3f defaultPos = ofVec3f(0, 0, cam.getDistance());
    if (newCamPos == defaultPos)
    {
        cam.setPosition(camPos);
    }
}

void ofApp::draw()
{
    ofBackground(255);
    cam.begin();
    ofEnableDepthTest();
    
    ofSetColor(0);
    
    for (int i = 0; i < elementVector.size(); i++)
    {
        int specifiedCluster = elementVector[i].getClusterIndex();
        
        if (clustersGui[specifiedCluster].drawImages)
        {
            ofSetColor(255, 255, 255);
            elementVector[i].getImage().draw(posVector[i], elementVector[i].getImage().getWidth(), elementVector[i].getImage().getWidth());
        }
        
        if (clustersGui[specifiedCluster].drawPointCloud)
        {
            ofSetColor(colors[clusters[i]]);
            sphere.setPosition(posVector[i].x + (elementVector[i].getImage().getWidth() / 2), posVector[i].y + (elementVector[i].getImage().getHeight() / 2), posVector[i].z);
            sphere.draw();
        }
    }
    
    ofDisableDepthTest();
    cam.end();
    drawGui();
}

void ofApp::initGui()
{
    // for every cluster, create a clustergui and push it back to vector of clusterguis
    for (int i = 0; i < NUMCLUSTERS; i++)
    {
        ClusterGui clusterGui;
        clustersGui.push_back(clusterGui);
    }
}

void ofApp::setupGui()
{
    // set up every gui
    int columnHeight = 10;
    
    for (int i = 0; i < NUMCLUSTERS; i++)
    {
        clustersGui[i].gui.setup();
        clustersGui[i].gui.setName("Cluster: " + ofToString(i+1));
        clustersGui[i].gui.add(clustersGui[i].drawImages.set("Draw Images", true));
        clustersGui[i].gui.add(clustersGui[i].drawPointCloud.set("Draw Point Cloud",true));
    }
    
    if (NUMCLUSTERS > columnHeight)
    {
        int columnHeight = 10;
        div_t columns = std::div (NUMCLUSTERS, columnHeight);
        
        if (columns.quot > 0 && columns.rem > 0)
        {
            int column = 0;
            for (int i = 0; i < NUMCLUSTERS; i++)
            {
                if (i >= columnHeight * (column+1)) column++;
                int threshold = (column < (columns.quot)) ? columnHeight : (NUMCLUSTERS - (column*columnHeight));
                for (int j = 0; j < threshold; j++)
                {
                    clustersGui[i].gui.setPosition(clustersGui[0].gui.getWidth() * column, clustersGui[0].gui.getHeight() * j);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < NUMCLUSTERS; i++)
        {
            clustersGui[i].gui.setPosition(0, clustersGui[i].gui.getHeight() * (i*3));
        }
    }
    
    
}

void ofApp::drawGui()
{
    // draw each gui
    for (int i = 0; i < NUMCLUSTERS; i++) clustersGui[i].gui.draw();
}

void ofApp::calcCamPos()
{
    float maxWidth = posVector[0].x;
    float minWidth = posVector[0].x;
    float maxHeight = posVector[0].y;
    float minHeight = posVector[0].y;
    float maxDepth = posVector[0].z;
    float minDepth = posVector[0].z;
    
    for (int i = 0; i < posVector.size(); i++)
    {
        if (posVector[i].x > maxWidth) maxWidth = posVector[i].x;
        if (posVector[i].x < minWidth) minWidth = posVector[i].x;
        if (posVector[i].y > maxHeight) maxHeight = posVector[i].y;
        if (posVector[i].y < minHeight) minHeight = posVector[i].y;
        if (posVector[i].z > maxDepth) maxDepth = posVector[i].z;
        if (posVector[i].z < minDepth) minDepth = posVector[i].z;
        
        camPos.x = (minWidth + maxWidth) / 2;
        camPos.y = (minHeight + maxHeight) / 2;
        camPos.z = maxDepth + 1500;
        
    }
}
