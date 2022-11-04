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
    
    img.load("1.png");

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
    
    //
    
    /// Zeno
    /// currentValue = currentValue * 0.9 + targetValue * 0.1
    pos = pos * 0.9 + (body.detections[0][BODY_LEFTWRIST]) * 0.1;
    line.addVertex(pos);
    
    if (line.size() > 100) {
        line.getVertices().erase(line.begin());
    }
    

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
    ofSetColor(0, 0, 0, 127.5);
    ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    ofPopStyle();
    
    
    ///
    /// IMAGES ALONG THE LINE
    ofPushStyle();
    ofPolyline smoothedLine = line.getSmoothed(10);
    ofPolyline resampledLine = smoothedLine.getResampledBySpacing(1);

    for (int i = 0; i < resampledLine.size(); i++) {

        ofSetRectMode(OF_RECTMODE_CENTER);
        img.draw(resampledLine[i].x, resampledLine[i].y, 20, 20);

    }

    ofPopStyle();
    
    
    ///
    /// WITH ORIENTATION
//    ofPushStyle();
//    ofPolyline smoothedLine = line.getSmoothed(10);
//    ofPolyline resampledLine = smoothedLine.getResampledBySpacing(1);
//
//    for (int i = 0; i < resampledLine.size(); i++) {
//
//        int i_minus_1 = i - 1;
//        int i_plus_1 = i + 1;
//        if (i_minus_1 < 0) {
//            i_minus_1 = 0;
//        }
//        if (i_plus_1 == resampledLine.size()) {
//            i_plus_1 = resampledLine.size()-1;
//        }
//
//        ofPoint prev = resampledLine[i_minus_1];
//        ofPoint curr = resampledLine[i];
//        ofPoint next = resampledLine[i_plus_1];
//
//        /// calculate orientation
//        ofPoint diff = next - curr;
//        float orientation = atan2f(diff.x, diff.y) * RAD_TO_DEG;
//
//        ofPushMatrix();
//        ofTranslate(resampledLine[i].x, resampledLine[i].y);
//        ofRotateDeg(orientation, 0, 0, 1);
//        ofSetRectMode(OF_RECTMODE_CENTER);
//        img.draw(0, 0, 20, 20);
//        ofPopMatrix();
//
//    }
//
//    ofPopStyle();
    
    
    ///
    /// WITH VELOCITY
//    ofPushStyle();
//    ofPolyline smoothedLine = line.getSmoothed(10);
//
//    for (int i = 0; i < smoothedLine.size(); i++) {
//
//        int i_minus_1 = i - 1;
//        int i_plus_1 = i + 1;
//        if (i_minus_1 < 0) {
//            i_minus_1 = 0;
//        }
//        if (i_plus_1 == smoothedLine.size()) {
//            i_plus_1 = smoothedLine.size()-1;
//        }
//
//        ofPoint prev = smoothedLine[i_minus_1];
//        ofPoint curr = smoothedLine[i];
//        ofPoint next = smoothedLine[i_plus_1];
//
//        /// calculate orientation
//        ofPoint diff = next - curr;
//        float orientation = atan2f(diff.x, diff.y) * RAD_TO_DEG;
//
//        /// calculate velocty
//        float vel = (next - prev).length()*2;
//
//        ofSetRectMode(OF_RECTMODE_CENTER);
//        ofPushMatrix();
//        ofTranslate(smoothedLine[i].x, smoothedLine[i].y);
//        ofRotateDeg(orientation, 0, 0, 1);
//        ofSetRectMode(OF_RECTMODE_CENTER);
//        img.draw(0, 0, 10 + vel, 10 + vel);
//        ofPopMatrix();
//
//    }
//
//    ofPopStyle();

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
