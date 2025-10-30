#pragma once

#include "ofMain.h"
#include "ofxOneDollar.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void createNewGesture();
		void showMessage(string sMessage, int nDelay = 2000);

		// GUI callbacks
		void clearLine();
		void createGesture();
		void findGesture();
		void saveToFile();
		void loadFromFile();

		// GUI
		ofxPanel gui;
		ofxButton btnClearLine;
		ofxButton btnCreateGesture;
		ofxButton btnFindGesture;
		ofxButton btnSaveToFile;
		ofxButton btnLoadFromFile;
		ofxLabel lblGestureCount;
		ofxLabel lblCurrentGesture;

		// Gesture recognition
		ofPolyline currentLine;
		ofPolyline foundGesture;
		ofxOneDollar dollar;
		ofxGesture* gesture;
		int num_created_gestures;

		// State
		int mode; // 0 = drawing, 1 = showing message
		string message;
		int hide_message_on;

	// Mode toggle
	bool bLearningMode; // true = learning mode (GUI visible), false = testing mode (auto-match)
};
