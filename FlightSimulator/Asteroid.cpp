#include "Asteroid.h"
#include "Player.h"
#include "Collision.h"

#include <iostream>
using namespace std;

Asteroid::Asteroid()
{
	m_vPos = { 0.f,0.f,0.f };
	m_vDir = { -1.f,0.f,0.f };
	m_bIsCloser = false;
	Init();
	m_fDist = 0.f;
}

Asteroid::Asteroid(Asteroid &)
{
}

Asteroid::~Asteroid()
{
	Shutdown();
}

void Asteroid::Init()
{
}

void Asteroid::Init(D3DXVECTOR3 _vPos)
{
	m_vPos = _vPos;
	m_pCollision = new Collision;
	m_pCollision->Init(Collision::COL_ASEROID, _vPos, 10.0f);
	cout << m_vPos.x << "," << m_vPos.y << endl;
	m_eTag = TAG_ASTEROID;
	m_fDist = (rand() % 10)*1.f;
}

bool Asteroid::Frame(float fFrameTime)
{
	Move(fFrameTime);
	if (m_pCollision)
		m_pCollision->UpdatePos(m_vPos);
	
	return true;
}

void Asteroid::Shutdown()
{

}

void Asteroid::Set_Player(GameObject* _pPlayer)
{
	if (_pPlayer)
		m_pPlayer = _pPlayer;
	else
		return;
}

Collision* Asteroid::Get_Collision()
{
	return m_pCollision;
}

void Asteroid::Move(float fFrameTime)
{
	D3DXVECTOR3 vPlayerPos = m_pPlayer->GetPos();
	float fDist = D3DXVec3Length(&(vPlayerPos - m_vPos));
	//cout<<fDist<<endl;
	float fSpeed = 0.07f;
	if (fDist < 150.f) {
		if (!m_bIsCloser)
		{
			m_vDir = vPlayerPos - m_vPos;
			D3DXVec3Normalize(&m_vDir, &m_vDir);
			m_bIsCloser = true;
		}
		if (fDist < 50.f)
			fSpeed = 0.09f;
		m_vPos += m_vDir * fSpeed * fFrameTime;
	}
	else if (fDist >= 150.f) {
		m_bIsCloser = false;
		if (m_bIsdown) {
			if (m_fDist > 10.f)
				m_bIsdown = false;
			m_fDist+=0.01f;
		}
		else {
			if (m_fDist < -10.f)
				m_bIsdown = true;
			m_fDist-=0.01f;
		}
	}

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.00001f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	D3DXMATRIX  matTans, matRot, matScale;

	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationZ(&matRot, rotation);
	D3DXMatrixTranslation(&matTans, m_vPos.x - 7.5f, m_vPos.y+m_fDist, m_vPos.z);

	m_matWorld = matScale  * matRot * matTans;
}
