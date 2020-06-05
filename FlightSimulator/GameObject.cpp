#include "GameObject.h"

GameObject::GameObject()
{
	Init();
}

GameObject::GameObject(const GameObject & other)
{
}

GameObject::~GameObject()
{
	Shutdown();
}

void GameObject::SetPos(D3DXVECTOR3 vPos)
{
	m_matWorld._41 = vPos.x;
	m_matWorld._42 = vPos.y;
	m_matWorld._43 = vPos.z;
}

void GameObject::SetRight(D3DXVECTOR3 vRight)
{
	m_matWorld._11 = vRight.x;
	m_matWorld._12 = vRight.y;
	m_matWorld._13 = vRight.z;
}

void GameObject::SetUp(D3DXVECTOR3 vUp)
{
	m_matWorld._21 = vUp.x;
	m_matWorld._22 = vUp.y;
	m_matWorld._23 = vUp.z;
}

void GameObject::SetLook(D3DXVECTOR3 vLook)
{
	m_matWorld._31 = vLook.x;
	m_matWorld._32 = vLook.y;
	m_matWorld._33 = vLook.z;
}

void GameObject::Init()
{
	D3DXMatrixIdentity(&m_matWorld);
}

bool GameObject::Frame(float fFrameTime)
{
	return false;
}

void GameObject::Shutdown()
{

}

