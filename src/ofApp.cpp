#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(10);
    ofEnableSmoothing();
    
    radius      = 35;
    num_circles = 204;
    num_per_row = 17;
    time_open   = 0.5;
    window_color = ofColor(238, 232, 222);
    background_color = ofColor(73,72,104);
    
    //Creating main circle windows
    int j = -1;
    for (int i = 0;i< num_circles;i++)
    {
        int k = i % num_per_row;
        float x = radius + (k * radius*1.8) - 30;
        if(k == 0)
            j++;
        
        float y = (radius) + (j * radius*1.8) -5;
        circles.push_back(MyCircles(ofVec3f(x, y, 0), window_color, radius, time_open, ofGetFrameNum(), windowObj)); //ofVec3f(52,56,56)
    }
    
   
    grabbed.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    startRecording = false;
    isRandom    = false;
    isHeart     = false;
    isNumasbala = true;
    openTime = false;
    
    particleType = multipleSections;
    if(particleType == multipleSections)
    {
        // numasbala
        bound_sections.push_back(ofVec2f(calcPos(8,0), circles.size()-2) ); // bottom
        bound_sections.push_back(ofVec2f(calcPos(0,7), calcPos(2,12)) );   // top
        bound_sections.push_back(ofVec2f(calcPos(0,8), calcPos(10,8)) );   // center top bottom
    }
    randomColor = false;
    
    //heart shape
    if(isHeart)
    {
        int t[] = { calcPos(0,4), calcPos(0,12),calcPos(1,3), calcPos(1,5),calcPos(1,11),calcPos(1,13),calcPos(2,2),calcPos(2,6),calcPos(2,10),calcPos(2,14),
        calcPos(3,2),calcPos(3,7),calcPos(3,9),calcPos(3,14), calcPos(4,2), calcPos(4,8),calcPos(4,14),calcPos(5,3),calcPos(5,13),calcPos(6,4),
        calcPos(6,12),calcPos(7,5),calcPos(7,11), calcPos(8,6), calcPos(8,10), calcPos(9,7), calcPos(9,9),calcPos(10,8) };
        
        wayPoints.push_back( calcPos(0,4)); wayPoints.push_back( calcPos(2,6));wayPoints.push_back( calcPos(4,8));wayPoints.push_back( calcPos(2,10));
        wayPoints.push_back( calcPos(0,12)); wayPoints.push_back( calcPos(2,14));wayPoints.push_back( calcPos(4,14));wayPoints.push_back( calcPos(7,11));
        wayPoints.push_back( calcPos(10,8)); wayPoints.push_back( calcPos(7,5));wayPoints.push_back( calcPos(4,2));wayPoints.push_back( calcPos(2,2));
        for (int i = 0; i < (sizeof(t) / sizeof(int)); ++i) init_pos.push_back(t[i]);
    }
    
    // numasbala shape
    if(isNumasbala)
    {
        int t[] = { calcPos(0,8), calcPos(1,8),calcPos(1,9), calcPos(2,9),calcPos(2,10),calcPos(3,8),calcPos(4,8),calcPos(5,3),calcPos(5,4),
            calcPos(5,5),calcPos(5,6),calcPos(5,7),calcPos(5,8), calcPos(5,9), calcPos(5,10),calcPos(5,11),calcPos(5,12),calcPos(5,13),calcPos(5,14),
            calcPos(6,3),calcPos(6,13),calcPos(7,4), calcPos(7,12), calcPos(8,5), calcPos(8,11), calcPos(9,6),calcPos(9,10),calcPos(10,7),
            calcPos(10,8),calcPos(10,9) };
        
        wayPoints.push_back( calcPos(0,8)); wayPoints.push_back( calcPos(2,10)); wayPoints.push_back( calcPos(2,9));wayPoints.push_back( calcPos(3,8));
        wayPoints.push_back( calcPos(5,8));wayPoints.push_back( calcPos(5,13)); wayPoints.push_back( calcPos(6,13));wayPoints.push_back( calcPos(10,9));
        wayPoints.push_back( calcPos(10,7));wayPoints.push_back( calcPos(6,3)); wayPoints.push_back( calcPos(5,3));wayPoints.push_back( calcPos(5,8));
        
        for (int i = 0; i < (sizeof(t) / sizeof(int)); ++i) init_pos.push_back(t[i]);
    }
    int row = 1;
    float extraTime = 0;
    for(vector<int>::iterator it = init_pos.begin(); it != init_pos.end();++it){
        if(*it / num_per_row > row){
            row++;
            extraTime += 0.0;
        }
        circles[*it].setOpen(ofGetElapsedTimef() + extraTime, 0);
    }
    

    // init particles
    addParticles(true);
}

int ofApp::calcPos(int x, int y)
{
    return (num_per_row * x) + y;
}


