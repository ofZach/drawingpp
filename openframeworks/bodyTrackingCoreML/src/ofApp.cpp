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
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    #ifdef _USE_LIVE_VIDEO
        cam.draw(0,0);
    #else
        vid.draw(0,0);
    #endif
    
    ofPushStyle();
    ofSetColor(255, 255, 255, 99);
    for (int i = 0; i < body.n_det; i++){
        for (int j = 0; j < BODY_N_PART; j++){
            if (body.detections[i][j].z >= 0.5) { /// z is the confidence score
                ofDrawCircle(body.detections[i][j].x, body.detections[i][j].y, 4);
            }
        }
    }
    
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
