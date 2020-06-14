#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "InputClass.h"
#include "GraphicsClass.h"
#include "FpsClass.h"
#include "CpuClass.h"
#include "TimerClass.h"
#include "SoundClass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_wstrApplicationName;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	InputClass* m_pInput;
	GraphicsClass* m_pGraphics;
	FpsClass* m_pFps;
	CpuClass* m_pCpu;
	TimerClass* m_pTimer;
	SoundClass* m_Sound;
};

// Function prototypes
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// Globals
static SystemClass* ApplicationHandle = 0;