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
		
    void addFish(ofVec2f initPos, ofVec3f color);
    int calcPos(int x, int y);
    //circles in back
    int radius;
    int num_circles;
    int num_per_row;
    float time_open;
    vector<MyCircles> circles;
    vector<int> closed_index;
    
    // fish elements
    int num_fish;
    int initPos;
    vector<MyCircles> fish;
    
    int timer;
    float curTimer;
    
    vector<ofVec2f> grid_pos;
     vector<int> init_pos;
    vector<int> wayPoints;
    bool isRandom;
    bool isHeart;
    bool isNumasbala;
};
