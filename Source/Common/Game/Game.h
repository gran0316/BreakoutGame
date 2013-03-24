#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../Screen Manager/Screen.h"

class GameObject;
class Brick;
class Ball;
class Paddle;
class OpenGLTexture;

class Game : public Screen, public InputListener
{
public:
  Game();
  ~Game();

  //Game lifecycle methods
  void update(double delta);
  void paint();
  void reset();
  
  //Method to check whether or not we need to call a game over.
  void checkGameOver();

  //Screen name, must be implemented, it's a pure
  //virtual method in the Screen class
  const char* getName();
    
  //Screen event method, inherited from the screen class
  void screenWillAppear();

  //GameObject Methods
  void addGameObject(GameObject* gameObject);
  GameObject* getGameObjectByType(const char* type);
    
  //Load the game bricks on startup so they exist and can be changed.
  void loadBricks();
    
  //Game level Methods
    
  //Loads the current level of the game.
  void loadGameLevel();
  void setBallAndPaddle();
    
  //Checks to see if we need a new level.
  bool newLevel();
  void restartGame();
    
  void toggleControl();
    
  void setLevel(int level);
    
private:
  //Mouse Events
  void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);

  //Key Events
  void keyUpEvent(int keyCode);
  void keyDownEvent(int keyCode);

  //Vector to hold the GameObjects
  std::vector<GameObject*> m_GameObjects;

  //Timer variable to delay reseting the game has ended
  double m_GameOverTimer;
    
  //Current game lives.
  short m_GameLives;
   
  //Current game level.
  short m_CurrentGameLevel;
   
  //Bool for AI toggle.
  bool m_AI;
    
    //Bool for control toggle.
    bool m_KeyboardEnabled;
    bool m_MouseEnabled;
    
  //Ball point to set speed of balls and is used for AI.
  Ball* m_ActiveBall;
  Paddle* m_Paddle;
   
  //OpenGLTextures for the game. It's Community themed. It returns February 7th. BE EXCITED!
  OpenGLTexture * m_Background;
  OpenGLTexture * m_Lives;
};

#endif