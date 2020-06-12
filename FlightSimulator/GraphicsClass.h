#pragma once

#include <windows.h>
#include "D3DClass.h"

#include <list>
using namespace std;

#include "TextClass.h"
#include "CameraClass.h"
#include "LightShaderClass.h"
#include "InputClass.h"
#include "LightClass.h"

class CollisionMgr;
class GameObjectMgr;
class GameObject;

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
	TextClass* m_pText;
	InputClass* m_pInputClass;

	GameObjectMgr* m_pGameObjectMgr;
	CollisionMgr* m_pCollisionMgr;

	GameObject* m_pPlayer;
	list<GameObject*> m_plistAs;
};

