#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0,0,0);
    
    ofSetColor(255,255,255);
    line.draw();
    
    if (bCalculatedCircle == true){
        ofSetCircleResolution(100);
        
        ofNoFill();
        ofSetColor(255,0,0, 130);
        ofDrawCircle(center, 3);
        ofSetColor(0,255,0, 130);
        ofDrawCircle(center, radius);
        ofDrawBitmapStringHighlight("circularity " + ofToString(circularity), center.x + radius*0.5, center.y);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    line.addVertex(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    bCalculatedCircle = false;
    
    line.clear();
    line.addVertex(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    // let's calculate things here!
    if (line.size() > 1){
        
        // first, find the avg position (centroid)
        // then calculate the avg distance (radius)
        // then look at the standard deviation of the distances to the radius to get how circular this is.
        // this is kind of primative, I'm sure there's a better way to meeasure circlarity
        // but this is easy to compute...
        
        // I need to do this, since if I draw slower or faster in some places,
        // that messed up the centroid:
        ofPolyline resampled = line.getResampledBySpacing(1); // 5 pixels apart
        ofPoint avgPosition = ofPoint(0,0);
        for (int i = 0; i < resampled.size(); i++){
            avgPosition += resampled[i];
        }
        avgPosition /= (float)resampled.size();
        center = avgPosition;
       
        // this also works!
        // center = line.getCentroid2D();
        
        vector < float > distances;
        float totalDistance = 0;
        for (int i = 0; i < line.size(); i++){
            float dist = ofDist(line[i].x, line[i].y, center.x, center.y);
            totalDistance += dist;
            distances.push_back(dist);
        }
        radius = totalDistance / (float)line.size();
        
        // this part I got from claude!  it's just for calc stddev:
        float variance = 0;
        for (int i = 0; i < distances.size(); i++){
            variance += pow(distances[i] - radius, 2);
        }
        variance /= distances.size();
        float stdDev = sqrt(variance);
                
        // Convert to percentage (0-100)
        // Perfect circle has stdDev = 0, normalize by radius
        circularity = max(0.0f, 100.0f * (1.0f - (stdDev / radius)));
        
        
        bCalculatedCircle = true;
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
