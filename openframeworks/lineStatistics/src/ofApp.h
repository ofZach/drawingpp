#pragma once

#include "ofMain.h"

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

        void computeAndPrintStatistics();

        ofPolyline line;

        // Statistics to display
        bool hasStats;
        float totalLength;
        float directDistance;
        float straightness;
        float totalAngleChange;
        float avgAngleChange;
        float maxAngleChange;
        float avgSegmentLength;
        float segmentLengthVariation;
        float avgDeviation;
        float bboxWidth;
        float bboxHeight;
        float bboxArea;
        float bboxAngle;

        // Bounding box corners for drawing
        vector<ofPoint> bboxCorners;
       
    
        
};
