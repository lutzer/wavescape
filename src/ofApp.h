#pragma once

#include "ofMain.h"
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
        void audioOut(float * input, int bufferSize, int nChannels);
    
        vector<float> landscape1;
        vector<float> landscape2;

        /* VISUAL OBJECTS */
        ofMesh landscapeMesh;
        ofEasyCam cam;

        ofVec3f* path;
        int pathIndex;

        ofxPanel gui;
        ofxFloatSlider frequency;
        ofxFloatSlider radius;
        ofxFloatSlider cusps;
        ofxFloatSlider rotation;
        ofxFloatSlider transition;

        /* SOUND OBJECTS */
        ofSoundStream soundStream;
        int		sampleRate;
        float 	volume;
        float phase;

        vector <float> lAudio;
        vector <float> rAudio;

};