//--------------------------------------------------------------
void ofApp::update(){
    
    float period    = 10;
    float amplitude = 10;
    float speed     = 10;
    
    if(ofGetFrameNum()%2 == 0 && fish.size() < num_particles){
        addParticles(false);

    }
    
    for (int i = 0;i< fish.size();i++)
    {
        float s = speed;
        ofVec2f p = ofVec2f();
        if(fish[i].type == followWayP){
            s = ofRandom(8, 16);
            p = circles[wayPoints[fish[i].curPoint]].pos;
            if(fish[i].arrived)
            {
                fish[i].arrived = false;
                fish[i].curPoint = (fish[i].curPoint+1)%wayPoints.size();
                p = circles[wayPoints[fish[i].curPoint]].pos;
            }
        }
        if(fish[i].type == moveBound)
            s = speed + 10;
        fish[i].updateParticles(p,amplitude, period, s);
    }

    //update circles that are closing
    for (vector<MyCircles>::iterator it = circles.begin() ; it != circles.end(); ++it)
        it->updateStatus();
    
    
   // if(ofGetFrameNum()%10 == 0)
     //   startRecording = !startRecording;
    if(ofGetFrameNum()%5 == 0)
        openTime = !openTime;
    
    
    if(ofGetFrameNum()%2 == 0) {
        if(isHeart || isNumasbala)
        {
            int row = 0;
            int add = 0;
            float extraTime = 0;
            for(vector<int>::iterator it = init_pos.begin(); it != init_pos.end();++it){
               
                if(openTime)
                {
                    if(!circles[*it].isClose){
                        if(*it / num_per_row >row)
                            row++;
                        continue;
                    }
                    if(*it / num_per_row > row && add > 4)break;
                    if(*it / num_per_row > row){
                        add ++;
                        row++;
                    }
                    
                    circles[*it].setOpen(ofGetElapsedTimef() + time_open, 0);
                }
                else{
                    
                    if(circles[*it].isClose){
                        if(*it / num_per_row >row)
                            row++;
                        continue;
                    }
                    if(*it / num_per_row > row && add > 4)break;
                    if(*it / num_per_row > row){
                        add ++;
                        row++;
                    }
                    
                    circles[*it].setClose();
                }
            }
        }

        // Add open closed circles randomly
        if(isRandom)
        {
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
    ofBackground(background_color);
    // drawing all my fish
    
    for(int i = 0; i < fish.size();i++) {
        MyCircles temp = fish[i];
        if(particleType == multipleSections)
        { // 10,8
            cout<<circles[bound_sections[0].x].isClose<<endl;
            if(temp.type == followWayP || (temp.type == moveBound && !circles[bound_sections[2].x].isClose) ||
               (temp.type == moveRight && !circles[bound_sections[2].y].isClose) )  {
                ofSetColor(temp.color);
                ofFill();
                ofCircle(temp.pos.x, temp.pos.y, temp.pos.z, temp.curRadius);
            }
        }
        else
        {
            ofSetColor(temp.color);
            ofFill();
            ofCircle(temp.pos.x, temp.pos.y, temp.pos.z, temp.curRadius);
        }
        
    }
    //for(int i = 12;i<18;i++)
    //circles[i].radius = 1;
    // drawing all my circles
    for(int i = 0; i < circles.size();i++) {
        MyCircles temp = circles[i];
        ofSetColor(temp.color);
        ofFill();
        ofCircle(temp.pos.x, temp.pos.y, temp.pos.z, temp.curRadius);
    }
   
    grabbed.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
  
    string name ="img_" + ofToString(ofGetFrameNum()) + ".jpg";
    if(startRecording)
        grabbed.saveImage(name);
}

//--------------------------------------------------------------
void ofApp::addParticles(bool isInit) {
    
    if(particleType == followEdge)
    {
        num_particles = 200;
        //add particles along enge
        addFish(circles[calcPos(0,8)].pos, ofColor(16,16,15), followWayP);
    }
    if(particleType == moveSides)
    {
        num_particles = 200;
        int side_particles = 10;
        if(!isInit)side_particles = 1;
        
        //adding particles that move right left
        for(int i = 0;i < side_particles; i++){
            
            int r = ofRandom(calcPos(8,0), circles.size()-2);
            addFish(circles[r].pos, ofColor(0,223,252), moveRight);
        }
    }
    if(particleType == multipleSections)
    {
        num_particles = 2000;
        int side_particles = 100;
        int bound_particles = 200;
        
        if(!isInit) {
            side_particles  = 1;
            bound_particles = 1;
        }
        //adding particles that move right left
        for(int i = 0;i < side_particles; i++){
            
            int r = ofRandom(bound_sections[0].x, bound_sections[0].y);
            addFish(circles[r].pos, ofColor(0,223,252), moveRight);
        }
        for(int i = 0;i < bound_particles;i++){
            
            int r = ofRandom(bound_sections[1].x, bound_sections[1].y);
            addFish(circles[r].pos, ofColor(16,16,15), moveBound);
        }
        //add particles along enge
        addFish(circles[calcPos(0,8)].pos, ofColor(16,16,15), followWayP);
    }

    
}

//--------------------------------------------------------------
void ofApp::addFish(ofVec2f pos, ofColor color, TypeCircle type_) {

    MyCircles newFish =  MyCircles(ofVec3f(pos.x, pos.y, 0), color, ofRandom(3, 12), time_open, ofGetFrameNum(), type_) ;
   
    if(newFish.type == followWayP){
       
        newFish.pos = circles[wayPoints[0]].pos;
    }
  
     fish.push_back(newFish);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'g')
        startRecording = !startRecording;
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
