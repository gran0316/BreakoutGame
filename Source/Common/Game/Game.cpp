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
  m_Background = new OpenGLTexture("background");
  m_Lives = new OpenGLTexture("ball");
    
  //Create a new paddle and ball
  addGameObject(new Paddle());
  addGameObject(new Ball());
  
  //Add the extra balls.
  addGameObject(new Ball());
  addGameObject(new Ball());
    
  //Initialise the game lives.
  m_GameLives = 3;

  //Loads the bricks the game will be using.
  loadBricks();
    
  //Initialise AI to false.
  m_AI = false;
    
  //Set the bool for extra bricks to false.
  m_ExtraBalls = false;

  //Set the current game level to the first game level.
  m_CurrentGameLevel = GAME_LEVEL_ONE;
    
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
  
  //Clear the points from the current brick vector.
  m_CurrentBricks.clear();
    
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
      if (m_CurrentGameLevel > GAME_LEVEL_FIVE)
      {
           m_CurrentGameLevel = GAME_LEVEL_ONE;
      }

	  //Reset the game.
      reset();
  }
    
  //Call the manage Balls to handle active and inactive balls.
  manageBalls();
    
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
            if(m_GameObjects.at(i)->getType() == GAME_PADDLE_TYPE)
            {
                m_GameObjects.at(i)->GameObject::setX(m_CurrentActiveBall->getX() - 100);
            }
        }
        
      //Update the GameObject
      m_GameObjects.at(i)->update(aDelta);
      
      //Check collision detection against the ball
      if(m_GameObjects.at(i) != m_CurrentActiveBall)
      {
          GameObject* gameObject = m_GameObjects.at(i);
          
          for(int i = 0; i < m_GameObjects.size(); i++)
          {
			  //If the object is a ball and is active.
              if (m_GameObjects.at(i)->getType() == GAME_BALL_TYPE &&
                  m_GameObjects.at(i)->getIsActive() == true)
              {
				  //Store it in a pointer to handle colision over multiple balls.
                  Ball* currentBall = (Ball*)m_GameObjects.at(i);
                  
                  currentBall->checkCollision(gameObject);
              }
          }
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
      //Offset for paint the game lives.
      int offset = 0;
      
	  //Check how many lives there are.
      for (int i = 0; i < m_GameLives; i ++)
      {
		  //Paint the life.
          OpenGLRenderer::getInstance()->drawTexture(m_Lives, offset, ScreenManager::getInstance()->getCurrentScreen()->getHeight() - 60);
		  //Increment paint location.
          offset = offset + 50;
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
   //Set active balls to false.
   m_ExtraBalls = false;
    
  //Cycle through and reset all the game objects
  for(int i = 0; i < m_GameObjects.size(); i++)
  {
    m_GameObjects.at(i)->reset();
  }
    
  //Reset the game over timer to zero
  m_GameOverTimer = 0.0;

   //Manager the balls.
    manageBalls();
    
  //Load the current game level.
  loadGameLevel(m_CurrentGameLevel);
}

void Game::gameOver()
{
  m_GameOverTimer = GAME_OVER_TIMER;

  //Reset lives.
  m_GameLives = 3;

  //Reset game Level.
  m_CurrentGameLevel = 1;
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
    for(int i = 0; i < 30; i++)
    {
		//Initialise all the bricks, add them to the brick vector for level management.
        m_CurrentBricks.push_back(new Brick(0,0));
        addGameObject(m_CurrentBricks.at(i));
    }
}

void Game::loadGameLevel(int m_CurrentGameLevel)
{
    //2 floats to hold the xOffset position and the y position the brick will be set too. 
    float xOffset = 110;
    float yPosition = 0;
    
    //Check to see if the current level is the first level.
    if (m_CurrentGameLevel == GAME_LEVEL_ONE)
    {
        //Set the balls speed to the lowest speed.
        m_CurrentActiveBall->setSpeed(GAME_BALL_DEFAULT_SPEED);
        
        //Set the position of the first row of bricks, incrementing the xOffset.
        for (int i = 0; i < 10; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
        
            xOffset = xOffset + 80;
        }
        
        //Reset the xOffset for the next row in this level and set the new yPosition for the new row of bricks.
        xOffset = 110;
        yPosition = 30;
        
        //Set the position of the second row of the bricks, incrementing the xOffset.
        for (int i = 10; i < 20; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            xOffset = xOffset + 80;
        }
        
        //Reset the xOffset for the next row in this level and set the new yPosition for the new row of bricks.
        xOffset = 110;
        yPosition = 60;
        
        //Set the position of the third row of the bricks, incrementing the xOffset.
        for (int i = 20; i < 30; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            xOffset = xOffset + 80;
        }
    }
    
    //Check to see if the current level is the second level.
    if (m_CurrentGameLevel == GAME_LEVEL_TWO)
    {
        //Set the balls speed for the second level.
        m_CurrentActiveBall->setSpeed(450.0f);
        
        //Set the xOffset and yPosition for the first row of bricks.
        xOffset = 110;
        yPosition = 30;
        
        //Set the position of the first row of bricks, incrementing the xOffset.
        for (int i = 0; i < 10; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            xOffset = xOffset + 80;
        }
        
        //Reset the xOffset for the next row in this level and set the new yPosition for the new row of bricks.
        xOffset = 110;
        yPosition = 90;
        
        //Set the position of the second row of the bricks, incrementing the xOffset.
        for (int i = 10; i < 20; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            xOffset = xOffset + 80;
        }
        
        //Reset the xOffset for the next row in this level and set the new yPosition for the new row of bricks.
        xOffset = 110;
        yPosition = 150;
        
        //Set the position of the third row of the bricks, incrementing the xOffset.
        for (int i = 20; i < 30; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            xOffset = xOffset + 80;
        }
    }
    //Check to see if the current level is the second level.
    if (m_CurrentGameLevel == GAME_LEVEL_THREE)
    {
		//Set the balls speed for the third level.
        m_CurrentActiveBall->setSpeed(650.0f);
        
		//Set the xOffset and yPosition for the first row of bricks.
        xOffset = 110;
        yPosition = 90;
        
		//Set the position of the bricks for their respective rows, incrementing the xOffset and change the xOffset and yPositon as needed.

        for (int i = 0; i < 10; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            xOffset = xOffset + 80;
        }
        
        xOffset = 0;
        yPosition = 180;
        
        for (int i = 10; i < 20; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            xOffset = xOffset + 80;
        }
        
        xOffset = 230;
        yPosition = 270;
        
        for (int i = 20; i < 30; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            xOffset = xOffset + 80;
        }
    }
    
    if (m_CurrentGameLevel == GAME_LEVEL_FOUR)
    {
		//Set the balls speed for the fourth level.
        m_CurrentActiveBall->setSpeed(850.0f);

        //Set the xOffset and yPosition for the first row of bricks.
        xOffset = 75;
        yPosition = 90;
        
		//Set the position of the bricks for their respective rows, incrementing the xOffset and change the xOffset and yPositon as needed.
        for (int i = 0; i < 10; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            if(i != 4)
            xOffset = xOffset + 80;
            else
                xOffset = xOffset + 160;
        }
        
        xOffset = 75;
        yPosition = 120;
        
        for (int i = 10; i < 20; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            if(i != 14)
                xOffset = xOffset + 80;
            else
                xOffset = xOffset + 160;
        }
        
        xOffset = 75;
        yPosition = 150;
        
        for (int i = 20; i < 30; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            if(i != 24)
                xOffset = xOffset + 80;
            else
                xOffset = xOffset + 160;
        }
    }
    
	//Set the balls speed for the fifth level.

    if (m_CurrentGameLevel == GAME_LEVEL_FIVE)
    {
		//Set the ball speed for this level.     
        m_CurrentActiveBall->setSpeed(1050.0f);

        //Set the xOffset and yPosition for the first row of bricks.
        xOffset = 75;
        yPosition = 90;
        
        for (int i = 0; i < 10; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            if(i != 4)
                xOffset = xOffset + 80;
            else
                xOffset = xOffset + 160;
        }
        
        xOffset = 75;
        yPosition = 190;
        
        for (int i = 10; i < 20; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
 
            xOffset = xOffset + 80;
        }
        
        xOffset = 75;
        yPosition = 290;
        
        for (int i = 20; i < 30; i++)
        {
            m_CurrentBricks.at(i)->setX(xOffset);
            m_CurrentBricks.at(i)->setY(yPosition);
            
            if(i != 24)
                xOffset = xOffset + 80;
            else
                xOffset = xOffset + 160;
        }
    }
}

bool Game::newLevel()
{
    for (int i = 0; i < m_CurrentBricks.size(); i++)
    {
        if(m_CurrentBricks.at(i)->getIsActive() == true)
        {
			//If an active brick is found we know the game is not over yet, return true.
            return false;
        }
    }
    
	//Else increment the game lives.
    m_GameLives++;
    
    return true;
}

void Game::manageBalls()
{
    for (int i = 0; i < m_GameObjects.size(); i++)
    {
        if (m_GameObjects.at(i)->getType() == GAME_BALL_TYPE &&
            m_GameObjects.at(i)->getIsActive() == true)
        {
			//If the ball at this position is active, set it to the current ball
			//so a th current ball always has a value for AI and setting speeds.
            m_CurrentActiveBall = (Ball*)m_GameObjects.at(i);
        }
    }
    
	//If theres only one ball left in game, allow for pocs.
    if(checkBallCount() == 1)
    {
        m_ExtraBalls = true;
    }
}

int Game::checkBallCount()
{
	//This value will be returned.
    int currentBallCount = 0;
    
    for (int i = 0; i < m_GameObjects.size(); i++)
    {
		//If the object is active and it's a ball.
        if (m_GameObjects.at(i)->getType() == GAME_BALL_TYPE
            && m_GameObjects.at(i)->getIsActive() == true)
        {
			//If a ball is found increment the ball count.
            currentBallCount++;
        }
    }

    return currentBallCount;
}

bool Game::checkGameOver()
{
	//If there's no ball it's a level over. Player loses a life and reset is called.
    if(checkBallCount() == 0)
    {
        m_GameLives--;
        reset();
    }
    
	//If the game lives are 0 the game is over.
    if (m_GameLives == 0)
    {
        return true;
    }
    
    return false;
}

void Game::extraBallProc()
{
	//Roll a random number.
    int randomRoll = rand() % 10;
    
	//If there's only one ball in the game and the random roll is 5, spawn the balls.
    if(checkBallCount() == 1)
    {
        if(randomRoll == 5)
        {
            spawnBalls();
        }
    }
}

void Game::spawnBalls()
{
	//Set this to true on entry, there is extra balls in the game.
    m_ExtraBalls = true;
    
    for (int i = 0; i < m_GameObjects.size(); i++)
    {
		//Find the inactive balls.
        if (m_GameObjects.at(i)->getType() == GAME_BALL_TYPE &&
            m_GameObjects.at(i)->getIsActive() == false)
        {
			//Set the ball to active and spawn them at the current balls location, with the current balls speed.
            m_GameObjects.at(i)->setIsActive(m_ExtraBalls);
            Ball* ball= (Ball*)m_GameObjects.at(i);
            
            ball->setSpeed(m_CurrentActiveBall->getSpeed());
            ball->setY(m_CurrentActiveBall->getY());
            ball->setX(m_CurrentActiveBall->getX());
        }
    }
    
}

bool Game::getExtraBall()
{
    return m_ExtraBalls;
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
        
        if (m_CurrentGameLevel > GAME_LEVEL_FIVE)
        {
            m_CurrentGameLevel = GAME_LEVEL_ONE;
        }
        
        reset();
    }
}


