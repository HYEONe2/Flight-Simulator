#pragma once

#include <windows.h>
#include "D3DClass.h"

#include <list>
using namespace std;

#include "InputClass.h"
#include "TextClass.h"
#include "CameraClass.h"
#include "LightShaderClass.h"
#include "LightClass.h"
#include "TextureShaderClass.h"

class SoundClass;
class CollisionMgr;
class GameObjectMgr;
class GameObject;

// Globals
const bool FULL_SCREEN = false;
// 주사율을 맞춰주는 것
const bool VSYNC_ENABLED = false; 
const float SCREEN_DEPTH = 2500.f;
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
	InputClass* m_pInputClass;
	CameraClass* m_pCamera;
	TextClass* m_pText;

	LightShaderClass* m_pLightShader;
	LightClass* m_pLight;
	TextureShaderClass* m_pTextureShader;

	GameObjectMgr* m_pGameObjectMgr;
	GameObject* m_pPlayer;

	CollisionMgr* m_pCollisionMgr;
	list<GameObject*> m_plistAs;

	SoundClass* m_pHitSound;
};

