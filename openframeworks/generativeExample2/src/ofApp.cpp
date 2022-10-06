#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

    
    
    for (int z = 0; z < 100; z ++){
        line tempLine;
        
        float length = 100;
        float angle = ofRandom(-1,1);
        //ofRandom(0, TWO_PI);
        ofPoint pos = ofPoint(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()));
        
        tempLine.a = pos + length * ofPoint(cos(angle), sin(angle));
        tempLine.b = pos - length * ofPoint(cos(angle), sin(angle));
        
        
        if (lines.size() == 0){
            lines.push_back(tempLine);
        } else {
            bool bIntsectAnything = false;
            for (int i = 0; i < lines.size(); i++){
                ofPoint intersect;
                if (ofLineSegmentIntersection(tempLine.a, tempLine.b, lines[i].a, lines[i].b, intersect)){
                    bIntsectAnything = true;
                    break;
                }
            }
            if (bIntsectAnything == false){
                lines.push_back(tempLine);
            }
        }
    }
   
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    for (int i = 0; i < lines.size(); i++){
        ofDrawLine(lines[i].a, lines[i].b);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    lines.clear();
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
