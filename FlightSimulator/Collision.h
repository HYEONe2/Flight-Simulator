#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
using namespace std;

class Collision
{
public:
	enum COLLISION_TAG {COL_PLAYER, COL_ASEROID, COL_END};

public:
	Collision();
	~Collision();
	void Init(COLLISION_TAG, const D3DXVECTOR3, const float);
	void UpdatePos(D3DXVECTOR3);
	//void Render(ID3D11DeviceContext * divceContext);

public:
	const COLLISION_TAG Get_Tag() { return m_eColTag; }
	const D3DXVECTOR3& Get_Pos() { return m_vPos; }
	float Get_Radius() { return m_fRadius; }

private:
	D3DXVECTOR3 m_vPos;
	float m_fRadius;
	COLLISION_TAG m_eColTag;
};
	

