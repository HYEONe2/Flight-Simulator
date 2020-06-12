#include "DistanceUI.h"

#include "D3DClass.h"
#include "LightShaderClass.h"
#include "LightClass.h"
#include "CameraClass.h"

DistanceUI::DistanceUI()
{
	Init();
}

DistanceUI::DistanceUI(DistanceUI &)
{
}

DistanceUI::~DistanceUI()
{
	Shutdown();
}

void DistanceUI::Init()
{
	m_pDistance = 0;

	m_eTag = TAG_UI;
}

void DistanceUI::Init(D3DClass * pD3D)
{
	m_pDistance = new ModelClass;
	m_pDistance->Initialize(pD3D->GetDevice(), L"../Engine/data/UI/Distance.png");
}

bool DistanceUI::Frame(float)
{
	D3DXMATRIX matScale, matTrans;
	
	D3DXVECTOR3 vPlayerPos = m_pPlayer->GetPos();
	D3DXVECTOR3 vDir = { m_pCamera->GetLook().x, m_pCamera->GetLook().y, m_pCamera->GetLook().z };
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXMATRIX matBill = m_pCamera->GetView();
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	matBill._41 = vPlayerPos.x + vDir.x * 0.8f;
	matBill._42 = vPlayerPos.y + vDir.y * 0.8f;
	matBill._43 = vPlayerPos.z + vDir.z * 0.8f;

	D3DXMatrixTranslation(&matTrans, 0, -14.5f, 0);
	D3DXMatrixScaling(&matScale, 0.4f, 0.02f, 0.4f);
	m_matWorld = matTrans * matScale * matBill;

	D3DXMatrixTranslation(&matTrans, 0.015f, 0, -0.001f);
	D3DXMatrixScaling(&matScale, 0.88f, 0.9f, 0.9f);
	m_matSubWorld = matTrans* matScale * m_matWorld;

	return false;
}

void DistanceUI::Render(D3DClass * pD3D, LightShaderClass * pLightShader, LightClass * pLight)
{
	m_pDistance->Render(pD3D->GetDeviceContext());
	pLightShader->Render(pD3D->GetDeviceContext(), m_pDistance->GetIndexCount(), m_matSubWorld, m_pCamera->GetView(),
		pD3D->GetProj(), m_pDistance->GetTexture(), pLight->GetDirection(), pLight->GetAmbientColor(),
		pLight->GetDiffuseColor(), m_pCamera->GetPos(), pLight->GetSpecularColor(), pLight->GetSpecularPower());
}

void DistanceUI::Shutdown()
{
	if (m_pDistance)
	{
		delete m_pDistance;
		m_pDistance = 0;
	}
}
