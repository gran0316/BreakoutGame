//
//  Brick.h
//  GAM-1532 OSX Game
//
//  Created by Derek Grant on 13-01-22.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1532_OSX_Game__Brick__
#define __GAM_1532_OSX_Game__Brick__

#include <iostream>

#include "GameObject.h"


//Paddle class, inherits from GameObject, is controlled by the
//mouse input on the x-axis.
class Brick : public GameObject
{
public:
    Brick();
    ~Brick();
    
    //Implementing the pure virtual lifecycle methods from GameObject
    void update(double delta);
    void paint();
    
    //Overriding the virtual reset method from GameObject
    void reset();
    
    //Implementing the pure virtual type method from GameObject
    const char* getType();
    
    //Setter size methods
    void setSize(float width, float height);
    void setWidth(float width);
    void setHeight(float height);
    
    //Getter size methods
    void getSize(float &width, float &height);
    float getWidth();
    float getHeight();
    
protected:
    float m_Width;
    float m_Height;
};


#endif /* defined(__GAM_1532_OSX_Game__Brick__) */
