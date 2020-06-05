#pragma once

#include <d3dx10math.h>

class CameraClass
{
public:
	enum MOVE{MOVE_FORWARD, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT, MOVE_MOUSEX, MOVE_MOUSEY, MOVE_END};

public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetRotation(float, float, float);
	void SetPos(float, float, float);
	void SetLook(float, float, float);
	void SetUp(float, float, float);
	void SetRight(float, float, float);

	const D3DXVECTOR3 GetRight()& { return D3DXVECTOR3(m_fRightX, m_fRightY, m_fRightZ); }
	const D3DXVECTOR3 GetUp()& { return D3DXVECTOR3(m_fUpX, m_fUpY, m_fUpZ); }
	const D3DXVECTOR3 GetLook()& { return D3DXVECTOR3(m_fLookAtX, m_fLookAtY, m_fLookAtZ); }
	const D3DXVECTOR3 GetPos()& { return D3DXVECTOR3(m_fPositionX, m_fPositionY, m_fPositionZ); }

	D3DXVECTOR3 GetRotation();
	void GetViewMatrix(D3DXMATRIX&);
	const D3DXMATRIX& GetView() { return m_matView; }

	void MoveCamera(MOVE, float, signed long = 0);
	void RotateCamera(MOVE, float);
	void Render();

private:
	float m_fRotationX, m_fRotationY, m_fRotationZ;
	float m_fPositionX, m_fPositionY, m_fPositionZ;
	float m_fLookAtX, m_fLookAtY, m_fLookAtZ;
	float m_fUpX, m_fUpY, m_fUpZ;
	float m_fRightX, m_fRightY, m_fRightZ;
	D3DXMATRIX m_matOrigin;

	D3DXMATRIX m_matView;
};