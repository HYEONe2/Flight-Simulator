#pragma once
#include "GameObject.h"

class D3DClass;
class LightShaderClass;
class LightClass;
class ModelClass;
class CameraClass;

class DistanceUI :
	public GameObject
{
public:
	DistanceUI();
	DistanceUI(DistanceUI&);
	virtual ~DistanceUI();

public:
	void SetCamera(CameraClass* pCamera) { m_pCamera = pCamera; }
	void SetPlayer(GameObject* pPlayer) { m_pPlayer = pPlayer; }

public:
	void Init();
	void Init(D3DClass*);

	virtual bool Frame(float);
	void Render(D3DClass*, LightShaderClass*, LightClass*);

private:
	void Shutdown();

private:
	CameraClass* m_pCamera;
	GameObject* m_pPlayer;

	ModelClass* m_pDistance;
	D3DXMATRIX m_matSubWorld;
};

