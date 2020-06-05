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

