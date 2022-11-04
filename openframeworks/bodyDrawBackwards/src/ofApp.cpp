#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    #ifdef _USE_LIVE_VIDEO
        cam.setDeviceID(1);
        cam.initGrabber(640,480);
    #else
        vid.load("Lenataa720.mov");
        vid.setVolume(0);
        vid.play();
        vid.setLoopState(OF_LOOP_NORMAL);
    #endif
    
    gui.setup();
    gui.setPosition(640+50, 50);
    
    prevPos = body.detections[0][BODY_LEFTWRIST];
    line.addVertex(prevPos);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    #ifdef _USE_LIVE_VIDEO
        cam.update();
        if (cam.isFrameNew()){
            ofPixels & pixels = cam.getPixels();
            body.detect(pixels);
        }
    #else
        vid.update();
        if (vid.isFrameNew()){
            ofPixels & pixels = vid.getPixels();
            body.detect(pixels);
        }
    #endif
    
    if (line.size() > 150) {
        line.getVertices().erase(line.begin());
    }
    
    nextPos = body.detections[0][BODY_LEFTWRIST];
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    #ifdef _USE_LIVE_VIDEO
        cam.draw(0,0);
    #else
        vid.draw(0,0);
    #endif
    
    ///
    ofPushStyle();
    ofSetColor(0, 0, 0, 70);
    ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    ofPopStyle();

    ///
    ofPoint diff = nextPos - prevPos;
    ofPoint pt = line[line.size()-1];
    line.addVertex(pt + -diff);
    
    ofPoint diffToBody = pt - nextPos;
    for (int i = 0; i < line.size(); i++){
        line[i] -= diffToBody;
    }
    
    prevPos = nextPos;
    
    ofPolyline smoothedLine = line.getSmoothed(15);
    
    ofPushStyle();
    ofSetColor (255, 255, 255);
    ofSetLineWidth(2);
    smoothedLine.draw();
    ofPopStyle();


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
