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

class MyCircles {
private:
    int radius;
public:
    ofVec3f pos;     // center position of circle
    ofVec3f color;   // color or circle
    int curRadius;
   //window
    bool isClose;    // if window is closed
    float timeOpen;
    float amountTimeClosed;

    //fish
    float originX;      // original position in X
    float originY;      // original position in Y
    int direction;     // 0 up 1 right
    int initFrame;    // stores in what frame itr started
    int curPoint;
    bool arrived;
    
    MyCircles(ofVec3f pos_, ofVec3f color_, int r, float timer, int initFrame_);
    void updateStatus();
    void setOpen(float t,int rad);
    void setClose();
    void updateFish(ofVec2f point, float amplitude, float period, float speed);
    
    
};
#endif /* defined(__myGifAnimation__MyCircles__) */
