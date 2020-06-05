#include "CameraClass.h"

CameraClass::CameraClass()
{
	m_fPositionX = 0.f;
	m_fPositionY = 0.f;
	m_fPositionZ = 0.f;
	m_fRotationX = 0.0f;
	m_fRotationY = 0.0f;
	m_fRotationZ = 0.0f;
	m_fLookAtX = 0.0;
	m_fLookAtY = 0.0;
	m_fLookAtZ = 1.0;
	m_fUpX = 0.0f;
	m_fUpY = 1.0f;
	m_fUpZ = 0.0f;
	D3DXMatrixIdentity(&m_matOrigin);
}

CameraClass::CameraClass(const CameraClass& other)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPos(float x, float y, float z)
{
	m_fPositionX = x;
	m_fPositionY = y;
	m_fPositionZ = z;
	return;
}
void CameraClass::SetRotation(float x, float y, float z)
{
	m_fRotationX = x;
	m_fRotationY = y;
	m_fRotationZ = z;
	return;
}

void CameraClass::SetLook(float x, float y, float z)
{
	m_fLookAtX = x;
	m_fLookAtY = y;
	m_fLookAtZ = z;
}

void CameraClass::SetUp(float x, float y, float z)
{
	m_fUpX = x;
	m_fUpY = y;
	m_fUpZ = z;
}

void CameraClass::SetRight(float x, float y, float z)
{
	m_fRightX = x;
	m_fRightY = y;
	m_fRightZ = z;
}

D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(m_fRotationX, m_fRotationY, m_fRotationZ);
}

void CameraClass::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = m_fUpX;
	up.y = m_fUpY;
	up.z = m_fUpZ;

	// Setup the position of the camera in the world.
	position.x = m_fPositionX;
	position.y = m_fPositionY;
	position.z = m_fPositionZ;
	
	// Setup where the camera is looking by default.
	lookAt.x = m_fLookAtX;
	lookAt.y = m_fLookAtY;
	lookAt.z = m_fLookAtZ;
	
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_fRotationX * 0.0174532925f;
	yaw = m_fRotationY * 0.0174532925f;
	roll = m_fRotationZ * 0.0174532925f;
	
	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &D3DXVECTOR3(m_fUpX, m_fUpY, m_fUpZ), &D3DXVECTOR3(m_fLookAtX, m_fLookAtY, m_fLookAtZ));
	m_fRightX = vRight.x;
	m_fRightY = vRight.y;
	m_fRightZ = vRight.z;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	
	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;
	
	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_matView, &position, &lookAt, &up);
	return;
}

void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_matView;
	return;
}

void CameraClass::MoveCamera(MOVE eMove, float frametime, signed long MouseMove)
{
	switch (eMove)
	{
	case MOVE_FORWARD:
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(m_fPositionX, m_fPositionY, m_fPositionZ);
		D3DXVECTOR3 vLook = D3DXVECTOR3(m_fLookAtX, m_fLookAtY, m_fLookAtZ);

		vPos += *D3DXVec3Normalize(&vLook, &vLook) * frametime * 0.01f;

		SetPos(vPos.x, vPos.y, vPos.z);
	}
		break;
	case MOVE_BACKWARD:
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(m_fPositionX, m_fPositionY, m_fPositionZ);
		D3DXVECTOR3 vLook = D3DXVECTOR3(m_fLookAtX, m_fLookAtY, m_fLookAtZ);

		vPos -= *D3DXVec3Normalize(&vLook, &vLook) * frametime * 0.01f;

		SetPos(vPos.x, vPos.y, vPos.z);
	}
		break;
	case MOVE_LEFT:
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(m_fPositionX, m_fPositionY, m_fPositionZ);
		D3DXVECTOR3 vRight = D3DXVECTOR3(m_fRightX, m_fRightY, m_fRightZ);

		vPos -= *D3DXVec3Normalize(&vRight, &vRight) * frametime * 0.01f;

		SetPos(vPos.x, vPos.y, vPos.z);
	}
		break;
	case MOVE_RIGHT:
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(m_fPositionX, m_fPositionY, m_fPositionZ);
		D3DXVECTOR3 vRight = D3DXVECTOR3(m_fRightX, m_fRightY, m_fRightZ);

		vPos += *D3DXVec3Normalize(&vRight, &vRight) * frametime * 0.01f;

		SetPos(vPos.x, vPos.y, vPos.z);
	}
		break;
	case MOVE_MOUSEX:
	{
		D3DXMATRIX	RotationMatrix;
		D3DXMatrixRotationAxis(&RotationMatrix, &D3DXVECTOR3(0, 1.f, 0), 0.005f * frametime * MouseMove);

		D3DXVECTOR3 vRight = D3DXVECTOR3(m_fRightX, m_fRightY, m_fRightZ);
		D3DXVECTOR3	vUp = D3DXVECTOR3(m_fUpX, m_fUpY, m_fUpZ);
		D3DXVECTOR3	vLook = D3DXVECTOR3(m_fLookAtX, m_fLookAtY, m_fLookAtZ);

		D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
		D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
		D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

		SetRight(vRight.x, vRight.y, vRight.z);
		SetUp(vUp.x, vUp.y, vUp.z);
		SetLook(vLook.x, vLook.y, vLook.z);
	}
		break;
	case MOVE_MOUSEY:
	{
		D3DXVECTOR3 vRight = D3DXVECTOR3(m_fRightX, m_fRightY, m_fRightZ);

		D3DXMATRIX	RotationMatrix;
		D3DXMatrixRotationAxis(&RotationMatrix, &vRight, 0.005f * frametime * MouseMove);

		D3DXVECTOR3	vUp = D3DXVECTOR3(m_fUpX, m_fUpY, m_fUpZ);
		D3DXVECTOR3	vLook = D3DXVECTOR3(m_fLookAtX, m_fLookAtY, m_fLookAtZ);

		D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
		D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
		D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

		SetRight(vRight.x, vRight.y, vRight.z);
		SetUp(vUp.x, vUp.y, vUp.z);
		SetLook(vLook.x, vLook.y, vLook.z);
	}
		break;
	}
}

void CameraClass::RotateCamera(MOVE eMove, float fRotSpeed)
{
	D3DXVECTOR3 vLook = GetLook();

	D3DXMATRIX	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vLook, fRotSpeed);

	D3DXVECTOR3	vUp = GetUp();
	D3DXVECTOR3	vRight = GetRight();

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	SetRight(vRight.x, vRight.y, vRight.z);
	SetUp(vUp.x, vUp.y, vUp.z);
	SetLook(vLook.x, vLook.y, vLook.z);
}
