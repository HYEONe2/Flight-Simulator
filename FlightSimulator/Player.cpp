#include "Player.h"

#include "D3DClass.h"
#include "BitmapClass.h"
#include "InputClass.h"
#include "TextureShaderClass.h"

#include <iostream>
using namespace std;

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
	m_pCamera = pCamera;
	m_pInput = pInput;
}

void Player::InitBitmap(ID3D11Device* device, int screenWidth, int screenHeight, WCHAR* textureFilename)
{
	if (m_pBitmap)
		return;

	m_iScreenWidth = screenWidth;
	m_iScreenHeight = screenHeight;

	m_pBitmap = new BitmapClass;
	m_pBitmap->Initialize(device, m_iScreenWidth, m_iScreenHeight, textureFilename);
}

bool Player::Frame(float fFrameTime)
{
	Move(fFrameTime);
	cout << m_fRotSpeed << endl;

	return true;
}

void Player::RenderBitmap(D3DClass* pD3D, TextureShaderClass* pTextureShader)
{
	if (!m_pBitmap)
		return;

	m_pCamera->Render();

	//pD3D->TurnZBufferOff();
	//pD3D->TurnOnAlphaBlending();

	//m_pBitmap->Render(pD3D->GetDeviceContext(), 0, 0);

	////D3DXMATRIX matBill;
	////D3DXMatrixIdentity(&matBill);
	////matBill = m_pCamera->GetView();
	////ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));
	////D3DXMatrixInverse(&matBill, 0, &matBill);
	////matBill = matBill * m_matWorld;
	//pTextureShader->Render(pD3D->GetDeviceContext(), m_pBitmap->GetIndexCount(),
	//	m_matWorld, m_pCamera->GetView(), pD3D->GetOrtho(), m_pBitmap->GetTexture());

	//pD3D->TurnOffAlphaBlending();
	//pD3D->TurnZBufferOn();
}

void Player::Shutdown()
{
	if (m_pBitmap)
	{
		m_pBitmap->Shutdown();
		delete m_pBitmap;
		m_pBitmap = 0;
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
		m_pCamera->MoveCamera(CameraClass::MOVE_MOUSEX, fFrameTime * 0.1f, MouseMove);
	}

	if (MouseMove = m_pInput->GetDIMouseMove(InputClass::DIMM_Y))
	{
		m_pCamera->MoveCamera(CameraClass::MOVE_MOUSEY, fFrameTime* 0.1f, MouseMove);
	}

	m_matWorld._41 = m_pCamera->GetPos().x;
	m_matWorld._42 = m_pCamera->GetPos().y;
	m_matWorld._43 = m_pCamera->GetPos().z;
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
