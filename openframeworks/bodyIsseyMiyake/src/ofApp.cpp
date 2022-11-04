#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    #ifdef _USE_LIVE_VIDEO
        cam.setDeviceID(1);
        cam.initGrabber(640,480);
    #else
        vid.load("test1.mov");
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
    ofSetColor(0, 0, 0, 201);
    ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    ofPopStyle();
    
    
    ///
    /// CONNECT ALL THE BODY POINTS
    for (int i = 0; i <= 0; i++) { /// we are only detecting 1 body, other wise this would be i < MAX_DET
        for (int j = 0; j < BODY_N_PART; j++) {

            int j_minus_1 = j-1;
            int j_plus_1 = j+1;

            if (j_minus_1 < 0) {
                j_minus_1 = 0;
            }

            if (j_plus_1 == BODY_N_PART) {
                j_plus_1 = BODY_N_PART - 1;
            }

            //ofDrawEllipse(body.detections[i][j].x, body.detections[i][j].y, 5, 5);

            /// check the confidence and exclude head points (they are a bit jumpy even with confidence check)
            if (body.detections[i][j].z > 0.50
                && (j != BODY_RIGHTEYE
                    && j != BODY_LEFTEYE
                    && j != BODY_LEFTEAR
                    && j != BODY_RIGHTEAR
                    && j != BODY_NOSE) ) {
                ofPoint prev = body.detections[i][j_minus_1];
                ofPoint curr = body.detections[i][j];
                ofPoint next = body.detections[i][j_plus_1];

                ///
                /// CONNECT ALL POINTS WITH LINES
                ofPushStyle();
                ofSetColor(255, 255, 255);
                ofNoFill();
                ofSetLineWidth(2);
                ofBeginShape();
                ofVertex(prev.x, prev.y);
                ofVertex(curr.x, curr.y);
                ofVertex(next.x, next.y);
                ofEndShape();
                //ofDrawLine(curr.x, curr.y, next.x, next.y);
                ofPopStyle();
                
                
                ///
                /// CONNECT TO CENTER
//                ofPushStyle();
//                ofSetColor(255, 255, 255);
//                ofNoFill();
//                ofSetLineWidth(2);
//                ofDrawLine(curr.x, curr.y, body.detections[0][BODY_ROOT].x, body.detections[0][BODY_ROOT].y);
//                ofPopStyle();


                ///
                /// TRIADIC BALLET
//                ofPushStyle();
//                ofSetColor(255, 255, 255);
//                ofNoFill();
//                ofSetLineWidth(2);
//                ofDrawCircle(curr.x, curr.y, 40);
//                ofPopStyle();

                
                ///
                /// SLAT DANCER INSPIRED
//                /// calculate normals
//                ofPoint diff = next - prev;
//                ofPoint normal = diff.getNormalized();
//                ofPoint topEnd =  curr + normal.getRotated(90, ofPoint(0,0,1)) + 50;
//                ofPoint bottomEnd = curr + normal.getRotated(-90, ofPoint(0,0,1)) - 50;
//
//                /// calculate orientation
//                ofPoint diff2 = next - curr;
//                float orientation = atan2f(diff2.x, diff2.y) * RAD_TO_DEG;
//
//                ofPushStyle();
//                ofSetColor(255, 255, 255);
//                ofSetLineWidth(2);
//                ofDrawLine(topEnd.x, topEnd.y, bottomEnd.x, bottomEnd.y);
//                ofPopStyle();

            }
        }
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
