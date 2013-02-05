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
    
  //Load the game bricks on startup so they exist and can be changed.
  void loadBricks();
    
  //Game level Methods
    
  //Loads the current level of the game.
  void loadGameLevel(int level);
    
  //Checks to see if the game is over.
  bool checkGameOver();
    
  //Checks to see if we need a new level.
  bool newLevel();
    
  //Manages the balls on each update to handle active and inactive balls. 
  void manageBalls();
    
  //Checks the current in game ball count.
  int checkBallCount();
  
  //Check for an extra ball proc.
  void extraBallProc();
  
  //Returns a bool wether we should proc extra balls or not.
  bool getExtraBall();
  
  //Spawns balls on proc.
  void spawnBalls();
    
private:
  //Mouse Events
  void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);

  //Key Events
  void keyUpEvent(int keyCode);

  //Vector to hold the GameObjects
  std::vector<GameObject*> m_GameObjects;
  //Vector to manage bricks.
  std::vector<Brick*> m_CurrentBricks;
  
  //Timer variable to delay reseting the game has ended
  double m_GameOverTimer;
    
  //Current game lives.
  int m_GameLives;
   
  //Current game level.
  int m_CurrentGameLevel;
   
  //Bool for AI toggle.
  bool m_AI;
    
  //Bool for extra ball proc.
  bool m_ExtraBalls;
    
  //Ball point to set speed of balls and is used for AI.
  Ball* m_CurrentActiveBall;
   
  //OpenGLTextures for the game. It's Community themed. It returns February 7th. BE EXCITED!
  OpenGLTexture* m_Background;
  OpenGLTexture * m_Ball;
  OpenGLTexture * m_Brick;
  OpenGLTexture * m_Paddle;
};

#endif