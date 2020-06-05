#pragma once

#include <d3d11.h>
#include <list>
using namespace std;

class D3DClass;
class GameObject;
class CameraClass;
class LightClass;
class LightShaderClass;
class TextureShaderClass;

class GameObjectMgr
{
public:
	GameObjectMgr();
	GameObjectMgr(const GameObjectMgr&);
	~GameObjectMgr();

public:
	bool PushGameObject(GameObject* pGameObject);
	
	bool Frame(float);
	void Render(D3DClass*, LightShaderClass*, TextureShaderClass*, CameraClass*, LightClass*);
	
	void EraseGameObject(GameObject* pGameObject);
	void Shutdown();

private:
	list<GameObject*> m_GameObjectLst;
};

