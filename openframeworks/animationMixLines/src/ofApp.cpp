#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    
    
    lineA.draw();
    lineB.draw();
    
    
    if (lineA.size() > 0 && lineB.size() > 0){
        
        
        ofPolyline lineAResampled = lineA.getResampledByCount(200);
        ofPolyline lineBResampled = lineB.getResampledByCount(200);
        
        ofPolyline mix;
        
        float pct = sin(ofGetElapsedTimef()) * 0.5 + 0.5;
        
        for (int i = 0; i < min(lineAResampled.size(), lineBResampled.size()); i++){
            //pct = sin(ofGetElapsedTimef() + i*0.01) * 0.5 + 0.5;
            ofPoint mixPt = pct * lineAResampled[i] + (1-pct) * lineBResampled[i];
            mix.addVertex(mixPt);
        }
        mix.draw();
        
        
        
        
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
    if (bDrawingA == true){
        lineA.addVertex(x,y);
    } else {
        lineB.addVertex(x,y);
    }
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    if (bDrawingA == true){
        lineA.clear();
        lineA.addVertex(x,y);
    } else {
        lineB.clear();
        lineB.addVertex(x,y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    bDrawingA = !bDrawingA;
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
