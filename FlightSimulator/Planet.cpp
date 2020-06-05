#include "Planet.h"

Planet::Planet()
{
	Init();
	m_fDist = 0.f;
	m_fScale = 10.f;
}

Planet::Planet(Planet &)
{
}

Planet::~Planet()
{
}

void Planet::Init()
{
}
void Planet::Init(float _fDist, float _scale)
{
	m_fDist = _fDist;
	m_fScale = _scale;
}
bool Planet::Frame(float fFrameTime)
{
	Move(fFrameTime);
	return true;
}
void Planet::Shutdown()
{
}


void Planet::Move(float fFrameTime)
{
	static float rotation = 0.0f;
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.00001f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	D3DXMATRIX  matTans, matRot, matRev, matScale;

	D3DXMatrixScaling(&matScale, m_fScale, m_fScale, m_fScale);
	D3DXMatrixRotationY(&matRot, rotation);
	D3DXMatrixRotationY(&matRev, rotation* m_fDist*0.04f);
	if (m_fScale < 10.f)
		D3DXMatrixRotationY(&matRev, rotation* m_fDist*0.004f);
	D3DXMatrixTranslation(&matTans, m_fDist, 0.f, 0.f);


	m_matWorld = matScale * matRot * matTans * matRev;
}
