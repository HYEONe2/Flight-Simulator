#include "HpUI.h"

#include "D3DClass.h"
#include "LightShaderClass.h"
#include "LightClass.h"
#include "CameraClass.h"
#include "Player.h"

HpUI::HpUI()
{
	Init();
}

HpUI::HpUI(HpUI &)
{
}

HpUI::~HpUI()
{
	Shutdown();
}

void HpUI::Init()
{
	m_eTag = TAG_HPUI;
}

void HpUI::Init(D3DClass *pD3D)
{

}

bool HpUI::Frame(float fFrameTime)
{
	m_iPlayerHp = dynamic_cast<Player*>(m_pPlayer)->GetHp();

	return true;
}

void HpUI::Render(D3DClass * pD3D, LightShaderClass * pLightShader, LightClass * pLight)
{
	D3DXMATRIX matScale, matTrans, matWorld;

	D3DXVECTOR3 vPlayerPos = m_pPlayer->GetPos();
	D3DXVECTOR3 vDir = { m_pCamera->GetLook().x, m_pCamera->GetLook().y, m_pCamera->GetLook().z };
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXMATRIX matBill = m_pCamera->GetView();
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	matBill._41 = vPlayerPos.x + vDir.x * 0.789f;
	matBill._42 = vPlayerPos.y + vDir.y * 0.789f;
	matBill._43 = vPlayerPos.z + vDir.z * 0.789f;

	D3DXMatrixScaling(&matScale, 0.02f, 0.02f, 0.02f);

	pD3D->TurnOnAlphaBlending();

	for (int i = 0; i < m_iPlayerHp; ++i)
	{
		D3DXMatrixTranslation(&matTrans, 17.7f - 1.5f*i, 13.3f, 0);
		m_matWorld = matTrans * matScale * matBill;
		
		dynamic_cast<ModelClass*>(this)->Render(pD3D->GetDeviceContext());
		pLightShader->Render(pD3D->GetDeviceContext(), dynamic_cast<ModelClass*>(this)->GetIndexCount(), m_matWorld, m_pCamera->GetView(),
			pD3D->GetProj(), dynamic_cast<ModelClass*>(this)->GetTexture(), pLight->GetDirection(), pLight->GetAmbientColor(),
			pLight->GetDiffuseColor(), m_pCamera->GetPos(), pLight->GetSpecularColor(), pLight->GetSpecularPower());
	}

	pD3D->TurnOffAlphaBlending();
}

void HpUI::Shutdown()
{
}
