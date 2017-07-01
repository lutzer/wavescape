#include "ofApp.h"

static const int LANDSCAPE_SIZE = 1024;
static const int GRID_CELL_SIZE = 32;
static const float Z_MULTIPLICATOR = 80.0;
static const int PATH_SIZE = 128;

// gets a sample from a cubic array,
// wrap parameters defines if the matrix wraps at the edges or extends the edge values
float getSample(const vector<float> &array, float x, float y, int size, bool wrap) {

    int i = x * size;
    int j = y * size;

    int iplus,jplus;

    if ((i+1) < size && (j+1) < size) {
        iplus = i + 1;
        jplus = j + 1;
    } else if ((i+1) < size) {
        iplus = i + 1;
        jplus = wrap ? 0 : j;
    } else {
        iplus = wrap ? 0 : i;
        jplus = j + 1;
    }

    // get 4 sruounding values
    float v00 = array[i + j * size];
    float v01 = array[iplus + j * size];
    float v10 = array[i + jplus * size];
    float v11 = array[iplus + jplus * size];

    // get x and y remainders
    float xrem = fmod(x*size, 1.0);
    float yrem = fmod(y*size, 1.0);

    // bilinear interpolate between the 4 values
    return v00 * (1 - xrem) * (1 - yrem) + v01 * xrem * (1 - yrem) + v10 * (1 - xrem) * yrem + v11 * xrem * yrem;
}

ofVec2f hypocycloid(float angle, float k, float r) {
    return ofVec2f(
        r * (k - 1) * cos(angle) + r * cos((k - 1) * angle),
        r * (k - 1) * sin(angle) + r * sin((k - 1) * angle)
    );
}

//--------------------------------------------------------------
void ofApp::setup(){

    //create wave landscape
    landscape = vector<float>(LANDSCAPE_SIZE*LANDSCAPE_SIZE);
    for (int x=0; x < LANDSCAPE_SIZE; x++) {
        for (int y=0; y < LANDSCAPE_SIZE; y++) {
            landscape[x + y * LANDSCAPE_SIZE] =
            sin(x / (double)LANDSCAPE_SIZE * TWO_PI) *
            //fmod(y * 2.0 / (double)LANDSCAPE_SIZE, 1.0);
            sin(y * 2 / (double)LANDSCAPE_SIZE * TWO_PI + M_PI_2 );
        }
    }

    // initialize path
    path = new ofVec3f[PATH_SIZE];
    pathIndex = 0;

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
    gui.add(radius.setup("path_radius", 0.25, 0.01, 0.25));
    gui.add(cusps.setup("path_cusps", -1, -10, 10));
    
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
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);

    
    // Draw 3d scene.
    ofEnableDepthTest();
    cam.begin();

    ofSetColor(120,120,120,120);
    landscapeMesh.draw();

    //ofDrawAxis(LANDSCAPE_SIZE);

    ofSetColor(255,0,0,255);
    for (int i=0; i < PATH_SIZE; i++) {
        ofDrawSphere(path[i], 5.0);
    }

    
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

        //float x = sin(phase * M_PI * 2) * 0.45 + 0.5;
        //float y = cos(phase * M_PI * 2) * 0.45 + 0.5;

        ofVec2f p = hypocycloid(phase * PI * 2, cusps, radius) * 0.5;
        p += ofVec2f(0.5,0.5);

        path[pathIndex] = ofVec3f(p.x * LANDSCAPE_SIZE, p.y * LANDSCAPE_SIZE, 0);
        pathIndex = (pathIndex + 1) % PATH_SIZE;

        p.x = fmod(p.x,1.0);
        p.y = fmod(p.y,1.0);

        float sample = getSample(landscape, p.x, p.y, LANDSCAPE_SIZE, false);

        /*lAudio[i] =*/ output[i*nChannels    ] = sample * volume;
        /*rAudio[i] =*/ output[i*nChannels + 1] = sample * volume;

        phase = fmod(phase + phaseStep, 1.0);
    }
    
}
