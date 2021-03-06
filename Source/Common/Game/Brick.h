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

class OpenGLTexture;

//Paddle class, inherits from GameObject
class Brick : public GameObject
{
public:
    Brick(int x, int y, int tag);
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
    int getTag();
    
protected:
    float m_Width;
    float m_Height;
    
    float m_PositionX;
    float m_PositionY;
    
    float m_InitialXPosition;
    float m_InitialYPosition;
    
    int m_LevelTag;
    
    OpenGLTexture * m_Brick;
};


#endif /* defined(__GAM_1532_OSX_Game__Brick__) */
