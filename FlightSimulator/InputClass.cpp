#include "InputClass.h"

InputClass::InputClass()
{
	m_InputSDK = 0;
	m_KeyBoardDev = 0;
	m_MouseDev = 0;
}

InputClass::InputClass(const InputClass& other)
{
}

InputClass::~InputClass()
{
}

bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	m_iScreenWidth = screenWidth; 
	m_iScreenHeight  = screenHeight;
	
	m_iMouseX = 0; 
	m_iMouseY = 0;

	if (DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_InputSDK,	NULL))
		return false;

	if (m_InputSDK->CreateDevice(GUID_SysKeyboard, &m_KeyBoardDev, nullptr))
		return false;

	m_KeyBoardDev->SetDataFormat(&c_dfDIKeyboard);

	m_KeyBoardDev->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	m_KeyBoardDev->Acquire();

	if (m_InputSDK->CreateDevice(GUID_SysMouse, &m_MouseDev, nullptr))
		return false;

	m_MouseDev->SetDataFormat(&c_dfDIMouse);

	m_MouseDev->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	m_MouseDev->Acquire();

	return true;
}

void InputClass::SetInputDev(void)
{
	if (nullptr == m_KeyBoardDev ||
		nullptr == m_MouseDev)
		return;

	m_KeyBoardDev->GetDeviceState(256, m_chKeyState);
	m_MouseDev->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}

void InputClass::ShutDown()
{
	if (m_MouseDev)
	{
		m_MouseDev->Unacquire();
		m_MouseDev->Release();
		m_MouseDev = 0;
	}

	if (m_KeyBoardDev)
	{
		m_KeyBoardDev->Unacquire();
		m_KeyBoardDev->Release();
		m_KeyBoardDev = 0;
	}
	
	if(m_InputSDK) 
	{
		m_InputSDK->Release();
		m_InputSDK = 0;
	} 
	
	return;
}

bool InputClass::KeyPressing(unsigned char byKeyID)
{
	if (m_chKeyState[byKeyID] & 0x8000)
		return true;

	return false;
}

bool InputClass::KeyDown(unsigned char byKeyID)
{
	if (m_chKeyState[byKeyID] & 0x8000)
	{
		if (m_bKeyDown[byKeyID] == false)
		{
			m_bKeyDown[byKeyID] = true;
			return true;
		}
	}

	else
	{
		m_bKeyDown[byKeyID] = false;
	}

	return false;
}

signed char InputClass::GetDIMouseState(MOUSEKEYSTATE eMouse)
{
	return m_tMouseState.rgbButtons[eMouse];
}

long InputClass::GetDIMouseMove(MOUSEMOVESTATE eMouseState)
{
	return *(((signed long*)&m_tMouseState) + eMouseState);
}