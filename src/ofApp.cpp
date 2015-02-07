#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(10);
    // Smooth edges
    ofEnableSmoothing();
    
    radius      = 35;
    num_circles = 200;
    num_per_row = 17;
    time_open   = 220;
    
    int j = -1;
    for (int i = 0;i< num_circles;i++)
    {
        int k = i % num_per_row;
        float x = radius + (k * radius*1.8) - 30;
        if(k == 0)
            j++;
        
        float y = (radius) + (j * radius*1.8) -5;
       if(i%3 == 0)
           grid_pos.push_back(ofVec2f(x,y));
        circles.push_back(MyCircles(ofVec3f(x, y, 0), ofVec3f(52,56,56), radius, time_open, ofGetFrameNum()));
    }
    
   
    
    isRandom    = false;
    isHeart     = true;
    isNumasbala = false;
   
    //heart shape
    if(isHeart)
    {
        int t[] = { calcPos(0,4), calcPos(0,12),calcPos(1,3), calcPos(1,5),calcPos(1,11),calcPos(1,13),calcPos(2,2),calcPos(2,6),calcPos(2,10),calcPos(2,14),
        calcPos(3,2),calcPos(3,7),calcPos(3,9),calcPos(3,14), calcPos(4,2), calcPos(4,8),calcPos(4,14),calcPos(5,3),calcPos(5,13),calcPos(6,4),
        calcPos(6,12),calcPos(7,5),calcPos(7,11), calcPos(8,6), calcPos(8,10), calcPos(9,7), calcPos(9,9),calcPos(10,8) };
        
        wayPoints.push_back( calcPos(0,4));
        wayPoints.push_back( calcPos(2,6));
        wayPoints.push_back( calcPos(4,8));
        wayPoints.push_back( calcPos(2,10));
        wayPoints.push_back( calcPos(0,12));
        wayPoints.push_back( calcPos(2,14));
        wayPoints.push_back( calcPos(4,14));
        wayPoints.push_back( calcPos(7,11));
        wayPoints.push_back( calcPos(10,8));
        wayPoints.push_back( calcPos(7,5));
        wayPoints.push_back( calcPos(4,2));
        wayPoints.push_back( calcPos(2,2));
        for (int i = 0; i < (sizeof(t) / sizeof(int)); ++i) init_pos.push_back(t[i]);
    }
    
    // numasbala shape
    if(isNumasbala)
    {
        int t[] = { calcPos(0,8), calcPos(1,8),calcPos(1,9), calcPos(2,9),calcPos(2,10),calcPos(3,8),calcPos(4,8),calcPos(5,3),calcPos(5,4),
            calcPos(5,5),calcPos(5,6),calcPos(5,7),calcPos(5,8), calcPos(5,9), calcPos(5,10),calcPos(5,11),calcPos(5,12),calcPos(5,13),calcPos(5,14),
            calcPos(6,3),calcPos(6,13),calcPos(7,4), calcPos(7,12), calcPos(8,5), calcPos(8,11), calcPos(9,6),calcPos(9,10),calcPos(10,7),
            calcPos(10,8),calcPos(10,9) };
        
        wayPoints.push_back( calcPos(0,8));
        wayPoints.push_back( calcPos(2,10));
        wayPoints.push_back( calcPos(2,9));
         wayPoints.push_back( calcPos(3,8));
        wayPoints.push_back( calcPos(5,8));
        wayPoints.push_back( calcPos(5,13));
        wayPoints.push_back( calcPos(6,13));
        wayPoints.push_back( calcPos(10,9));
        wayPoints.push_back( calcPos(10,7));
        wayPoints.push_back( calcPos(6,3));
        wayPoints.push_back( calcPos(5,3));
        wayPoints.push_back( calcPos(5,8));
        
        for (int i = 0; i < (sizeof(t) / sizeof(int)); ++i) init_pos.push_back(t[i]);
    }
    
    for(vector<int>::iterator it = init_pos.begin(); it != init_pos.end();++it)
        circles[*it].setOpen(ofGetElapsedTimef(), 0);
    
   
    
    // init fish
    num_fish = 200;
    int counter = 0;
    for (vector<ofVec2f>::iterator it = grid_pos.begin(); it != grid_pos.end(); ++it)
    {
        addFish(*it, ofVec3f(0,223,252));
        counter++;
        if(counter > 2)break;
    }
    
    timer = 1;
    curTimer = ofGetElapsedTimef();
}

int ofApp::calcPos(int x, int y)
{
    return (num_per_row * x) + y;
}
//--------------------------------------------------------------
void ofApp::update(){
    
    float period    = 10;
    float amplitude = 10;
    float speed     = 8;
    
    if(timer%3 == 0 && fish.size() < num_fish){
        int r = ofRandom(0, grid_pos.size());
        addFish(grid_pos[r], ofVec3f(0,223,252));
    }
    
    timer++;
    for (int i = 0;i< fish.size();i++)
    {
        ofVec2f p = ofVec2f();
        if(isHeart || isNumasbala){
            speed = ofRandom(4, 14);
            p = circles[wayPoints[fish[i].curPoint]].pos;
            if(fish[i].arrived)
            {
                fish[i].arrived = false;
                fish[i].curPoint = (fish[i].curPoint+1)%wayPoints.size();
                p = circles[wayPoints[fish[i].curPoint]].pos;
            }
        }
        fish[i].updateFish(p,amplitude, period, speed);
    }

    //update circles that are closing
   
    for (vector<MyCircles>::iterator it = circles.begin() ; it != circles.end(); ++it)
    {
        it->updateStatus();
    }
    
    
    // Add open closed circles randomly
    if(isRandom)
    {
        if(ofGetFrameNum()%2 == 0) {
           int r = ofRandom(0, num_circles);
           if(circles[r].isClose)
            {
                circles[r].setOpen(ofGetElapsedTimef(), 0);

            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,140,158);
    
    // drawing all my fish
    for(int i = 0; i < fish.size();i++) {
        MyCircles temp = fish[i];
        ofSetColor(temp.color.x,temp.color.y,temp.color.z);
        ofFill();
        ofCircle(temp.pos.x, temp.pos.y, temp.pos.z, temp.curRadius);
    }
   
    //for(int i = 12;i<18;i++)
    //circles[i].radius = 1;
    // drawing all my circles
    for(int i = 0; i < circles.size();i++) {
        MyCircles temp = circles[i];
        ofSetColor(temp.color.x,temp.color.y,temp.color.z);
        ofFill();
        ofCircle(temp.pos.x, temp.pos.y, temp.pos.z, temp.curRadius);
    }
   
}

//--------------------------------------------------------------
void ofApp::addFish(ofVec2f pos, ofVec3f color) {

    MyCircles newFish =  MyCircles(ofVec3f(pos.x, pos.y, 0), color, ofRandom(3, 12), time_open, ofGetFrameNum()) ;
   
    if(isHeart || isNumasbala){
        newFish.direction = 3;
        newFish.color = ofVec3f(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
        newFish.pos = circles[wayPoints[0]].pos;
    }
    else {
        if(pos.y > pos.x){
            newFish.direction = 0;
            newFish.color = ofVec3f(174,226,57);
        }
    }
     fish.push_back(newFish);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
