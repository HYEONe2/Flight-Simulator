#include "SystemClass.h"

SystemClass::SystemClass()
{
	m_pInput = 0;
	m_pGraphics = 0;
	m_pFps = 0;
	m_pCpu = 0;
	m_pTimer = 0;
	m_Sound = 0;
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	int iScreenWidth, iScreenHeight;
	bool result;
	
	// Initialize the width and height of the screen to zero before sending the variables into the function.
	iScreenWidth = 0;
	iScreenHeight = 0;
	
	// Initialize the windows api.
	InitializeWindows(iScreenWidth, iScreenHeight);
	
	// Create the input object. This object will be used to handle reading the keyboard input from the user.
	m_pInput = new InputClass;
	if (!m_pInput)
	{
		return false;
	}

	// Initialize the input object.
	result = m_pInput->Initialize(m_hInstance, m_hWnd, iScreenWidth, iScreenHeight);
	if (!result) 
	{ 
		MessageBox(m_hWnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false; 
	}

	// Create the graphics object. This object will handle rendering all the graphics for this application.
	m_pGraphics = new GraphicsClass;
	if (!m_pGraphics)
	{
		return false;
	}
	// Initialize the graphics object.
	m_pGraphics->SetInputClass(m_pInput);
	result = m_pGraphics->Initialize(iScreenWidth, iScreenHeight, m_hWnd);
	if (!result)
	{
		return false;
	}

	// Create the fps object.
	m_pFps = new FpsClass;
	if (!m_pFps)
	{
		return false;
	}
	// Initialize the fps object.
	m_pFps->Initialize();

	// Create the cpu object.
	m_pCpu = new CpuClass;
	if (!m_pCpu)
	{
		return false;
	}
	// Initialize the cpu object.
	m_pCpu->Initialize();

	// Create the timer object.
	m_pTimer = new TimerClass;
	if (!m_pTimer)
	{
		return false;
	}
	// Initialize the timer object.
	result = m_pTimer->Initialize();
	if (!result)
	{
		MessageBox(m_hWnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the sound object.
	m_Sound = new SoundClass;
	if (!m_Sound)
	{
		return false;
	}
	// Initialize the sound object.
	result = m_Sound->InitializeBGM(m_hWnd);
	if (!result)
	{
		MessageBox(m_hWnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	// Release the sound object.
	if (m_Sound)
	{
		m_Sound->Shutdown();
		delete m_Sound;
		m_Sound = 0;
	}

	// Release the graphics object.
	if (m_pGraphics)
	{
		m_pGraphics->Shutdown();
		delete m_pGraphics;
		m_pGraphics = 0;
	}
	
	// Release the input object.
	if (m_pInput)
	{
		m_pInput->ShutDown();
		delete m_pInput;
		m_pInput = 0;
	}
	
	// Release the cpu object.
	if (m_pCpu)
	{
		m_pCpu->Shutdown();
		delete m_pCpu;
		m_pCpu = 0;
	}
	
	// Release the fps object.
	if (m_pFps)
	{
		delete m_pFps;
		m_pFps = 0;
	}

	// Release the timer object.
	if (m_pTimer)
	{
		delete m_pTimer;
		m_pTimer = 0;
	}

	// Shutdown the window.
	ShutdownWindows();

	return;
}

void SystemClass::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	bool done = false, result;

	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}
	return;
}

bool SystemClass::Frame()
{
	bool result;

	// Update the system stats.
	m_pTimer->Frame();
	m_pFps->Frame();
	m_pCpu->Frame();

	m_pInput->SetInputDev();
	if (m_pInput->KeyPressing(DIK_ESCAPE))
	{
		return false;
	}
	m_pGraphics->MoveCamera(m_pTimer->GetTime());

	// Do the frame processing for the graphics object.
	result = m_pGraphics->Frame(m_pFps->GetFps(), m_pCpu->GetCpuPercentage(), m_pTimer->GetTime());
	if (!result)
	{
		return false;
	}
	return true;
}

void SystemClass::InitializeWindows(int& iScreenWidth, int& iScreenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
	// Get an external pointer to this object.
	ApplicationHandle = this;
	// Get the instance of this application.
	m_hInstance = GetModuleHandle(NULL);
	// Give the application a name.
	m_wstrApplicationName = L"Engine";
	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_wstrApplicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	// Register the window class.
	RegisterClassEx(&wc);
	// Determine the resolution of the clients desktop screen.
	iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)iScreenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)iScreenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		iScreenWidth = 800;
		iScreenHeight = 600;
		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - iScreenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - iScreenHeight) / 2;
	}
	// Create the window with the screen settings and get the handle to it.
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_wstrApplicationName, m_wstrApplicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, iScreenWidth,
		iScreenHeight, NULL, NULL, m_hInstance, NULL);
	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
	// Hide the mouse cursor.
	ShowCursor(false);
	return;
}

void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_wstrApplicationName, m_hInstance);
	m_hInstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	}

	return 1;
}