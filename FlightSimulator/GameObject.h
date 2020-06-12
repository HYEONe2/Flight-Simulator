#pragma once
#include "ModelClass.h"

class GameObject :
	public ModelClass
{
public:
	enum TAG {TAG_SKYBOX, TAG_PLAYER, TAG_ASTEROID, TAG_END};

public:
	GameObject();
	GameObject(const GameObject&);
	virtual ~GameObject();

public:
	const TAG GetTag() { return m_eTag; }
	const D3DXMATRIX GetWorld() const { return m_matWorld; }

	void SetWorld(D3DXMATRIX matWorld) { m_matWorld = matWorld; }
	void SetRight(D3DXVECTOR3 vRight);
	void SetUp(D3DXVECTOR3 vUp);
	void SetLook(D3DXVECTOR3 vLook);
	void SetPos(D3DXVECTOR3 vPos);

	D3DXVECTOR3& GetRight() { return D3DXVECTOR3(m_matWorld._11, m_matWorld._12, m_matWorld._13); }
	D3DXVECTOR3& GetUp() { return D3DXVECTOR3(m_matWorld._21, m_matWorld._22, m_matWorld._23); }
	D3DXVECTOR3& GetLook() { return D3DXVECTOR3(m_matWorld._31, m_matWorld._32, m_matWorld._33); }
	D3DXVECTOR3& GetPos() { return D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43); }

public:
	void Init();
	virtual bool Frame(float);
	void Shutdown();

protected:
	D3DXMATRIX m_matWorld;
	TAG m_eTag;
};

