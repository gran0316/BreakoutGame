#include "InputManager.h"
#include "InputListener.h"
#include <stdlib.h>


InputManager* InputManager::m_Instance = NULL;
InputManager* InputManager::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new InputManager();
	}
	
	return m_Instance;
}

void InputManager::cleanupInstance()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

InputManager::InputManager()
{
  m_Listener = NULL;
}

InputManager::~InputManager()
{
  m_Listener = NULL;
}

void InputManager::registerListener(InputListener* aListener)
{
  m_Listener = aListener;
}

void InputManager::unregisterListener()
{
  m_Listener = NULL;
}

bool InputManager::isKeyUp(int aKeyCode)
{
#if WIN32
	if((GetKeyState(aKeyCode) & 0x8000) == 0)
	{
		return true;
	}
#elif TARGET_OS_MAC
  CGEventSourceStateID eventSource = kCGEventSourceStateCombinedSessionState;
  if(CGEventSourceKeyState(eventSource, aKeyCode) == true)
  {
    return true;
  }
#endif

	return false;
}

bool InputManager::isKeyDown(int aKeyCode)
{
#if WIN32
	if((GetKeyState(aKeyCode) & 0x8000) > 0)
	{
		return true;
	}
#elif TARGET_OS_MAC
  CGEventSourceStateID eventSource = kCGEventSourceStateCombinedSessionState;
  if(CGEventSourceKeyState(eventSource, aKeyCode) == true)
  {
    return true;
  }
#endif

	return false;
}

void InputManager::handleMouseMovement(float aDeltaX, float aDeltaY, float aPositionX, float aPositionY)
{
  if(m_Listener != NULL)
  {
    m_Listener->mouseMovementEvent(aDeltaX, aDeltaY, aPositionX, aPositionY);
  }
}

void InputManager::handleMouseLeftClickDown(float aPositionX, float aPositionY)
{
  if(m_Listener != NULL)
  {
    m_Listener->mouseLeftClickDownEvent(aPositionX, aPositionY);
  }
}

void InputManager::handleMouseRightClickDown(float aPositionX, float aPositionY)
{
  if(m_Listener != NULL)
  {
    m_Listener->mouseRightClickDownEvent(aPositionX, aPositionY);
  }
}

void InputManager::handleMouseLeftClickUp(float aPositionX, float aPositionY)
{
  if(m_Listener != NULL)
  {
    m_Listener->mouseLeftClickUpEvent(aPositionX, aPositionY);
  }
}

void InputManager::handleMouseRightClickUp(float aPositionX, float aPositionY)
{
  if(m_Listener != NULL)
  {
    m_Listener->mouseRightClickUpEvent(aPositionX, aPositionY);
  }
}

void InputManager::handleKeyDown(int aKeyCode)
{
  if(m_Listener != NULL)
  {
    m_Listener->keyDownEvent(aKeyCode);
  }
}

void InputManager::handleKeyUp(int aKeyCode)
{
  if(m_Listener != NULL)
  {
    m_Listener->keyUpEvent(aKeyCode);
  }
}
