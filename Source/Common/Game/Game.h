#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../Screen Manager/Screen.h"

class GameObject;
class Brick;
class Ball;
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
    
  void resetBall();
  void resetLevel();
  
  //Game Over method, call this when to end the game
  void gameOver();

  //Screen name, must be implemented, it's a pure
  //virtual method in the Screen class
  const char* getName();
    
  //Screen event method, inherited from the screen class
  void screenWillAppear();

  //GameObject Methods
  void addGameObject(GameObject* gameObject);
  GameObject* getGameObjectByType(const char* type);
    
private:
  //Mouse Events
  void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);

  //Key Events
  void keyUpEvent(int keyCode);
    
  void nextLevel();
    
  void paintLevelInfo(float alpha);

  //Vector to hold the GameObjects
  std::vector<GameObject*> m_GameObjects;

  //Timer variable to delay reseting the game has ended.
  double m_GameOverTimer;
    
  //Timer variable to delay the begining for the next level.
  double m_NextLevelTimer;
    
  double m_StartDelayTimer;
  float m_LevelInfoAlpha;
    
  //Current game lives.
  short m_GameLives;
   
  //Current game level.
  short m_CurrentGameLevel;
   
  //Bool for AI toggle.
  bool m_AI;
    
  //Ball pointer for AI.
  Ball* m_ActiveBall;
   
  //OpenGLTextures for the game. It's Community themed. It returns February 7th. BE EXCITED!
  OpenGLTexture * m_Background;
  OpenGLTexture * m_Lives;
};

#endif