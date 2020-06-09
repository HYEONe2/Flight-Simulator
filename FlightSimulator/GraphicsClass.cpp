#include "GraphicsClass.h"

#include "GameObjectMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Planet.h"


GraphicsClass::GraphicsClass()
{
	m_pD3D = 0;
	m_pCamera = 0;
	m_pLightShader = 0;
	m_pLight = 0;
	m_pText = 0;

	m_pPlane = 0;
	m_pMonokumaModel = 0;

	m_pGameObjectMgr = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;    
	int iPolyCnt = 0;

	// Create the Direct3D object.  
	m_pD3D = new D3DClass;  
	if(!m_pD3D) 
		return false;
					 
	// Initialize the Direct3D object.  
	result = m_pD3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);  
	if(!result)  
	{   
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);   
		return false;  
	}

	// Create the camera object.
	m_pCamera = new CameraClass;
	if (!m_pCamera)
		return false;
	// Set the initial position of the camera.
	m_pCamera->SetPos(0.0f, 1.5f, -15.0f);

	D3DXMATRIX baseViewMatrix;
	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_pCamera->Render();
	m_pCamera->GetViewMatrix(baseViewMatrix);

	m_pTextureShader = new TextureShaderClass;
	if (!m_pTextureShader)
		return false;
	
	result = m_pTextureShader->Initialize(m_pD3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the plane object.
	m_pPlane = new GameObject;
	result = m_pPlane->InitializeForPlane(m_pD3D->GetDevice(), L"../Engine/data/Plane/PlaneTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	// Create the model object.
	m_pMonokumaModel = new GameObject;
	if (!m_pMonokumaModel)
		return false;
	//result = m_pMonokumaModel->InitializeForRectObj(m_pD3D->GetDevice(), L"../Engine/data/Moon/Moon 2K.obj", L"../Engine/data/Moon/Diffuse_2K.png");
	result = m_pMonokumaModel->Initialize(m_pD3D->GetDevice(), L"../Engine/data/Monokuma/Monokuma.obj", L"../Engine/data/Monokuma/kuma00_p4.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	iPolyCnt += (m_pPlane->GetVertexCount() / 3);
	iPolyCnt += (m_pMonokumaModel->GetVertexCount() / 3);

	// Create the text object.
	m_pText = new TextClass;
	if (!m_pText)
		return false;
	
	result = m_pText->Initialize(m_pD3D->GetDevice(), m_pD3D->GetDeviceContext(), hwnd, screenWidth,
		screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}
	
	// Set the Vertex .
	result = m_pText->SetSentence(iPolyCnt, m_pD3D->GetDeviceContext());
	if (!result)
		return false;

	// Create the light shader object.
	m_pLightShader = new LightShaderClass;
	if (!m_pLightShader)
		return false;
	
	// Initialize the light shader object.
	result = m_pLightShader->Initialize(m_pD3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_pLight = new LightClass;
	if (!m_pLight)
		return false;

	m_pLight->SetDirection(0.f, -1.f, 0.f);
	m_pLight->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.f);
	m_pLight->SetDiffuseColor(1.f, 1.f, 1.f, 1.f);
	m_pLight->SetSpecularColor(1.f, 1.f, 1.f, 1.f);
	m_pLight->SetSpecularPower(32.f);

	m_pGameObjectMgr = new GameObjectMgr;
	if (!m_pGameObjectMgr)
	{
		return false;
	}

	GameObject* pPlayer = new Player;
	dynamic_cast<Player*>(pPlayer)->InitBitmap(m_pD3D->GetDevice(), screenWidth, screenHeight, L"../Engine/data/Player/Player.png");
	dynamic_cast<Player*>(pPlayer)->Init(m_pCamera, m_pInputClass);
	iPolyCnt += (pPlayer->GetVertexCount() / 3);

	m_pGameObjectMgr->PushGameObject(pPlayer);


	GameObject* pMoon = new Planet;
	dynamic_cast<Planet*>(pMoon)->Init(10.f);
	pMoon->InitializeForRectObj(m_pD3D->GetDevice(), L"../Engine/data/Moon/Moon 2K.obj", L"../Engine/data/Moon/Diffuse_2K.png");
	iPolyCnt += (pMoon->GetVertexCount() / 3);
	m_pGameObjectMgr->PushGameObject(pMoon);

	GameObject* pMercury = new Planet;
	dynamic_cast<Planet*>(pMercury)->Init(50.f);
	pMercury->InitializeForRectObj(m_pD3D->GetDevice(), L"../Engine/data/Mercury/Mercury 1K.obj", L"../Engine/data/Mercury/Diffuse_1K.png");
	iPolyCnt += (pMercury->GetVertexCount() / 3);
	m_pGameObjectMgr->PushGameObject(pMercury);

	GameObject* pVenus = new Planet;
	dynamic_cast<Planet*>(pVenus)->Init(110.f);
	pVenus->InitializeForRectObj(m_pD3D->GetDevice(), L"../Engine/data/Venus/Venus_1K.obj", L"../Engine/data/Venus/Atmosphere_2K.png");
	iPolyCnt += (pVenus->GetVertexCount() / 3);
	m_pGameObjectMgr->PushGameObject(pVenus);

	GameObject* pEarth = new Planet;
	dynamic_cast<Planet*>(pEarth)->Init(210.f);
	pEarth->InitializeForRectObj(m_pD3D->GetDevice(), L"../Engine/data/Earth/Earth 2K.obj", L"../Engine/data/Earth/Diffuse_2K.png");
	iPolyCnt += (pEarth->GetVertexCount() / 3);
	m_pGameObjectMgr->PushGameObject(pEarth);

	GameObject* pMars = new Planet;
	dynamic_cast<Planet*>(pMars)->Init(410.f);
	pMars->InitializeForRectObj(m_pD3D->GetDevice(), L"../Engine/data/Mars/Mars 2K.obj", L"../Engine/data/Mars/Diffuse_2K.png");
	iPolyCnt += (pMars->GetVertexCount() / 3);
	m_pGameObjectMgr->PushGameObject(pMars);

	GameObject* pJupiter = new Planet;
	dynamic_cast<Planet*>(pJupiter)->Init(700.f, 0.3f);
	pJupiter->InitializeForRectObj(m_pD3D->GetDevice(), L"../Engine/data/Jupiter/13905_Jupiter_V1_l3.obj", L"../Engine/data/Jupiter/Jupiter_diff.jpg");
	iPolyCnt += (pJupiter->GetVertexCount() / 3);
	m_pGameObjectMgr->PushGameObject(pJupiter);


	m_pGameObjectMgr->PushGameObject(m_pPlane);
	m_pGameObjectMgr->PushGameObject(m_pMonokumaModel);
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}
	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_pD3D->GetDevice(), screenWidth, screenHeight,
		L"../Engine/data/Player/Player.png", 200, 200);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	// Release the text object.
	if (m_pText)
	{
		m_pText->Shutdown();
		delete m_pText;
		m_pText = 0;
	}

	// Release the light object.
	if (m_pLight)
	{
		delete m_pLight;
		m_pLight = 0;
	}
	// Release the light shader object.
	if (m_pLightShader)
	{
		m_pLightShader->Shutdown();
		delete m_pLightShader;
		m_pLightShader = 0;
	}
	if (m_pTextureShader)
	{
		m_pTextureShader->Shutdown();
		delete m_pTextureShader;
		m_pTextureShader = 0;
	}
	// Release the camera object.
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = 0;
	}

	if (m_pD3D)
	{
		m_pD3D->Shutdown();
		delete m_pD3D;
		m_pD3D = 0;
	}

	if (m_pGameObjectMgr)
	{
		m_pGameObjectMgr->Shutdown();
		delete m_pGameObjectMgr;
		m_pGameObjectMgr = 0;
	}

	return;
}

bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;

	static float rotation = 0.0f;
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.0005f * frameTime;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_pText->SetFps(fps, m_pD3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_pText->SetCpu(cpu, m_pD3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	
	// Render the graphics scene. 
	result = m_pGameObjectMgr->Frame(frameTime);

	result = Render();
	if(!result)
	{ 
		return false; 
	} 

	return true;
}

void GraphicsClass::SetInputClass(InputClass * InputClass)
{
	m_pInputClass = InputClass;
}

void GraphicsClass::MoveCamera(float frametime)
{

}

bool GraphicsClass::Render()
{
	// Clear the buffers to begin the scene.
	m_pD3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_pGameObjectMgr->Render(m_pD3D, m_pLightShader, m_pTextureShader, m_pCamera, m_pLight);
	
	RenderText();

	// Present the rendered scene to the screen.  
	m_pD3D->EndScene(); 
	
	return true;
}

bool GraphicsClass::RenderText()
{
	bool result;

	D3DXMATRIX worldMatrix, orthoMatrix;
	m_pD3D->GetWorldMatrix(worldMatrix);
	m_pD3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_pD3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_pD3D->TurnOnAlphaBlending();
	
	// Render the text strings.
	result = m_pText->Render(m_pD3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	// Turn off alpha blending after rendering the text.
	m_pD3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_pD3D->TurnZBufferOn();

	return true;
}
