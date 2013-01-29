#include "Game.h"
#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "..//Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"


Game::Game()
{
  //Create a new paddle and ball
  addGameObject(new Paddle());
  addGameObject(new Ball());
  
  reset();
}

Game::~Game()
{
  //Delete all the GameObject's in the vector
  for(int i = 0; i < m_GameObjects.size(); i++)
  {
    delete m_GameObjects.at(i);
    m_GameObjects.at(i) = NULL;
  }
  
  //Clear the pointers from the vector
  m_GameObjects.clear();
}

void Game::update(double aDelta)
{
  //If the GameOver Timer is greater that zero, countdown
  if(m_GameOverTimer > 0.0)
  {
    m_GameOverTimer -= aDelta;
    if(m_GameOverTimer < 0.0)
    {
      m_GameOverTimer = 0.0;
	  ScreenManager::getInstance()->switchScreen(GAME_OVER_MENU_NAME);
    }
    return;
  }

  //Get the ball GameObject, we'll use this for collision detection
  Ball* ball = (Ball*)getGameObjectByType(GAME_BALL_TYPE);

  //Cycle through all the game objects update them and check their collision detection
  for(int i = 0; i < m_GameObjects.size(); i++)
  {
    //Make sure the GameObject is active
    if(m_GameObjects.at(i)->getIsActive() == true)
    {
      //Update the GameObject
      m_GameObjects.at(i)->update(aDelta);
      
      //Check collision detection against the ball
      if(m_GameObjects.at(i) != ball)
      {
        ball->checkCollision(m_GameObjects.at(i));
      }
    }
  }
}

void Game::paint()
{
  //Cycle through and draw all the game objects
  for(int i = 0; i < m_GameObjects.size(); i++)
  {
    if(m_GameObjects.at(i)->getIsActive() == true)
    {
      m_GameObjects.at(i)->paint();
    }
  }
  
  //Draw the outer white walls
  OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorWhite());
  OpenGLRenderer::getInstance()->setLineWidth(4.0f);
  OpenGLRenderer::getInstance()->drawLine(1.0f, 0.0f, 1.0f, getHeight());
  OpenGLRenderer::getInstance()->drawLine(0.0f, 1.0f, getWidth(), 1.0f);
  OpenGLRenderer::getInstance()->drawLine(getWidth() - 1, 0.0f, getWidth() - 1, getHeight());
  OpenGLRenderer::getInstance()->setLineWidth(1.0f);
}

void Game::reset()
{
  //Cycle through and reset all the game objects
  for(int i = 0; i < m_GameObjects.size(); i++)
  {
    m_GameObjects.at(i)->reset();
  }
  
  //Reset the game over timer to zero
  m_GameOverTimer = 0.0;
}

void Game::gameOver()
{
  m_GameOverTimer = GAME_OVER_TIMER;
}

const char* Game::getName()
{
	return GAME_SCREEN_NAME;
}

void Game::screenWillAppear()
{
  OpenGLRenderer::getInstance()->setBackgroundColor(OpenGLColorCornflowerBlue());
}

void Game::addGameObject(GameObject* aGameObject)
{
  if(aGameObject != NULL)
  {
    m_GameObjects.push_back(aGameObject);
  }
}

GameObject* Game::getGameObjectByType(const char* aType)
{
  //Cycle through a find the game object (if it exists)
  for(unsigned int i = 0; i < m_GameObjects.size(); i++)
  {
    if(strcmp(m_GameObjects.at(i)->getType(), aType) == 0)
    {
      return m_GameObjects.at(i);
    }
  }
  return NULL;
}

void Game::mouseMovementEvent(float aDeltaX, float aDeltaY, float aPositionX, float aPositionY)
{
  //Set the paddle to the x position of the mouse
  Paddle* paddle = (Paddle*)getGameObjectByType(GAME_PADDLE_TYPE);

  //Safety check, paddle could be NULL
  if(paddle != NULL)
  {
    paddle->setX(aPositionX - (paddle->getWidth() / 2.0f));
  }
}

void Game::keyUpEvent(int aKeyCode)
{
  //
  if(aKeyCode == KEYCODE_ESCAPE)
  {
    //
    ScreenManager::getInstance()->switchScreen(PAUSE_MENU_NAME);
  }
}
