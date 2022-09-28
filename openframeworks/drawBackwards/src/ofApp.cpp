#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    prevMouse = ofPoint(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    line.draw();
    
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

    
    ofPoint diff = ofPoint(x,y) - prevMouse;
    
    ofPoint pt = line[line.size()-1];
    
    line.addVertex( pt + -diff);
    
    ofPoint diffToMouse = pt - ofPoint(x,y);
    
    for (int i = 0; i < line.size(); i++){
        line[i] -= diffToMouse;
    }
    
    prevMouse = ofPoint(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    line.clear();
    line.addVertex(x,y);
    prevMouse = ofPoint(x,y);
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
