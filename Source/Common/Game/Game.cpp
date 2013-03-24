#include "Game.h"
#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "..//Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"


Game::Game()
{
  //Create the textures.
  m_Background = new OpenGLTexture(GAME_BACKGROUND_TEXTURE);
  m_Lives = new OpenGLTexture(GAME_BALL_TEXTURE);
    
  //Create a new paddle and ball
  addGameObject(new Paddle());
  addGameObject(new Ball());
    
  //Initialise the game lives.
  m_GameLives = GAME_STARTING_GAME_LIVES;

  //Loads the bricks the game will be using.
  loadBricks();
    
  //Initialise AI to false.
  m_AI = false;
    
  m_MouseEnabled = true;
  m_KeyboardEnabled = false;

  //Set the current game level to the first game level.
  m_CurrentGameLevel = GAME_DEFAULT_LEVEL;
    
  //Reset the game.
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
    
  //Clear all the OpenGLTextures.
  if (m_Background != NULL)
  {
      m_Background = NULL;
      delete m_Background;
  }
  if (m_Lives != NULL)
  {
      m_Lives = NULL;
      delete m_Lives;
  }
}

void Game::update(double aDelta)
{
  //Check to see if we need a new game level.
  if(newLevel() == true)
   {
	  //If we do increment the current game level.
      m_CurrentGameLevel++;
        
      //If it' set to the max level, set it to level 1.
      if (m_CurrentGameLevel > GAME_MAX_LEVEL)
      {
          ScreenManager::getInstance()->switchScreen(WIN_MENU_NAME);
           m_CurrentGameLevel = GAME_DEFAULT_LEVEL;
      }

	  //Reset the game.
      reset();
  }
    
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

  //Cycle through all the game objects update them and check their collision detection
  for(int i = 0; i < m_GameObjects.size(); i++)
  {
    //Make sure the GameObject is active
    if(m_GameObjects.at(i)->getIsActive() == true)
    {
		//If AI is toggled, make the paddle follow the current active ball.
        if(m_AI)
        {
            m_Paddle->setX(m_ActiveBall->getX() - GAME_BRICK_BALL_OFFSET);
        }
        
      //Update the GameObject
      m_GameObjects.at(i)->update(aDelta);
      
      //Check collision detection against the ball
      if(m_GameObjects.at(i) != m_ActiveBall)
      {
          GameObject* gameObject = m_GameObjects.at(i);
          m_ActiveBall->checkCollision(gameObject);
      }
    }
  }
}

