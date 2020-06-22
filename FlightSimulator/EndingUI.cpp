#include "EndingUI.h"

#include "D3DClass.h"
#include "CameraClass.h"
#include "TextureShaderClass.h"

#include <iostream>
using namespace std;

EndingUI::EndingUI()
{
	Init();
}

EndingUI::EndingUI(EndingUI &)
{
}

EndingUI::~EndingUI()
{
	Shutdown();
}

void EndingUI::Init()
{
	m_eTag = TAG_ENDINGUI;
}

void EndingUI::Init(D3DClass *pD3D)
{
	m_pFail = new ModelClass;
	m_pFail->Initialize(pD3D->GetDevice(), L"../Engine/data/UI/EndingFail.png");
}

bool EndingUI::Frame(float fFrameTime)
{
	return true;
}

void EndingUI::Render(D3DClass * pD3D, TextureShaderClass * pTextureShader)
{
	if (!m_bRender)
		return;

	if (m_bIsSuccess)
	{
		D3DXMATRIX matScale, matTrans, matWorld;

		D3DXVECTOR3 vPlayerPos = m_pCamera->GetPos();
		D3DXVECTOR3 vDir = { m_pCamera->GetLook().x, m_pCamera->GetLook().y, m_pCamera->GetLook().z };
		D3DXVec3Normalize(&vDir, &vDir);

		D3DXMATRIX matBill = m_pCamera->GetView();
		D3DXMatrixInverse(&matBill, NULL, &matBill);
		matBill._41 = vPlayerPos.x + vDir.x * 0.77f;
		matBill._42 = vPlayerPos.y + vDir.y * 0.77f;
		matBill._43 = vPlayerPos.z + vDir.z * 0.77f;

		D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);
		m_matWorld = matScale * matBill;

		dynamic_cast<ModelClass*>(this)->Render(pD3D->GetDeviceContext());
		pTextureShader->Render(pD3D->GetDeviceContext(), dynamic_cast<ModelClass*>(this)->GetIndexCount(), m_matWorld, m_pCamera->GetView(),
			pD3D->GetProj(), dynamic_cast<ModelClass*>(this)->GetTexture());
	}
	else
	{
		D3DXMATRIX matScale, matTrans, matWorld;

		D3DXVECTOR3 vPlayerPos = m_pCamera->GetPos();
		D3DXVECTOR3 vDir = { m_pCamera->GetLook().x, m_pCamera->GetLook().y, m_pCamera->GetLook().z };
		D3DXVec3Normalize(&vDir, &vDir);

		D3DXMATRIX matBill = m_pCamera->GetView();
		D3DXMatrixInverse(&matBill, NULL, &matBill);
		matBill._41 = vPlayerPos.x + vDir.x * 0.78f;
		matBill._42 = vPlayerPos.y + vDir.y * 0.78f;
		matBill._43 = vPlayerPos.z + vDir.z * 0.78f;

		D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);
		m_matWorld = matScale * matBill;

		m_pFail->Render(pD3D->GetDeviceContext());
		pTextureShader->Render(pD3D->GetDeviceContext(), m_pFail->GetIndexCount(), m_matWorld, m_pCamera->GetView(),
			pD3D->GetProj(), m_pFail->GetTexture());
	}
}

void EndingUI::Shutdown()
{
}
