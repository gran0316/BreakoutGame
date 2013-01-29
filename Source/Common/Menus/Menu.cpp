#include "Menu.h"


Menu::Menu() : Screen()
{
  m_MenuTitle = NULL;
  m_MenuSelectionBox = new OpenGLTexture(MENU_SELECTION_BOX);
  m_SelectedIndex = -1;
}
 
Menu::~Menu()
{
  //Delete the menu title textuer
  if(m_MenuTitle != NULL)
  {
    delete m_MenuTitle;
    m_MenuTitle = NULL;
  }

  //Delete the selection box texture
  if(m_MenuSelectionBox != NULL)
  {
    delete m_MenuSelectionBox;
    m_MenuSelectionBox = NULL;
  }

  //Delete the menu option textures
  for(int i = 0; i < m_MenuOptions.size(); i++)
  {
    delete m_MenuOptions.at(i);
    m_MenuOptions.at(i) = NULL;
  }

  //Clear the menu options
  m_MenuOptions.clear();
}
 
void Menu::update(double delta)
{
  //Not used
}

void Menu::paint()
{
  //Draw the menu title
  int x = (getWidth() - m_MenuTitle->getSourceWidth()) * MENU_TITLE_X_PERCENTAGE;
  int y = (getHeight() - m_MenuTitle->getSourceHeight()) * MENU_TITLE_Y_PERCENTAGE;
  OpenGLRenderer::getInstance()->drawTexture(m_MenuTitle, (float)x, (float)y);

  //Draw the menu options
  y = getHeight() * MENU_OPTIONS_STARTING_Y_PERCENTAGE;
  for(int i = 0; i < m_MenuOptions.size(); i++)
  {
    //Get the menu option at index i
    OpenGLTexture* menuOption = m_MenuOptions.at(i);

    //Calculate the x for the menu option and then draw it
    x = (getWidth() - menuOption->getSourceWidth()) * MENU_OPTIONS_X_PERCENTAGE;
    OpenGLRenderer::getInstance()->drawTexture(menuOption, (float)x, (float)y);

    //If i is equal to the selected index, draw the selection box
    if(i == m_SelectedIndex)
    {
      OpenGLRenderer::getInstance()->drawTexture(m_MenuSelectionBox, (float)x, (float)y);
    }

    //Increment the y for the next menu option
    y += menuOption->getSourceHeight();
  }
}

void Menu::reset()
{
  //If there are menu options, set the selected index to zero
  if(m_MenuOptions.size() >= 1)
  {
    m_SelectedIndex = 0;
  }
}

void Menu::screenWillAppear()
{
  //Set the background color to black
  OpenGLRenderer::getInstance()->setBackgroundColor(OpenGLColorBlack());

  //Reset the menu
  reset();
}

void Menu::screenWillDisappear()
{
  //Not used
}

void Menu::keyUpEvent(int aKeyCode)
{
  if(aKeyCode == KEYCODE_RETURN)
  {
    menuAction(getSelectedIndex());
  }
  else if(aKeyCode == KEYCODE_UP_ARROW && m_SelectedIndex != -1)
  {
    m_SelectedIndex--;
    if(m_SelectedIndex < 0)
    {
      m_SelectedIndex = 0;
    }
  }
  else if(aKeyCode == KEYCODE_DOWN_ARROW && m_SelectedIndex != -1)
  {
    m_SelectedIndex++;
    if(m_SelectedIndex >= m_MenuOptions.size())
    {
      m_SelectedIndex = m_MenuOptions.size() - 1;
    }
  }
}

int Menu::getSelectedIndex()
{
  return m_SelectedIndex;
}

void Menu::addMenuTitle(OpenGLTexture* aMenuTitle)
{
  if(aMenuTitle != NULL)
  {
    m_MenuTitle = aMenuTitle;
  }
}

void Menu::addMenuOption(OpenGLTexture* aMenuOption)
{
  if(aMenuOption != NULL)
  {
    m_MenuOptions.push_back(aMenuOption);

    if(m_MenuOptions.size() == 1)
    {
      m_SelectedIndex = 0;
    }
  }
}