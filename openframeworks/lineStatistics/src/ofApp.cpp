#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    hasStats = false;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0,0,0);

    ofSetColor(255,255,255);
    line.draw();

    // Draw oriented bounding box if available
    if (hasStats && bboxCorners.size() == 4) {
        ofSetColor(255, 100, 100);  // Red color for the box
        ofNoFill();
        ofSetLineWidth(2);

        // Draw the 4 sides of the bounding box
        ofDrawLine(bboxCorners[0], bboxCorners[1]);
        ofDrawLine(bboxCorners[1], bboxCorners[2]);
        ofDrawLine(bboxCorners[2], bboxCorners[3]);
        ofDrawLine(bboxCorners[3], bboxCorners[0]);

        ofSetLineWidth(1);
    }

    // Draw statistics if available
    if (hasStats) {
        ofSetColor(100, 255, 100);

        int x = 20;
        int y = 30;
        int lineHeight = 18;

        ofDrawBitmapString("========== LINE STATISTICS ==========", x, y);
        y += lineHeight * 1.5;

        ofDrawBitmapString("BASIC MEASUREMENTS", x, y);
        y += lineHeight;
        ofDrawBitmapString("Total Length: " + ofToString(totalLength, 1) + " px", x, y);
        y += lineHeight;
        ofDrawBitmapString("Direct Distance: " + ofToString(directDistance, 1) + " px", x, y);
        y += lineHeight;
        ofDrawBitmapString("Straightness: " + ofToString(straightness, 3) + " (1.0 = straight)", x, y);
        y += lineHeight * 1.5;

        if (line.size() > 2) {
            ofDrawBitmapString("ANGLE & DIRECTION", x, y);
            y += lineHeight;
            ofDrawBitmapString("Total Angle Change: " + ofToString(totalAngleChange, 1) + " deg", x, y);
            y += lineHeight;
            ofDrawBitmapString("Average Turn: " + ofToString(avgAngleChange, 1) + " deg", x, y);
            y += lineHeight;
            ofDrawBitmapString("Sharpest Turn: " + ofToString(maxAngleChange, 1) + " deg", x, y);
            y += lineHeight * 1.5;
        }

        ofDrawBitmapString("CONSISTENCY", x, y);
        y += lineHeight;
        ofDrawBitmapString("Avg Segment Length: " + ofToString(avgSegmentLength, 1) + " px", x, y);
        y += lineHeight;
        ofDrawBitmapString("Segment Variation: " + ofToString(segmentLengthVariation, 1) + " px", x, y);
        y += lineHeight;
        ofDrawBitmapString("Avg Distance from Line: " + ofToString(avgDeviation, 1) + " px", x, y);
        y += lineHeight * 1.5;

        ofDrawBitmapString("ORIENTED BOUNDING BOX", x, y);
        y += lineHeight;
        ofDrawBitmapString("Width: " + ofToString(bboxWidth, 1) + " px", x, y);
        y += lineHeight;
        ofDrawBitmapString("Height: " + ofToString(bboxHeight, 1) + " px", x, y);
        y += lineHeight;
        ofDrawBitmapString("Area: " + ofToString(bboxArea, 0) + " px^2", x, y);
        y += lineHeight;
        ofDrawBitmapString("Rotation: " + ofToString(bboxAngle, 1) + " deg", x, y);
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
    line.addVertex(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

     line.clear();
     line.addVertex(x,y);
     hasStats = false;
}

//--------------------------------------------------------------
void ofApp::computeAndPrintStatistics() {

    if (line.size() < 2) {
        cout << "Line too short to compute statistics" << endl;
        hasStats = false;
        return;
    }

    hasStats = true;

    cout << "\n========== LINE STATISTICS ==========" << endl;

    // ---- BASIC MEASUREMENTS ----

    // Total length: sum of all segment lengths
    totalLength = line.getPerimeter();

    // Direct distance: straight line from start to end
    ofPoint start = line[0];
    ofPoint end = line[line.size()-1];
    directDistance = start.distance(end);

    // Straightness: 1.0 = perfectly straight, closer to 0 = more wandering
    straightness = (totalLength > 0) ? directDistance / totalLength : 0;

    cout << "Total Length: " << totalLength << " pixels" << endl;
    cout << "Direct Distance: " << directDistance << " pixels" << endl;
    cout << "Straightness: " << straightness << " (1.0 = straight)" << endl;


    // ---- ANGLE & DIRECTION STATISTICS ----

    if (line.size() > 2) {
        float totalAngleChangeRad = 0;
        float maxAngleChangeRad = 0;
        int numAngles = 0;

        // Look at each trio of points to measure angle changes
        for (int i = 0; i < line.size() - 2; i++) {
            ofPoint p1 = line[i];
            ofPoint p2 = line[i+1];
            ofPoint p3 = line[i+2];

            // Get direction vectors
            ofPoint v1 = p2 - p1;
            ofPoint v2 = p3 - p2;

            // Calculate angle between vectors
            float angle1 = atan2(v1.y, v1.x);
            float angle2 = atan2(v2.y, v2.x);
            float angleDiff = angle2 - angle1;

            // Normalize to -PI to PI range
            while (angleDiff > PI) angleDiff -= TWO_PI;
            while (angleDiff < -PI) angleDiff += TWO_PI;

            float absAngle = abs(angleDiff);
            totalAngleChangeRad += absAngle;
            maxAngleChangeRad = max(maxAngleChangeRad, absAngle);
            numAngles++;
        }

        float avgAngleChangeRad = totalAngleChangeRad / numAngles;

        // Store in member variables (in degrees for display)
        totalAngleChange = ofRadToDeg(totalAngleChangeRad);
        avgAngleChange = ofRadToDeg(avgAngleChangeRad);
        maxAngleChange = ofRadToDeg(maxAngleChangeRad);

        cout << "\nTotal Angle Change: " << totalAngleChange << " degrees" << endl;
        cout << "Average Turn: " << avgAngleChange << " degrees" << endl;
        cout << "Sharpest Turn: " << maxAngleChange << " degrees" << endl;
    }


    // ---- CONSISTENCY (Segment Length Variation) ----

    vector<float> segmentLengths;
    float totalSegmentLength = 0;

    for (int i = 0; i < line.size() - 1; i++) {
        ofPoint p1 = line[i];
        ofPoint p2 = line[i+1];
        float dist = p1.distance(p2);
        segmentLengths.push_back(dist);
        totalSegmentLength += dist;
    }

    avgSegmentLength = totalSegmentLength / segmentLengths.size();

    // Calculate standard deviation of segment lengths
    float variance = 0;
    for (float len : segmentLengths) {
        float diff = len - avgSegmentLength;
        variance += diff * diff;
    }
    variance /= segmentLengths.size();
    segmentLengthVariation = sqrt(variance);

    cout << "\nAverage Segment Length: " << avgSegmentLength << " pixels" << endl;
    cout << "Segment Length Variation: " << segmentLengthVariation << " pixels (lower = more consistent)" << endl;


    // ---- AVERAGE DISTANCE FROM STRAIGHT LINE ----

    float totalDeviation = 0;
    ofPoint lineDir = (end - start).getNormalized();

    for (int i = 1; i < line.size() - 1; i++) {
        ofPoint point = line[i];
        ofPoint toPoint = point - start;

        // Project onto the straight line
        float projLength = toPoint.dot(lineDir);
        ofPoint projection = start + lineDir * projLength;

        // Distance from point to the straight line
        float deviation = point.distance(projection);
        totalDeviation += deviation;
    }

    avgDeviation = (line.size() > 2) ? totalDeviation / (line.size() - 2) : 0;
    cout << "Average Distance from Straight Line: " << avgDeviation << " pixels" << endl;


    // ---- ORIENTED BOUNDING BOX (Non-axis aligned) ----

    float minArea = FLT_MAX;
    float bestMinX, bestMaxX, bestMinY, bestMaxY;

    // Try rotating at different angles to find minimum bounding box
    for (float angle = 0; angle < 180; angle += 2) {
        float rad = ofDegToRad(angle);
        float cosA = cos(rad);
        float sinA = sin(rad);

        float minX = FLT_MAX, maxX = -FLT_MAX;
        float minY = FLT_MAX, maxY = -FLT_MAX;

        // Rotate all points and find bounds
        for (int i = 0; i < line.size(); i++) {
            float x = line[i].x;
            float y = line[i].y;

            // Rotate point
            float rotX = x * cosA - y * sinA;
            float rotY = x * sinA + y * cosA;

            minX = min(minX, rotX);
            maxX = max(maxX, rotX);
            minY = min(minY, rotY);
            maxY = max(maxY, rotY);
        }

        float width = maxX - minX;
        float height = maxY - minY;
        float area = width * height;

        if (area < minArea) {
            minArea = area;
            bboxAngle = angle;
            bboxWidth = width;
            bboxHeight = height;
            bestMinX = minX;
            bestMaxX = maxX;
            bestMinY = minY;
            bestMaxY = maxY;
        }
    }

    bboxArea = minArea;

    // Calculate the 4 corners of the bounding box and rotate back to original space
    bboxCorners.clear();
    float rad = ofDegToRad(bboxAngle);
    float cosA = cos(-rad);  // Negative angle to rotate back
    float sinA = sin(-rad);

    // Four corners in rotated space
    vector<ofPoint> rotatedCorners;
    rotatedCorners.push_back(ofPoint(bestMinX, bestMinY));
    rotatedCorners.push_back(ofPoint(bestMaxX, bestMinY));
    rotatedCorners.push_back(ofPoint(bestMaxX, bestMaxY));
    rotatedCorners.push_back(ofPoint(bestMinX, bestMaxY));

    // Rotate back to original space
    for (int i = 0; i < 4; i++) {
        float x = rotatedCorners[i].x;
        float y = rotatedCorners[i].y;
        float origX = x * cosA - y * sinA;
        float origY = x * sinA + y * cosA;
        bboxCorners.push_back(ofPoint(origX, origY));
    }

    cout << "\nOriented Bounding Box:" << endl;
    cout << "  Width: " << bboxWidth << " pixels" << endl;
    cout << "  Height: " << bboxHeight << " pixels" << endl;
    cout << "  Area: " << bboxArea << " square pixels" << endl;
    cout << "  Rotation: " << bboxAngle << " degrees" << endl;

    cout << "====================================\n" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    computeAndPrintStatistics();
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
