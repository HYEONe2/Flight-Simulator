#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::Init(COLLISION_TAG _eColltag, const D3DXVECTOR3 _vPos, const float _fRadius)
{
	m_eColTag = _eColltag;
	m_vPos = _vPos;
	m_fRadius = _fRadius;
}

void Collision::UpdatePos(D3DXVECTOR3 _vPos)
{
	m_vPos = _vPos;
}




