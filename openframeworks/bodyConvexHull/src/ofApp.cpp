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
    
    points.clear();
    hull.clear();
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    #ifdef _USE_LIVE_VIDEO
        cam.draw(0,0);
    #else
        vid.draw(0,0);
    #endif
    
    ofPushStyle();
    ofSetColor(0, 0, 0, 80);
    ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    ofPopStyle();
    
    
    ///
    /// CONVEX HULL
    for (int i = 0; i <= 0; i++) { /// we are only detecting 1 body, other wise this would be i < MAX_DET
        for (int j = 0; j < BODY_N_PART; j++) {

//            int j_minus_1 = j-1;
//            int j_plus_1 = j+1;
//
//            if (j_minus_1 < 0) {
//                j_minus_1 = 0;
//            }
//
//            if (j_plus_1 == BODY_N_PART) {
//                j_plus_1 = BODY_N_PART - 1;
//            }
//
//            ofPoint prev = body.detections[i][j_minus_1];
//            ofPoint curr = body.detections[i][j];
//            ofPoint next = body.detections[i][j_plus_1];

//            ofPushStyle();
//            ofDrawEllipse(body.detections[i][j].x, body.detections[i][j].y, 5, 5);
//            ofPopStyle();
            
            if (body.detections[i][j].z > 0.30) {
                points.push_back(ofPoint(body.detections[i][j].x, body.detections[i][j].y));
            }
        }
    }
    
    hull = convexHull.getConvexHull(points);
    
    /// Draw hull
    ofPushStyle();
    ofSetColor(255, 255, 255);
    ofNoFill();
    ofSetLineWidth(3);
    ofBeginShape();
    for (int i = 0; i < hull.size(); i++) {
        ofVertex(hull[i]);
    }
    ofEndShape();
    ofPopStyle();
    
//    ofPushStyle();
//    ofSetColor(255, 255, 255);
//    ofSetLineWidth(3);
//    ofPolyline hullLine;
//    for (int i = 0; i < hull.size(); i++) {
//        hullLine.addVertex(hull[i]);
//    }
//    ofPolyline resampled = hullLine.getResampledByCount(500);
//    ofPolyline smoothed = resampled.getSmoothed(7);
//    smoothed.draw();
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
