#include "ofApp.h"

static const int LANDSCAPE_SIZE = 1024;
static const int GRID_CELL_SIZE = 32;
static const float Z_MULTIPLICATOR = 80.0;

float getSample(const vector<float> &array, float x, float y, int size) {

    float ind = x * size;

    // liner interpolate between two x values
    float val1 = array[ind];
    float val2 = array[(int)(ind + 1) % size];

    return val1 + (val2 - val1) * fmod(ind,1.0);
}

//--------------------------------------------------------------
void ofApp::setup(){

    //create wave landscape
    landscape = vector<float>(LANDSCAPE_SIZE*LANDSCAPE_SIZE);
    for (int x=0; x < LANDSCAPE_SIZE; x++) {
        for (int y=0; y < LANDSCAPE_SIZE; y++) {
            landscape[x + y * LANDSCAPE_SIZE] = sin(x / (double)LANDSCAPE_SIZE * TWO_PI) *
            sin(y / (double)LANDSCAPE_SIZE * TWO_PI + M_PI_2);
        }
    }

    //setup audio
    int bufferSize = 256;
    sampleRate = 44100;
    volume = 1.0f;
    
    soundStream.printDeviceList();
    //soundStream.setDeviceID(2);
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);

    //setup camera
    ofPoint center(LANDSCAPE_SIZE/2,LANDSCAPE_SIZE/2, 0);
    cam.setPosition(center + ofVec3f(0, 0, 1000));
    cam.setTarget(center);
    cam.setDistance(2000);

    //setup gui
    gui.setup();
    gui.setHeaderBackgroundColor(ofColor::lightGray);
    gui.add(frequency.setup("frequency", 40, 1, 1000));
    
    //create landscape mesh
    landscapeMesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_POINTS);
    for (int i=0; i < landscape.size(); i++) {
        int x = i % LANDSCAPE_SIZE;
        int y = i / LANDSCAPE_SIZE;
        
        if (x % GRID_CELL_SIZE != 0 && y % GRID_CELL_SIZE != 0)
            continue;
        
        landscapeMesh.addVertex(ofVec3f(x, y, landscape[i] * Z_MULTIPLICATOR));
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //float dt = ofGetElapsedTimef();
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);

    
    // Draw 3d scene.
    ofEnableDepthTest();
    cam.begin();

    ofSetColor(120,120,120,120);
    landscapeMesh.draw();

    ofDrawAxis(LANDSCAPE_SIZE);

    ofSetColor(255,0,0,255);
    ofDrawSphere(phase * LANDSCAPE_SIZE, 0, 0, 10.0);
    
    cam.end();
    ofDisableDepthTest();

    gui.draw();
    
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

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){


    double phaseStep = (frequency / sampleRate);

    for (int i = 0; i < bufferSize; i++){

        float sample = getSample(landscape, phase, 0.0, LANDSCAPE_SIZE);

        /*lAudio[i] =*/ output[i*nChannels    ] = sample * volume;
        /*rAudio[i] =*/ output[i*nChannels + 1] = sample * volume;

        phase = fmod(phase + phaseStep, 1.0);
    }
    
}
