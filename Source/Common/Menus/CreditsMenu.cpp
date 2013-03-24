#include "CreditsMenu.h"
#include "../Game/Game.h"


CreditsMenu::CreditsMenu() : Menu()
{
    //Add the menu title
    addMenuTitle(new OpenGLTexture(CREDITS_MENU_TITLE));
    
    //Add the menu's background image.
    //addMenuBackground(new OpenGLTexture(GAME_BACKGROUND_TEXTURE));
    
    m_BackgroundImage = new OpenGLTexture(CREDITS_BACKGROUND_TEXTURE);
    
    m_ScrollValue = 0.0f;
}

CreditsMenu::~CreditsMenu()
{
    if(m_BackgroundImage != NULL)
    {
        delete m_BackgroundImage;
        m_BackgroundImage = NULL;
    }
}

const char* CreditsMenu::getName()
{
    return CREDITS_MENU_NAME;
}

void CreditsMenu::paint()
{
    OpenGLRenderer::getInstance()->drawTexture(m_BackgroundImage, 0.0f, m_ScrollValue);
    
    m_ScrollValue -= 1.0f;
}

void CreditsMenu::menuAction(int aIndex)
{
    
}

void CreditsMenu::keyUpEvent(int aKeyCode)
{
  ScreenManager::getInstance()->switchScreen(MAIN_MENU_NAME);
}