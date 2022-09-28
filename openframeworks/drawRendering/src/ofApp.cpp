#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //ofSetLineWidth(10);
    line.draw();
    
    
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for (int i = 0; i < line.size(); i++){
        
        int i_m_1 = i-1;
        int i_p_1 = i+1;
        if (i_m_1 < 0) i_m_1 = 0;
        if (i_p_1 == line.size()) i_p_1 = line.size()-1;
        ofPoint a = line[i_m_1];
        ofPoint b = line[i];
        ofPoint c = line[i_p_1];
        ofPoint diff  = (c-a).getNormalized();
        diff = diff.getRotated(90, ofPoint(0, 0, 1));
        
        mesh.addVertex(b + diff*10);
        mesh.addVertex(b - diff*10);
        mesh.addColor(ofColor::white);
        mesh.addColor(ofColor::black);
        
        //ofDrawLine(b, b + diff*100);
    }
    mesh.draw();
    
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
    line.addVertex(x,y);
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    line.clear();
    line.addVertex(x,y);
    
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
