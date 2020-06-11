#include "Player.h"

#include "D3DClass.h"
#include "BitmapClass.h"
#include "InputClass.h"
#include "LightShaderClass.h"
#include "LightClass.h"

Player::Player()
{
	Init();
}

Player::Player(Player &)
{
}

Player::~Player()
{
	Shutdown();
}

void Player::Init()
{
	m_iScreenWidth = 0;
	m_iScreenHeight = 0;
}

void Player::Init(CameraClass *pCamera, InputClass *pInput)
{
	m_pInput = pInput;
	m_pCamera = pCamera;
	m_pCamera->SetPos( 650.f, 0.f, -600.f );
	
	m_eTag = TAG_PLAYER;
}

void Player::InitCockPit(ID3D11Device *device, WCHAR * wstrFileName)
{
	m_pCockpit = new ModelClass;
	m_pCockpit->Initialize(device, wstrFileName);
}

bool Player::Frame(float fFrameTime)
{
	Move(fFrameTime);

	return true;
}

void Player::RenderCockpit(D3DClass* pD3D, LightShaderClass* pLightShader, LightClass* pLight)
{
	m_pCamera->Render();

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 0.7f, 0.45f, 0.7f);
	D3DXVECTOR3 vDir = { m_pCamera->GetLook().x, m_pCamera->GetLook().y, m_pCamera->GetLook().z };
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXMATRIX matBill = m_pCamera->GetView();
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	matBill = matScale * matBill;
	matBill._41 = m_matWorld._41 + vDir.x;
	matBill._42 = m_matWorld._42 + vDir.y;
	matBill._43 = m_matWorld._43 + vDir.z;

	pD3D->TurnOnAlphaBlending();

	m_pCockpit->Render(pD3D->GetDeviceContext());
	pLightShader->Render(pD3D->GetDeviceContext(), m_pCockpit->GetIndexCount(), matBill, m_pCamera->GetView(),
		pD3D->GetProj(), m_pCockpit->GetTexture(), pLight->GetDirection(), pLight->GetAmbientColor(),
		pLight->GetDiffuseColor(), m_pCamera->GetPos(), pLight->GetSpecularColor(), pLight->GetSpecularPower());
	
	pD3D->TurnOffAlphaBlending();
}

void Player::Shutdown()
{
	if (m_pCockpit)
	{
		delete m_pCockpit;
		m_pCockpit = 0;
	}
}

void Player::Move(float fFrameTime)
{
	if (!m_pInput)
		return;

	if (m_pInput->KeyPressing(DIK_W))
	{
		CheckSpeed(CameraClass::MOVE_FORWARD, fFrameTime);
		m_pCamera->MoveCamera(CameraClass::MOVE_FORWARD, fFrameTime*m_fSpeed);
	}
	else
	{
		CheckSpeed(CameraClass::MOVE_FORWARD, fFrameTime, true);
		m_pCamera->MoveCamera(CameraClass::MOVE_FORWARD, fFrameTime*m_fSpeed);
	}

	if (m_pInput->KeyPressing(DIK_A))
	{
		CheckSpeed(CameraClass::MOVE_LEFT, fFrameTime);
		m_pCamera->MoveCamera(CameraClass::MOVE_LEFT, fFrameTime*0.5f);
	}
	else
		CheckSpeed(CameraClass::MOVE_LEFT, fFrameTime, true);


	if (m_pInput->KeyPressing(DIK_D))
	{
		CheckSpeed(CameraClass::MOVE_RIGHT, fFrameTime);
		m_pCamera->MoveCamera(CameraClass::MOVE_RIGHT, fFrameTime*0.5f);
	}
	else
		CheckSpeed(CameraClass::MOVE_RIGHT, fFrameTime, true);


	signed long	MouseMove = 0;

	if (MouseMove = m_pInput->GetDIMouseMove(InputClass::DIMM_X))
	{
		m_pCamera->MoveCamera(CameraClass::MOVE_MOUSEX, fFrameTime * 0.2f, MouseMove);
	}

	if (MouseMove = m_pInput->GetDIMouseMove(InputClass::DIMM_Y))
	{
		m_pCamera->MoveCamera(CameraClass::MOVE_MOUSEY, fFrameTime* 0.1f, MouseMove);
	}

	SetRight(m_pCamera->GetRight());
	SetUp(m_pCamera->GetUp());
	SetLook(m_pCamera->GetLook());
	SetPos(m_pCamera->GetPos());
}

void Player::CheckSpeed(CameraClass::MOVE eMove, float fFrameTime, bool bCheck)
{
	if (eMove == CameraClass::MOVE_FORWARD)
	{
		if (bCheck)
		{
			if (m_fSpeed <= 0)
				m_fSpeed = 0;

			m_fSpeed -= fFrameTime * 0.001f;
		}
		else
		{
			if (m_fSpeed >= m_fMaxSpeed)
			{
				m_fSpeed = m_fMaxSpeed;
				return;
			}
			m_fSpeed += fFrameTime * 0.002f;
		}
	}
	if (eMove == CameraClass::MOVE_LEFT)
	{
		if (bCheck)
		{
			if (m_fRotSpeedL <= 0)
			{
				m_fRotSpeedL = 0;
				return;
			}
			
			m_fRotSpeedL -= fFrameTime * 0.0000001f;
			m_pCamera->RotateCamera(CameraClass::MOVE_RIGHT, -m_fRotSpeedL);
		}
		else
		{
			if (m_fRotMaxSpeed <= m_fRotSpeedL)
			{
				m_fRotSpeedL = m_fRotMaxSpeed;
				return;
			}

			m_fRotSpeedL += fFrameTime * 0.0000001f;
			m_pCamera->RotateCamera(CameraClass::MOVE_RIGHT, m_fRotSpeedL);
		}
	}
	else if (eMove == CameraClass::MOVE_RIGHT)
	{
		if (bCheck)
		{
			if (m_fRotSpeed >= 0)
			{
				m_fRotSpeed = 0;
				return;
			}

			m_fRotSpeed += fFrameTime * 0.0000001f;
			m_pCamera->RotateCamera(CameraClass::MOVE_RIGHT, -m_fRotSpeed);
		}
		else
		{
			if (m_fRotMinSpeed >= m_fRotSpeed)
			{
				m_fRotSpeed = m_fRotMinSpeed;
				return;
			}

			m_fRotSpeed -= fFrameTime * 0.0000001f;
			m_pCamera->RotateCamera(CameraClass::MOVE_RIGHT, m_fRotSpeed);
		}
	}
}
