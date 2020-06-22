#pragma once
#include "GameObject.h"

class D3DClass;
class TextureShaderClass;
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
	void SetOriginDist(D3DXVECTOR3 vOriginPos, D3DXVECTOR3 vMoonPos);

public:
	void Init();
	void Init(D3DClass*);

	virtual bool Frame(float);
	void Render(D3DClass*, TextureShaderClass*);

private:
	void Shutdown();

private:
	CameraClass* m_pCamera;
	GameObject* m_pPlayer;

	ModelClass* m_pDistance;
	D3DXMATRIX m_matSubWorld;

	D3DXVECTOR3 m_vPlayerPos;
	D3DXVECTOR3 m_vMoonPos;

	float m_fOriginDist = 0;
	float m_fRate = 0;
};

