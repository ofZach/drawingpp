#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    bMousePressed = false;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    
    if (bMousePressed == true){
        line.addVertex(mouseX, mouseY);
    }
    
    line.draw();
    
    for (int i = 0; i < line.size(); i++){
        line[i] -= ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    }
    
    ofMatrix4x4 mat;
    mat.makeIdentityMatrix();
    mat.rotate(1, 0, 1, 0);
    
    for (int i = 0; i < line.size(); i++){
        ofPoint pt = line[i];
        pt = mat * pt;
        line[i] = pt;
    }
    
    
    for (int i = 0; i < line.size(); i++){
        line[i] += ofPoint(ofGetWidth()/2, ofGetHeight()/2);
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

    //line.addVertex(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    line.clear();
    line.addVertex(x,y);
    
    bMousePressed = true;
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    bMousePressed = false;
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
