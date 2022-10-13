#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

   
    ofNoFill();
    ofSetColor(255);
    ofBeginShape();
    for (int i = 0; i < timePts.size(); i++){
        ofVertex(timePts[i].x, timePts[i].y);
    }
    ofEndShape();
    
    if (timePts.size() > 0 &&  bDrawing == false){
        
        float duration = timePts[timePts.size()-1].t;
        ofFill();
        
        // this is for "10" playbacks
       // for (int j = 0; j < 10; j++){
        //float timeForPlayback = fmod(ofGetElapsedTimef() + (j/10.0)*duration, duration);
        
        float timeForPlayback = fmod(ofGetElapsedTimef(), duration);
            for (int i = 0; i < timePts.size()-1; i++){
                if (timeForPlayback >= timePts[i].t &&
                    timeForPlayback < timePts[i+1].t){
                    
                    float pct = ofMap(timeForPlayback, timePts[i].t,timePts[i+1].t,0, 1 );
                    ofPoint mix = (1-pct)* ofPoint(timePts[i].x, timePts[i].y) + pct*ofPoint(timePts[i+1].x, timePts[i+1].y);
                    ofSetColor(255,0,0);
                    ofDrawCircle(mix, 10);
        
                }
                        
            }
        // for 10....
        //}
        
        
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

    timePt pt;
    pt.t = ofGetElapsedTimef() - startTime;
    pt.x = x;
    pt.y = y;
    timePts.push_back(pt);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    bDrawing = true;
    
    timePts.clear();
    startTime = ofGetElapsedTimef();
    timePt pt;
    pt.t = 0;
    pt.x = x;
    pt.y = y;
    timePts.push_back(pt);
    
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    bDrawing = false;
    
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
