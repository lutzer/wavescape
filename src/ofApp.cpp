#include "ofApp.h"

static const int LANDSCAPE_SIZE = 1024;
static const float Z_MULTIPLICATOR = 80.0;

double getValue(vector<double> array, float x, float y) {
    float size = LANDSCAPE_SIZE;
    return array[int(x * size) + int(y * size) * LANDSCAPE_SIZE];
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    landscape = vector<float>(LANDSCAPE_SIZE*LANDSCAPE_SIZE);
    
    //create wave landscape with a base frequency of bufferSize / sampleRate = 43 Hz
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
    targetFrequency = 1.0;

    soundStream.printDeviceList();
    //soundStream.setDeviceID(0)
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);

    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);

    //create landscape mesh
    for (int i=0; i < landscape.size(); i++) {
        int x = i % LANDSCAPE_SIZE;
        int y = i / LANDSCAPE_SIZE;
        landscapeMesh.addVertex(ofVec3f(x, y, landscape[i] * Z_MULTIPLICATOR));
    }
    landscapeMesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_POINTS);

    //setup camera
    ofPoint center(LANDSCAPE_SIZE/2,LANDSCAPE_SIZE/2, 0);
    cam.setTarget(center);
    cam.setDistance(2000);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float dt = ofGetElapsedTimef();
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    
    // Draw 3d scene.
    ofEnableDepthTest();
    cam.begin();

    ofSetColor(120,120,120,120);
    landscapeMesh.draw();

    ofDrawAxis(LANDSCAPE_SIZE);

    ofSetColor(255,0,0,120);
    ofDrawSphere(phase * LANDSCAPE_SIZE, 0, 0, 20.0);
    
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

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){

    while (phase >= 1.0){
        phase -= 1.0;
    }

    double phaseStep = (targetFrequency / sampleRate);

    for (int i = 0; i < bufferSize; i++){

        float sample = landscape[phase * LANDSCAPE_SIZE];

        lAudio[i] = output[i*nChannels    ] = sample * volume;
        rAudio[i] = output[i*nChannels + 1] = sample * volume;

        phase = fmod(phase + phaseStep, 1.0);
    }

    //ofLog() << phase;



//    //pan = 0.5f;
//    float leftScale = 1 - pan;
//    float rightScale = pan;
//
//    // sin (n) seems to have trouble when n is very large, so we
//    // keep phase in the range of 0-TWO_PI like this:
//    while (phase > TWO_PI){
//        phase -= TWO_PI;
//    }
//
//    if ( bNoise == true){
//        // ---------------------- noise --------------
//        for (int i = 0; i < bufferSize; i++){
//            lAudio[i] = output[i*nChannels    ] = ofRandom(0, 1) * volume * leftScale;
//            rAudio[i] = output[i*nChannels + 1] = ofRandom(0, 1) * volume * rightScale;
//        }
//    } else {
//        phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
//        for (int i = 0; i < bufferSize; i++){
//            phase += phaseAdder;
//            float sample = sin(phase);
//            lAudio[i] = output[i*nChannels    ] = sample * volume * leftScale;
//            rAudio[i] = output[i*nChannels + 1] = sample * volume * rightScale;
//        }
//    }
    
}
