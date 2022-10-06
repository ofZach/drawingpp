#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

    
    
    for (int z = 0; z < 10; z ++){
        
        
        
        line tempLine;
        
        
        float length = ofRandom(10, 100);
        float angle = ofRandom(0, TWO_PI);
        //ofRandom(0, TWO_PI);
        ofPoint pos = ofPoint(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()));
        
        if (lines.size() > 0){
            int whichLine = ofRandom(0, lines.size());
            float randomPct = ofRandom(0,1);
            ofPoint pos = lines[whichLine].a + (lines[whichLine].b - lines[whichLine].a)*randomPct;
            tempLine.a = pos + 0.01 * ofPoint(cos(angle), sin(angle));
            tempLine.b = pos + length * ofPoint(cos(angle), sin(angle));
        } else {
            pos = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
            tempLine.a = pos + length * ofPoint(cos(angle), sin(angle));
            tempLine.b = pos - length * ofPoint(cos(angle), sin(angle));
        }
        
        if (lines.size() == 0){
            lines.push_back(tempLine);
        } else {
            bool bIntsectAnything = false;
            for (int i = 0; i < lines.size(); i++){
                ofPoint intersect;
                if (ofLineSegmentIntersection(tempLine.a, tempLine.b, lines[i].a, lines[i].b, intersect)){
                    
                    tempLine.b = intersect;
                    //bIntsectAnything = true;
                    //break;
                }
            }
            if (bIntsectAnything == false){
                if ((tempLine.a - tempLine.b).length() > 5){
                    lines.push_back(tempLine);
                }
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
