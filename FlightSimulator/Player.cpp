#include "Player.h"

#include "D3DClass.h"
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
	m_pCockpit = 0;
	m_pEffect = 0;
	m_pCamera = 0;
	m_pInput = 0;
}

void Player::Init(CameraClass *pCamera, InputClass *pInput)
{
	m_pInput = pInput;
	m_pCamera = pCamera;
	m_pCamera->SetPos(650.f, 0.f, -600.f);

	m_eTag = TAG_PLAYER;
}

void Player::InitCockPit(ID3D11Device *device, WCHAR * wstrFileName)
{
	m_pCockpit = new ModelClass;
	m_pCockpit->Initialize(device, L"../Engine/data/Player/Player.png");

	m_pEffect = new ModelClass;
	m_pEffect->Initialize(device, L"../Engine/data/Player/Damage.png");
}

bool Player::Frame(float fFrameTime)
{
	Move(fFrameTime);

	if (m_bRenderEffect)
	{
		if (m_fAlpha < 0.f)
		{
			m_fAlpha = 0.f;
			m_fStayTime = 0.f;
			m_bReverse = false;
			m_bRenderEffect = false;

			return true;
		}

		if (m_fAlpha >= 1.f)
			m_bReverse = true;

		if (m_bReverse)
		{
			m_fStayTime += fFrameTime * 0.001f;

			if(m_fStayTime > 3.f)
				m_fAlpha -= fFrameTime * 0.005f;
		}
		else
			m_fAlpha += fFrameTime * 0.005f;
	}

	if (m_pInput->KeyDown(DIK_1))
		m_bRenderEffect = !m_bRenderEffect;

	return true;
}

void Player::Render(D3DClass * pD3D, LightShaderClass * pLightShader, LightClass * pLight)
{
	m_pCamera->Render();

	if(m_bRenderEffect)
		RenderEffect(pD3D, pLightShader, pLight);

	RenderCockpit(pD3D, pLightShader, pLight);
}

void Player::RenderCockpit(D3DClass* pD3D, LightShaderClass* pLightShader, LightClass* pLight)
{
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 0.7f, 0.5f, 0.7f);
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

void Player::RenderEffect(D3DClass* pD3D, LightShaderClass* pLightShader, LightClass* pLight)
{
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 0.6f, 0.5f, 0.6f);
	D3DXVECTOR3 vDir = { m_pCamera->GetLook().x, m_pCamera->GetLook().y, m_pCamera->GetLook().z };
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXMATRIX matBill = m_pCamera->GetView();
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	matBill = matScale * matBill;
	matBill._41 = m_matWorld._41 + vDir.x*1.2f;
	matBill._42 = m_matWorld._42 + vDir.y*1.2f;
	matBill._43 = m_matWorld._43 + vDir.z*1.2f;

	pLight->SetAmbientColor(0.3f*m_fAlpha, 0.3f*m_fAlpha, 0.3f*m_fAlpha, m_fAlpha);

	pD3D->TurnOnAlphaBlending();
	
	m_pEffect->Render(pD3D->GetDeviceContext());
	pLightShader->Render(pD3D->GetDeviceContext(), m_pEffect->GetIndexCount(), matBill, m_pCamera->GetView(),
		pD3D->GetProj(), m_pEffect->GetTexture(), pLight->GetDirection(), pLight->GetAmbientColor(),
		pLight->GetDiffuseColor(), m_pCamera->GetPos(), pLight->GetSpecularColor(), pLight->GetSpecularPower());

	pD3D->TurnOffAlphaBlending();

	pLight->SetAmbientColor(0.3f, 0.3f, 0.3f, 1.f);
}

void Player::Shutdown()
{
	if (m_pCockpit)
	{
		delete m_pCockpit;
		m_pCockpit = 0;
	}

	if (m_pEffect)
	{
		delete m_pEffect;
		m_pEffect = 0;
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
		m_pCamera->MoveCamera(CameraClass::MOVE_LEFT, fFrameTime* m_fRotSpeed[0] * 100000.f);
	}
	else
		CheckSpeed(CameraClass::MOVE_LEFT, fFrameTime, true);


	if (m_pInput->KeyPressing(DIK_D))
	{
		CheckSpeed(CameraClass::MOVE_RIGHT, fFrameTime);
		m_pCamera->MoveCamera(CameraClass::MOVE_RIGHT, fFrameTime* m_fRotSpeed[1] * -100000.f);
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

			m_fSpeed -= fFrameTime * 0.002f;
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
			if (m_fRotSpeed[0] <= 0)
			{
				m_fRotSpeed[0] = 0;
				return;
			}

			m_fRotSpeed[0] -= fFrameTime * 0.0000001f;
			m_pCamera->RotateCamera(CameraClass::MOVE_RIGHT, -m_fRotSpeed[0]);
		}
		else
		{
			if (m_fRotSpeedLimit[1] <= m_fRotSpeed[0])
			{
				m_fRotSpeed[0] = m_fRotSpeedLimit[1];
				return;
			}

			m_fRotSpeed[0] += fFrameTime * 0.0000001f;
			m_pCamera->RotateCamera(CameraClass::MOVE_RIGHT, m_fRotSpeed[0]);
		}
	}
	else if (eMove == CameraClass::MOVE_RIGHT)
	{
		if (bCheck)
		{
			if (m_fRotSpeed[1] >= 0)
			{
				m_fRotSpeed[1] = 0;
				return;
			}

			m_fRotSpeed[1] += fFrameTime * 0.0000001f;
			m_pCamera->RotateCamera(CameraClass::MOVE_RIGHT, -m_fRotSpeed[1]);
		}
		else
		{
			if (m_fRotSpeedLimit[0] >= m_fRotSpeed[1])
			{
				m_fRotSpeed[1] = m_fRotSpeedLimit[0];
				return;
			}

			m_fRotSpeed[1] -= fFrameTime * 0.0000001f;
			m_pCamera->RotateCamera(CameraClass::MOVE_RIGHT, m_fRotSpeed[1]);
		}
	}
}
