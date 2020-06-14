#include "DistanceUI.h"

#include "D3DClass.h"
#include "LightShaderClass.h"
#include "LightClass.h"
#include "CameraClass.h"

#include <iostream>
using namespace std;

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

void DistanceUI::SetOriginDist(D3DXVECTOR3 vOriginPos, D3DXVECTOR3 vMoonPos)
{
	m_vMoonPos = vMoonPos;
	m_fOriginDist = sqrtf(pow((vMoonPos.x - vOriginPos.x), 2) + pow((vMoonPos.y - vOriginPos.y), 2) + pow((vMoonPos.z - vOriginPos.z), 2));
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

bool DistanceUI::Frame(float fFrameTime)
{
	m_vPlayerPos = m_pPlayer->GetPos();
	float fDist = sqrtf(pow((m_vMoonPos.x - m_vPlayerPos.x), 2) + pow((m_vMoonPos.y - m_vPlayerPos.y), 2) + pow((m_vMoonPos.z - m_vPlayerPos.z), 2));

	m_fRate = fDist / m_fOriginDist;

	return false;
}

void DistanceUI::Render(D3DClass * pD3D, LightShaderClass * pLightShader, LightClass * pLight)
{
	D3DXMATRIX matScale, matTrans, matWorld;

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

	if (m_fRate < 0.01f)
		m_fRate = 0.f;
	if (m_fRate >= 1.f)
		m_fRate = 1.f;

	matWorld = m_matWorld;
	matWorld._41 = matBill._41 -0.2f;
	//matWorld._42 = matBill._42 /*-0.1f*/;
	cout << matWorld._43 << endl;
	matWorld._43 = matWorld._43 -0.1f;
	D3DXMatrixTranslation(&matTrans, 1.01f, 0, -0.001f);
	D3DXMatrixScaling(&matScale, 0.88f * (1.f - m_fRate), 0.9f, 0.9f);
	m_matSubWorld = matTrans * matScale * matWorld;
	
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
