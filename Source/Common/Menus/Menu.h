#ifndef MENU_H
#define MENU_H

#include "../Screen Manager/ScreenManager.h"
#include "../Screen Manager/Screen.h"
#include "../Constants/Constants.h"
#include "../OpenGL/OpenGL.h"
#include <vector>

//Abstract menu class, inherits from the screen class. All Menus should 
//inherit from this class, it provides menu options control and a callback
//method upon option selection. All centers title at the top. Override the 
//paint method to allow for custom drawing.
class Menu : public Screen
{
public:
  Menu();
  virtual ~Menu();
 
  //Lifecycle methods, inherited from the Screen class
  virtual void update(double delta);
  virtual void paint();
  virtual void reset();

  //Screen events, inherited from the Screen class
  virtual void screenWillAppear();
  virtual void screenWillDisappear();

  //Inherited from the Screen (which inherits from the InputListener), used 
  //to detected keyUp enter, up and down arrow events and handle them.
  void keyUpEvent(int keyCode);

  //Conveniance methods to add the menu title and menu options.
  void addMenuTitle(OpenGLTexture* menuTitle);
  void addMenuOption(OpenGLTexture* menuOption);

  //Conveniance method to get the selected menu option index.
  int getSelectedIndex();

protected:
  //This method must be implemented in inheriting classes, it is called when a 
  //menu option is selected, the selected menu options index is passed as a parameter
  virtual void menuAction(int index) = 0;

private:
  //Private member variables, they are private so inheriting classes don't misuse them.
  OpenGLTexture* m_MenuTitle;
  OpenGLTexture* m_MenuSelectionBox;
  std::vector <OpenGLTexture*>m_MenuOptions;
  int m_SelectedIndex;
};

#endif