void Game::paint()
{
   //Draw the game background.
   OpenGLRenderer::getInstance()->drawTexture(m_Background, 0.0f, 0.0f, getWidth(), getHeight());
    
  //Cycle through and draw all the game objects
  for(int i = 0; i < m_GameObjects.size(); i++)
  {
    if(m_GameObjects.at(i)->getIsActive() == true)
    {
      m_GameObjects.at(i)->paint();
    }
      //Offset to paint the game lives.
      int offset = 0;
      
	  //Check how many lives there are.
      for (int i = 0; i < m_GameLives; i ++)
      {
		  //Paint the life.
          OpenGLRenderer::getInstance()->drawTexture(m_Lives, offset, ScreenManager::getInstance()->getCurrentScreen()->getHeight() - GAME_LIFE_OFFSET);
		  //Increment paint location.
          offset = offset + GAME_LIFE_INCREMENT;
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
      
      if (m_GameObjects.at(i)->getType() == GAME_BALL_TYPE)
      {
          m_ActiveBall = (Ball *)m_GameObjects.at(i);
      }
      
      if (m_GameObjects.at(i)->getType() == GAME_PADDLE_TYPE)
      {
          m_Paddle = (Paddle *)m_GameObjects.at(i);
      }
  }
    
  //Reset the game over timer to zero
  m_GameOverTimer = 0.0;
    
  //Load the current game level.
  loadGameLevel();
  setBallAndPaddle();
}

void Game::checkGameOver()
{
  //If we have no game lives we lose the game.
  if(m_GameLives == 0)
  {
    m_GameOverTimer = GAME_OVER_TIMER;

    //Reset lives.
    m_GameLives = GAME_STARTING_GAME_LIVES;

    //Reset game Level.
    m_CurrentGameLevel = GAME_DEFAULT_LEVEL;
  }
  //We still have game lives.
  else
  {
      //Reset the ball.
      m_ActiveBall->reset();
        
      m_GameLives--;
  }
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

void Game::loadBricks()
{
    float brickHeight = GAME_BRICK_HEIGHT;
    float brickWidth = GAME_BRICK_WIDTH;
    float brickX = GAME_BRICK_OFFSET;
    float brickY = 0;
    
    for (int row = 0; row < GAME_NUMBER_OF_ROWS; row++)
    {
        for (int collumn = 0; collumn < GAME_NUMBER_OF_COLLUMNS; collumn ++)
        {
            addGameObject(new Brick(brickX, brickY, row + 1));
            
            brickX = brickX + brickWidth;
        }
        
        brickX = GAME_BRICK_OFFSET;
        brickY = brickY + brickHeight;
    }
}

void Game::loadGameLevel()
{
    for (int i = 0; i < m_GameObjects.size(); i++)
    {
        if (m_GameObjects.at(i)->getType() == GAME_BRICK_TYPE)
        {
            Brick* brick = (Brick *)m_GameObjects.at(i);
                
            if(brick->getTag() <= m_CurrentGameLevel)
            {
                brick->setIsActive(true);
            }
                
            else
            {
                brick->setIsActive(false);
            }
        }
    }
}

void Game::setBallAndPaddle()
{
    float currentBallSpeed = m_ActiveBall->getSpeed();
    float currentPaddleWidth = m_Paddle->getWidth();
    
    //Check to see if the current level is the first level.
    if (m_CurrentGameLevel == GAME_DEFAULT_LEVEL)
    {
        //Set the balls speed to the lowest speed.
        m_ActiveBall->setSpeed(GAME_BALL_DEFAULT_SPEED);
        m_Paddle->setWidth(GAME_PADDLE_DEFAULT_WIDTH);
    }
    else 
    {
        m_ActiveBall->setSpeed(currentBallSpeed + GAME_BALL_SPEED_INCREMENT);
        m_Paddle->setWidth(currentPaddleWidth - GAME_PADDLE_WIDTH_DECREMENT);
    }
}

bool Game::newLevel()
{
    for (int i = 0; i < m_GameObjects.size(); i++)
    {
        if(m_GameObjects.at(i)->getType() == GAME_BRICK_TYPE &&
           m_GameObjects.at(i)->getIsActive() == true)
        {
			//If an active brick is found we know the game is not over yet, return true.
            return false;
        }
    }
    
	//Else increment the game lives.
    m_GameLives++;
    
    return true;
}

void Game::restartGame()
{
    //Set the starting values.
    m_GameLives = GAME_STARTING_GAME_LIVES;
    m_CurrentGameLevel = GAME_DEFAULT_LEVEL;
    
    //Load the game level. 
    loadGameLevel();
    setBallAndPaddle();
    
    reset();
}

void Game::toggleControl()
{
    if(!m_KeyboardEnabled)
    {
        m_KeyboardEnabled = true;
        m_MouseEnabled = false;
    }
    else
    {
        m_MouseEnabled = true;
        m_KeyboardEnabled = false;
    }
}

void Game::setLevel(int aLevel)
{
    m_CurrentGameLevel = aLevel;
    
    if (m_CurrentGameLevel > GAME_MAX_LEVEL)
    {
        m_CurrentGameLevel = GAME_DEFAULT_LEVEL;
    }
}

void Game::mouseMovementEvent(float aDeltaX, float aDeltaY, float aPositionX, float aPositionY)
{
    if(m_MouseEnabled)
    m_Paddle->setX(aPositionX - (m_Paddle->getWidth() / 2.0f));
  
}

void Game::keyUpEvent(int aKeyCode)
{
  //
  if(aKeyCode == KEYCODE_ESCAPE)
  {
    //
    ScreenManager::getInstance()->switchScreen(PAUSE_MENU_NAME);
  }
    
  //If the key is A, toggle AI.
    if(aKeyCode == KEYCODE_A)
    {
        if(m_AI)
            m_AI = false;
        else
            m_AI = true;
    }
    
	//If the key is space, skip a level.

    if(aKeyCode == KEYCODE_SPACE)
    {
        m_CurrentGameLevel++;
        
        if (m_CurrentGameLevel > GAME_MAX_LEVEL)
        {
        //BRAD: you can toggle this to show the win screen instead of having to try and beat the level...
            ScreenManager::getInstance()->switchScreen(WIN_MENU_NAME);
            m_CurrentGameLevel = GAME_DEFAULT_LEVEL;
        }
        
        reset();
    }
}

void Game::keyDownEvent(int aKeyCode)
{
    if(m_KeyboardEnabled)
    {
        float currentPosition = m_Paddle->getX();
    
        if(aKeyCode == KEYCODE_S)
        {
            m_Paddle->setX(currentPosition -= GAME_PADDLE_SPEED);
        }
        if(aKeyCode == KEYCODE_D)
        {
            m_Paddle->setX(currentPosition += GAME_PADDLE_SPEED);
        }
    }
}


