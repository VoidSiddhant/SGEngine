#include "Input.h"

namespace SGEngine
{
	Input& Input::instance()
	{
		static Input* _instance = new Input();
		return *_instance;
	}
	
	Input::Input()
	{
		m_lastFrameKey = 999;
		m_lastFrameReleasedKey = 999;

		for(int i = 0 ; i<256;i++)
		{
			keyState[i] = 0;
		}
	}

	Input::~Input()
	{

	}

	void Input::ClearLastFrameKey()
	{
		m_lastFrameKey = 999;
		m_lastFrameReleasedKey = 999;
	}

	//Keyboard.................................................................
	void Input::SetKeyDown(SG_UINT virtualKeyCode)
	{
		if (keyState[virtualKeyCode] == false)
			m_lastFrameKey = virtualKeyCode;
		keyState[virtualKeyCode] = true;
	}
	void Input::SetKeyUp(SG_UINT virtualKeyCode)
	{
		m_lastFrameReleasedKey = virtualKeyCode;
		keyState[virtualKeyCode] = false;
	}

	bool Input::GetKey(SG_UINT keyCode)
	{
		return keyState[keyCode];
	}

	bool Input::GetKeyDown(SG_UINT keyCode)
	{
		if (m_lastFrameKey == keyCode)
			return true;
		else
			return false;
	}
	bool Input::GetKeyUp(SG_UINT keyCode)
	{
		if (m_lastFrameReleasedKey == keyCode)
			return true;
		else
			return false;
	}
} // namespace
