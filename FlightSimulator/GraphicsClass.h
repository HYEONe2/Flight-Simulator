#pragma once
#define MAX_ASTEROID 5

#include <windows.h>
#include "D3DClass.h"

#include "TextClass.h"
#include "BitmapClass.h"
#include "CameraClass.h"
#include "LightShaderClass.h"
#include "TextureShaderClass.h"
#include "InputClass.h"
#include "LightClass.h"
#include <list>
using namespace std;

class GameObjectMgr;
class GameObject;
class CollisionMgr;

// Globals
const bool FULL_SCREEN = false;
// 주사율을 맞춰주는 것
const bool VSYNC_ENABLED = false; 
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
	
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, float);

	void SetInputClass(InputClass*);
	void MoveCamera(float);

private:
	bool Render();
	bool RenderText();

private:
	D3DClass* m_pD3D;
	CameraClass* m_pCamera;
	LightShaderClass* m_pLightShader;
	LightClass* m_pLight;
	TextureShaderClass* m_pTextureShader;
	TextClass* m_pText;
	InputClass* m_pInputClass;

	GameObject* m_pPlane;
	GameObject* m_pMonokumaModel;

	GameObjectMgr* m_pGameObjectMgr;
	CollisionMgr* m_pCollisionMgr;

	BitmapClass* m_Bitmap;

	list<GameObject*> m_plistAs;

};

