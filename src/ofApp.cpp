#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(10);
    ofEnableSmoothing();
    
    radius      = 35;
    num_circles = 410; //238 //410
    num_per_row = 24; //17 24
    window_color = ofColor(255,255,255);//ofColor(249,242,231);//(238, 232, 222);
    background_color = ofColor(0,0,0);//ofColor(153,178,183);//(73,72,104);
    
    //Creating main circle windows
    int j = -1;
    for (int i = 0;i< num_circles;i++)
    {
        int k = i % num_per_row;
        float x = radius + (k * radius*1.8) - 10;
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
    

    multipleS_colors.push_back(ofColor(26,26,25));
    multipleS_colors.push_back(ofColor(36,36,35));
    multipleS_colors.push_back(ofColor(46,46,45));
    
    //side
    //multipleS_colors.push_back(ofColor(192,41,66));
    //multipleS_colors.push_back(ofColor(198,31,59));
    //multipleS_colors.push_back(ofColor(136,15,36));
    
    multipleS_colors.push_back(ofColor(0,223,252));
    multipleS_colors.push_back(ofColor(0,168,198));
    multipleS_colors.push_back(ofColor(64,192,203));
    
    
    //heart shape
    if(isHeart)
    {
        int t[] = { calcPos(0,4), calcPos(0,12),calcPos(1,3), calcPos(1,5),calcPos(1,11),calcPos(1,13),calcPos(2,2),calcPos(2,6),calcPos(2,10),calcPos(2,14),
        calcPos(3,2),calcPos(3,7),calcPos(3,9),calcPos(3,14), calcPos(4,2), calcPos(4,8),calcPos(4,14),calcPos(5,3),calcPos(5,13),calcPos(6,4),
        calcPos(6,12),calcPos(7,5),calcPos(7,11), calcPos(8,6), calcPos(8,10), calcPos(9,7), calcPos(9,9),calcPos(10,8) };
       
        for (int i = 0; i < (sizeof(t) / sizeof(int)); ++i) init_pos.push_back(t[i]);
    }
    
    // numasbala shape
    if(isNumasbala)
    {
        int mid  = num_per_row/2;   //8
        int midY = num_circles/num_per_row *0.5  -1;  //6
       
        
        int t[] = { calcPos(midY-5,mid), calcPos(midY-4,mid),calcPos(midY-4,mid+1), calcPos(midY-3,mid+1),calcPos(midY-3,mid+2),calcPos(midY-2,mid),
            calcPos(midY-1,mid),calcPos(midY,mid-5),calcPos(midY,mid-4),calcPos(midY,mid-3),calcPos(midY,mid-2),calcPos(midY,mid-1),calcPos(midY,mid),
            calcPos(midY,mid+1), calcPos(midY,mid+2),calcPos(midY,mid+3),calcPos(midY,mid+4),calcPos(midY,mid+5),calcPos(midY,mid+4),
            calcPos(midY+1,mid-5),calcPos(midY+1,mid+5),calcPos(midY+2,mid-4), calcPos(midY+2,mid+4), calcPos(midY+3,mid-3), calcPos(midY+3,mid+3),
            calcPos(midY+4,mid-2),calcPos(midY+4,mid+2),calcPos(midY+5,mid-1),calcPos(midY+5,mid),calcPos(midY+5,mid+1) };
        
      
        for (int i = 0; i < (sizeof(t) / sizeof(int)); ++i) init_pos.push_back(t[i]);
    }
  
    for(vector<int>::iterator it = init_pos.begin(); it != init_pos.end();++it)
        circles[*it].type = moveUp;
    
    
    for (vector<MyCircles>::iterator it = circles.begin() ; it != circles.end(); ++it)
    {
        if(it->type != moveUp)
        {
            MyCircles t = *it;
            
            t.color = multipleS_colors[ofRandom(3, multipleS_colors.size())];
            blue_c.push_back(t);
        }
    }
}

int ofApp::calcPos(int x, int y)
{
    return (num_per_row * x) + y;
}


//--------------------------------------------------------------
void ofApp::update(){

    //update circles that are closing
    float period    =  25;
    float amplitude = radius;
    for (vector<MyCircles>::iterator it = circles.begin() ; it != circles.end(); ++it)
    {
        if(it->type == moveUp)
        {
            it->curRadius = amplitude * sin(TWO_PI * (ofGetFrameNum() )/period) ;
        }
        else{
            it->curRadius = amplitude * cos(TWO_PI * (ofGetFrameNum() )/period) ;
        }
    }
    
    amplitude = radius/2;
    for (vector<MyCircles>::iterator it = blue_c.begin() ; it != blue_c.end(); ++it)
    {
        it->curRadius = amplitude * sin(TWO_PI * (ofGetFrameNum() )/period) ;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(background_color);
    
    // drawing all my circles
    for(int i = 0; i < circles.size();i++) {
        MyCircles temp = circles[i];
        ofSetColor(temp.color);
        ofFill();
        ofCircle(temp.pos.x, temp.pos.y, temp.pos.z, temp.curRadius);
    }
   //draw blue circles
    for (vector<MyCircles>::iterator it = blue_c.begin() ; it != blue_c.end(); ++it)
    {
        MyCircles temp = *it;
        ofSetColor(temp.color);
        ofFill();
        ofCircle(temp.pos.x, temp.pos.y, temp.pos.z, temp.curRadius);
    }


    // record screen
    if(startRecording){
        grabbed.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        string name ="img_" + ofToString(ofGetFrameNum()) + ".jpg";
        grabbed.saveImage(name);
    }
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
