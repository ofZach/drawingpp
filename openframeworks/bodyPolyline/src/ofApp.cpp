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
    
    /// Zeno
    /// currentValue = currentValue * 0.9 + targetValue * 0.1
    pos = pos * 0.9 + (body.detections[0][BODY_LEFTWRIST]) * 0.1;
    line.addVertex(pos);
    
    /// Erase
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
    
    ofPushStyle();
    ofSetColor(0, 0, 0, 70);
    ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    ofPopStyle();
    
    ///
    /// LINE
//    ofPushStyle();
//    ofSetColor(255, 255, 255);
//    ofSetLineWidth(5);
//    line.draw();
//    ofPopStyle();
    
    
    ///
    /// SMOOTHED LINE
//    ofPushStyle();
//
//    ofPolyline smoothedLine = line.getSmoothed(10);
//
//    ofSetColor(255, 255, 255);
//    ofSetLineWidth(5);
//    smoothedLine.draw();
//    ofPopStyle();
    
    
    ///
    /// CIRCLES ALONG LINE
//    ofPushStyle();
//
//    ofSetColor(255, 255, 255, 90);
//    ofPolyline smoothedLine = line.getSmoothed(10);
//
//    for (int i = 0; i < smoothedLine.size(); i++) {
//        ofDrawCircle(smoothedLine[i].x, smoothedLine[i].y, 10);
//    }
//
//    ofPopStyle();
    
    
    ///
    /// LINE TO MESH
        ofPushStyle();
        ofSetColor(255, 255, 255);
        ofPolyline smoothedLine = line.getSmoothed(10);
    
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    
        for (int i = 0; i < smoothedLine.size(); i++) {
            mesh.addVertex(ofPoint(smoothedLine[i].x, smoothedLine[i].y));
        }
    
        mesh.draw();
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
