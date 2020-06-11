#include "Asteroid.h"
#include "Player.h"

#include <iostream>
using namespace std;

Asteroid::Asteroid()
{
	m_vPos = { 0.f,0.f,0.f };
	m_vDir = { -1.f,0.f,0.f };
	m_bIsCloser = false;
	Init();
}

Asteroid::Asteroid(Asteroid &)
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Init()
{
}

void Asteroid::Init(GameObject* _pPlayer, D3DXVECTOR3 _vPos)
{
	if (_pPlayer)
		m_pPlayer = _pPlayer;
	else
		return;

	m_vPos = _vPos;
}

bool Asteroid::Frame(float fFrameTime)
{
	Move(fFrameTime);
	return true;
}

void Asteroid::Shutdown()
{
}

void Asteroid::Move(float fFrameTime)
{	
	D3DXVECTOR3 vPlayerPos = m_pPlayer->GetPos();
	float fDist = D3DXVec3Length(&(vPlayerPos-m_vPos));
	//cout<<fDist<<endl;
	float fSpeed = 0.05f;
	if (fDist < 150.f) {
		if (!m_bIsCloser)
		{
			m_vDir = vPlayerPos - m_vPos;
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			m_bIsCloser = true;
		}
		m_vPos += m_vDir * fSpeed * fFrameTime;
	}
	else if(fDist >= 150.f)
		m_bIsCloser = false;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.00001f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	D3DXMATRIX  matTans, matRot, matScale;

	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationY(&matRot, rotation*30.f);
	D3DXMatrixTranslation(&matTans, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matWorld = matScale * matRot * matTans;
}
