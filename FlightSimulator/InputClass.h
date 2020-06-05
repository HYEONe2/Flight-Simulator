#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class InputClass
{
public:
	enum MOUSEKEYSTATE { DIM_LBUTTON, DIM_RBUTTON, DIM_WHEELBUTTON, DIM_XBUTTON, DIM_END };
	enum MOUSEMOVESTATE { DIMM_X, DIMM_Y, DIMM_WHEEL, DIMM_END };

public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void SetInputDev();
	void ShutDown();

	//bool GetDIKeyState(unsigned char);
	bool KeyDown(unsigned char);
	bool KeyPressing(unsigned char);
	signed char GetDIMouseState(MOUSEKEYSTATE);
	signed long GetDIMouseMove(MOUSEMOVESTATE);

private:
	bool m_keys[256];
	
	LPDIRECTINPUT8 m_InputSDK = nullptr;
	LPDIRECTINPUTDEVICE8 m_KeyBoardDev;
	LPDIRECTINPUTDEVICE8 m_MouseDev;

	signed char m_chKeyState[256];
	bool        m_bKeyDown[256]; 
	bool        m_bKeyUp[256];   

	DIMOUSESTATE m_tMouseState;
	int m_iScreenWidth, m_iScreenHeight;
	int m_iMouseX, m_iMouseY;
};