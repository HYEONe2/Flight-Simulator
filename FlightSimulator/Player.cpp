#include "Player.h"

#include "D3DClass.h"
#include "BitmapClass.h"
#include "CameraClass.h"
#include "InputClass.h"
#include "TextureShaderClass.h"

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

	m_pBitmap = new BitmapClass;
	m_pBitmap->Initialize(device, screenWidth, screenHeight, textureFilename);
}

bool Player::Frame(float fFrameTime)
{
	Move(fFrameTime);

	return true;
}

void Player::RenderBitmap(D3DClass* pD3D, TextureShaderClass* pTextureShader)
{
	if (!m_pBitmap)
		return;

	m_pCamera->Render();

	pD3D->TurnZBufferOff();

	m_pBitmap->Render(pD3D->GetDeviceContext(), 0, 0);
	pTextureShader->Render(pD3D->GetDeviceContext(), m_pBitmap->GetIndexCount(),
		m_matWorld, m_pCamera->GetView(), m_pCamera->GetOrtho(), m_pBitmap->GetTexture());

	pD3D->TurnZBufferOn();
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
		m_pCamera->MoveCamera(CameraClass::MOVE_FORWARD, fFrameTime);
	}

	if (m_pInput->KeyPressing(DIK_S))
	{
		m_pCamera->MoveCamera(CameraClass::MOVE_BACKWARD, fFrameTime);
	}

	if (m_pInput->KeyPressing(DIK_A))
	{
		m_pCamera->MoveCamera(CameraClass::MOVE_LEFT, fFrameTime);
	}

	if (m_pInput->KeyPressing(DIK_D))
	{
		m_pCamera->MoveCamera(CameraClass::MOVE_RIGHT, fFrameTime);
	}

	signed long	MouseMove = 0;

	if (MouseMove = m_pInput->GetDIMouseMove(InputClass::DIMM_X))
	{
		m_pCamera->MoveCamera(CameraClass::MOVE_MOUSEX, fFrameTime, MouseMove);
	}

	if (MouseMove = m_pInput->GetDIMouseMove(InputClass::DIMM_Y))
	{
		m_pCamera->MoveCamera(CameraClass::MOVE_MOUSEY, fFrameTime, MouseMove);
	}

	m_matWorld._41 = m_pCamera->GetPos().x;
	m_matWorld._42 = m_pCamera->GetPos().y;
	m_matWorld._43 = m_pCamera->GetPos().z;
}
