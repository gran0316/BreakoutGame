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


Brick::Brick() : GameObject()
{

}

Brick::~Brick()
{
    
}

void Brick::update(double aDelta)
{
    
}

void Brick::paint()
{
    //Draw the Red Brick with a white outline
    OpenGLRenderer::getInstance()->setLineWidth(2.0f);
    OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorBlack());
    OpenGLRenderer::getInstance()->drawRectangle(getX(), getY(), getWidth(), getHeight());
    OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorWhite());
    OpenGLRenderer::getInstance()->drawRectangle(getX(), getY(), getWidth(), getHeight(), false);
    OpenGLRenderer::getInstance()->setLineWidth(1.0f);
}

void Brick::reset()
{
    //Get the screen width and height
    float screenWidth = ScreenManager::getInstance()->getScreenWidth();
    float screenHeight = ScreenManager::getInstance()->getScreenHeight();
    
    //Reset the Brick's width and height
    setWidth(80.0f);
    setHeight(30.0f);
    
    //Reset the x and y position
    setX(0);
    setY(0);
    
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