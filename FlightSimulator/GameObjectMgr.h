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
	void Render(D3DClass*, CameraClass*, LightShaderClass*, LightClass*, TextureShaderClass*);
	
	void EraseGameObject(GameObject* pGameObject);
	void Shutdown();

	int Get_Size() { return m_GameObjectLst.size(); }
	int Get_PolySize();

private:
	list<GameObject*> m_GameObjectLst;
};

