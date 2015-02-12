#pragma once

#include "ofMain.h"
#include "MyCircles.h"


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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    void addParticles(bool isInit);
    void addFish(ofVec2f pos, ofColor color, TypeCircle type_);
    int calcPos(int x, int y);
    ofColor window_color;
    ofColor background_color;
    
    //circles in back
    int radius;
    int num_circles;
    int num_per_row;
    float time_open;
    vector<MyCircles> circles;
    vector<int> closed_index;
    bool openTime;
    vector<MyCircles> blue_c;
    
    
    //colors
    vector<ofColor>moveSides_colors;
    vector<ofColor>followEdge_colors;
    vector<ofColor>multipleS_colors;

    
    
   // main window shape when open
    vector<int> init_pos;
    vector<int> wayPoints;
    bool isRandom;
    bool isHeart;
    bool isNumasbala;
    
    
    //image saver
    ofImage grabbed;
    bool startRecording;
};
