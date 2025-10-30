#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	num_created_gestures = 0;
	ofBackground(0,0,0);
	createNewGesture();

	// Setup GUI
	gui.setup("Dollar Gesture Recognizer");
	gui.add(btnClearLine.setup("Clear Line"));
	gui.add(btnCreateGesture.setup("Create Gesture"));
	gui.add(btnFindGesture.setup("Find Gesture"));
	gui.add(btnSaveToFile.setup("Save to File"));
	gui.add(btnLoadFromFile.setup("Load from File"));
	gui.add(lblGestureCount.setup("Gestures", "0"));
	gui.add(lblCurrentGesture.setup("Current", ""));
    gui.setDefaultWidth(300);
	// Add listeners
	btnClearLine.addListener(this, &ofApp::clearLine);
	btnCreateGesture.addListener(this, &ofApp::createGesture);
	btnFindGesture.addListener(this, &ofApp::findGesture);
	btnSaveToFile.addListener(this, &ofApp::saveToFile);
	btnLoadFromFile.addListener(this, &ofApp::loadFromFile);

	mode = 0;
	bLearningMode = true; // Start in learning mode
}

//--------------------------------------------------------------
void ofApp::update(){
	if(mode == 1 && ofGetElapsedTimeMillis() >= hide_message_on) {
		mode = 0;
		foundGesture.clear();
	}

	// Update labels
	lblGestureCount = "Gestures: " + ofToString(dollar.gestures.size());
	lblCurrentGesture = "Current: " + gesture->name;
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Draw GUI only in learning mode
	if(bLearningMode) {
		gui.draw();
	}

	// Draw current line being drawn
	if(mode == 0) {
		ofSetColor(255, 255, 0);
		ofSetLineWidth(2);
		currentLine.draw();
	}

	// Draw found gesture
	if(foundGesture.size() > 0) {
		ofSetColor(0, 255, 50);
		ofSetLineWidth(3);
		foundGesture.draw();
	}

	// Draw message
	if (mode == 1) {
		ofSetColor(255, 0, 155);
		ofDrawBitmapString(message, 10, ofGetHeight()-40);
	}

	// Draw mode indicator
	ofSetColor(200, 200, 200);
	string modeStr = bLearningMode ? "LEARNING MODE (press 't' to switch to testing)" : "TESTING MODE (press 't' to switch to learning)";
	ofDrawBitmapString(modeStr, 10, ofGetHeight()-10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 't' || key == 'T') {
		bLearningMode = !bLearningMode;
		if(!bLearningMode) {
			showMessage("Switched to TESTING MODE - draw and release to auto-match", 1500);
		} else {
			showMessage("Switched to LEARNING MODE - use GUI to create gestures", 1500);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(mode == 0) {
		currentLine.addVertex(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	// In testing mode, automatically find gesture on mouse release
	if(!bLearningMode && currentLine.size() > 10) {
		findGesture();
	}
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

//--------------------------------------------------------------
void ofApp::clearLine() {
	currentLine.clear();
}

//--------------------------------------------------------------
void ofApp::createGesture() {
	// Add all the points we've just drawn to the gesture
	gesture->reset();

	auto& points = currentLine.getVertices();
	for(int i = 0; i < points.size(); ++i) {
		gesture->addPoint(points[i].x, points[i].y);
	}

	if(gesture->points.size() <= 10) {
		message = "Please draw a line first (needs more than 10 points)";
	}
	else {
		dollar.addGesture(gesture);
		message = "Added gesture to recognizer";
		currentLine.clear();
		createNewGesture();
	}
	showMessage(message, 800);
	currentLine.clear();
}

//--------------------------------------------------------------
void ofApp::findGesture() {
	// Find the gesture which matches the current line
	ofxGesture* tmp = new ofxGesture();

	auto& points = currentLine.getVertices();
	for(int i = 0; i < points.size(); ++i) {
		tmp->addPoint(points[i].x, points[i].y);
	}
	currentLine.clear();

	double score = 0.0;
	ofxGesture* match = dollar.match(tmp, &score);
	string result = "Matching score: " + ofToString(score, 3);

	if(match != NULL) {
		result += ", which matches with gesture: " + match->name;
		foundGesture.clear();
		float dx = ofGetWidth()/2;
		float dy = ofGetHeight()/2;
		for(int i = 0; i < match->resampled_points.size(); ++i) {
			foundGesture.addVertex(dx + match->resampled_points[i].x,
			                       dy + match->resampled_points[i].y);
		}
	}
	showMessage(result, 1500);
	delete tmp;
}

//--------------------------------------------------------------
void ofApp::saveToFile() {
	dollar.save(ofToDataPath("gestures.txt", true));
	showMessage("Saved to gestures.txt!");
}

//--------------------------------------------------------------
void ofApp::loadFromFile() {
	dollar.load(ofToDataPath("gestures.txt", true));
	showMessage("Loaded! Note that saved gestures are rotated to the optimal position!", 4000);
}

//--------------------------------------------------------------
void ofApp::showMessage(string sMessage, int nDelay) {
	message = sMessage;
	mode = 1;
	hide_message_on = ofGetElapsedTimeMillis() + nDelay;
}

//--------------------------------------------------------------
void ofApp::createNewGesture() {
	++num_created_gestures;
	gesture = new ofxGesture();
	gesture->setName("Gesture#" + ofToString(num_created_gestures));
}
