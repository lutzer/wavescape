#include "ofApp.h"

static const int LANDSCAPE_SIZE = 1024;

double getValue(vector<double> array, float x, float y) {
    return array[x + y * LANDSCAPE_SIZE];
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    landscape = vector<double>(LANDSCAPE_SIZE*LANDSCAPE_SIZE);
    
    
    //crate landscape
    for (int x=0; x < LANDSCAPE_SIZE; x++) {
        for (int y=0; y < LANDSCAPE_SIZE; y++) {
            landscape[x + y * LANDSCAPE_SIZE] = sin(x / (double)LANDSCAPE_SIZE * PI * 2);
        }
    }
    
    phasor.setRepeatType(LOOP);
    pashor.setCurve(LINEAR);
    phasor.animateTo(1.0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float dt = ofGetElapsedTimef();
    phasor.update(dt);
    
    //float angle = phasor * PI * 2;
    
    float y = 0;
    float x = value * LANDSCAPE_SIZE;
    
    double value = landscape[x + y * LANDSCAPE_SIZE];
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofMesh mesh;
    for (int i=0; i < landscape.size(); i += 16) {
        int x = i % LANDSCAPE_SIZE;
        int y = i / LANDSCAPE_SIZE;
        mesh.addVertex(ofVec3f(x,y,landscape[i]));
    }
    
    // Draw 3d scene.
    ofEnableDepthTest();
    cam.begin();
    
    mesh.draw();
    
    cam.end();
    ofDisableDepthTest();
    
    
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
