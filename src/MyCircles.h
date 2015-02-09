//
//  MyCircles.h
//  myGifAnimation
//
//  Created by Mariale Montenegro on 2/5/15.
//
//

#ifndef __myGifAnimation__MyCircles__
#define __myGifAnimation__MyCircles__

#include "ofMain.h"
#include <stdio.h>

enum TypeCircle {moveRight, moveUp, followWayP, moveBound, windowObj };


class MyCircles {

private:
    int radius;
public:
    ofVec3f pos;     // center position of circle
    ofColor color;   // color or circle
    int curRadius;
   //window
    bool isClose;    // if window is closed
    float timeOpen;
    float amountTimeClosed;

    //particles
    TypeCircle type;
    
    float originX;      // original position in X
    float originY;      // original position in Y
   
    int initFrame;    // stores in what frame itr started
    int curPoint;
    bool arrived;
    
    MyCircles(ofVec3f pos_, ofColor color_, int r, float timer, int initFrame_, TypeCircle type_);
    void updateStatus();
    void setOpen(float t,int rad);
    void setClose();
    void updateParticles(ofVec2f point, float amplitude, float period, float speed);
    
    
};
#endif /* defined(__myGifAnimation__MyCircles__) */
