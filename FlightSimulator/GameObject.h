#pragma once
#include "ModelClass.h"

class GameObject :
	public ModelClass
{
public:
	GameObject();
	GameObject(const GameObject&);
	virtual ~GameObject();

public:
	const D3DXMATRIX GetWorld() const { return m_matWorld; }
	void SetWorld(D3DXMATRIX matWorld) { m_matWorld = matWorld; }

	void SetPos(D3DXVECTOR3 vPos) { memcpy(&m_matWorld.m[4], &vPos, sizeof(D3DXVECTOR3)); }
	void SetLook(D3DXVECTOR3 vLook) { memcpy(&m_matWorld.m[3], &vLook, sizeof(D3DXVECTOR3)); }

public:
	void Init();
	virtual bool Frame(float);
	void Shutdown();

protected:
	D3DXMATRIX m_matWorld;
};

