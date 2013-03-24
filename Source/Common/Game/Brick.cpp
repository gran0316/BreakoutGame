//
//  Brick.cpp
//  GAM-1532 OSX Game
//
//  Created by Derek Grant on 13-01-22.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Brick.h"
#include "../Constants/Constants.h"
#include "../Screen Manager/ScreenManager.h"
#include "../OpenGL/OpenGL.h"


Brick::Brick(int x, int y, int tag) : GameObject()
{
    m_InitialXPosition = x;
    m_InitialYPosition = y;
    m_LevelTag = tag;
    m_Brick = new OpenGLTexture(GAME_BRICK_TEXTURE);
}

Brick::~Brick()
{
    if(m_Brick != NULL)
    {
        delete m_Brick;
        m_Brick = NULL;
    }
}

void Brick::update(double aDelta)
{
    
}

void Brick::paint()
{
    //Draw the brick. 
    OpenGLRenderer::getInstance()->drawTexture(m_Brick, getX(), getY(), getWidth(), getHeight());
}

void Brick::reset()
{    
    //Reset the Brick's width and height
    setWidth(GAME_BRICK_WIDTH);
    setHeight(GAME_BRICK_HEIGHT);
    
    //Reset the x and y position
    setX(m_InitialXPosition);
    setY(m_InitialYPosition);
    
    //Reset the Brick to active
    setIsActive(true);
}

const char* Brick::getType()
{
    return GAME_BRICK_TYPE;
}

void Brick::setSize(float aWidth, float aHeight)
{
    setWidth(aWidth);
    setHeight(aHeight);
}

void Brick::setWidth(float aWidth)
{
    m_Width = aWidth;
}

void Brick::setHeight(float aHeight)
{
    m_Height = aHeight;
}

void Brick::getSize(float &aWidth, float &aHeight)
{
    aWidth = getWidth();
    aHeight = getHeight();
}

float Brick::getWidth()
{
    return m_Width;
}

float Brick::getHeight()
{
    return m_Height;
}

int Brick::getTag()
{
    return m_LevelTag;
}