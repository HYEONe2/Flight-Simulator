#include "GameObjectMgr.h"

#include "D3DClass.h"
#include "GameObject.h"
#include "CameraClass.h"
#include "LightClass.h"
#include "LightShaderClass.h"
#include "TextureShaderClass.h"

#include "Skybox.h"
#include "Player.h"
#include "DistanceUI.h"
#include "EndingUI.h"
#include "HpUI.h"

GameObjectMgr::GameObjectMgr()
{
}

GameObjectMgr::GameObjectMgr(const GameObjectMgr & other)
{
}

GameObjectMgr::~GameObjectMgr()
{
	Shutdown();
}

bool GameObjectMgr::PushGameObject(GameObject * pGameObject)
{
	m_GameObjectLst.push_back(pGameObject);

	return true;
}

bool GameObjectMgr::Frame(float fFrameTime)
{
	if (m_GameObjectLst.size() == 0)
		return false;

	for (auto iter : m_GameObjectLst)
	{
		if (!iter->Frame(fFrameTime))
		{
			return false;
		}
	}
	return true;
}

void GameObjectMgr::Render(D3DClass *pD3D, CameraClass *pCamera, LightShaderClass *pLightShader, LightClass *pLight, TextureShaderClass *pTextureShader)
{
	if (m_GameObjectLst.size() == 0)
		return;

	for (auto iter : m_GameObjectLst)
	{
		ID3D11RasterizerState* pRasterState;
		pD3D->GetDeviceContext()->RSGetState(&pRasterState);

		D3D11_RASTERIZER_DESC rasterDesc;
		pRasterState->GetDesc(&rasterDesc);

		if (rasterDesc.CullMode == D3D11_CULL_NONE)
		{
			ID3D11RasterizerState* pRasterState;
			pD3D->GetDeviceContext()->RSGetState(&pRasterState);

			D3D11_RASTERIZER_DESC rasterDesc;
			pRasterState->GetDesc(&rasterDesc);

			rasterDesc.CullMode = D3D11_CULL_BACK;
			pD3D->GetDevice()->CreateRasterizerState(&rasterDesc, &pRasterState);
			pD3D->GetDeviceContext()->RSSetState(pRasterState);
		}

		switch (iter->GetTag())
		{
		case GameObject::TAG_SKYBOX:
			rasterDesc.CullMode = D3D11_CULL_NONE;
			pD3D->GetDevice()->CreateRasterizerState(&rasterDesc, &pRasterState);
			pD3D->GetDeviceContext()->RSSetState(pRasterState);
			dynamic_cast<Skybox*>(iter)->Render(pD3D, pTextureShader);
			continue;
		case GameObject::TAG_PLAYER:
			dynamic_cast<Player*>(iter)->Render(pD3D, pLightShader, pLight);
			continue;
		case GameObject::TAG_DISTANCEUI:
			dynamic_cast<DistanceUI*>(iter)->Render(pD3D, pTextureShader);
			continue;
		case GameObject::TAG_ENDINGUI:
			dynamic_cast<EndingUI*>(iter)->Render(pD3D, pTextureShader);
			continue;
		case GameObject::TAG_HPUI:
			dynamic_cast<HpUI*>(iter)->Render(pD3D, pTextureShader);
			continue;
		}

		iter->Render(pD3D->GetDeviceContext());
		pLightShader->Render(pD3D, iter, pCamera, pLight);
	}
}

void GameObjectMgr::EraseGameObject(GameObject * pGameObject)
{
	if (m_GameObjectLst.size() == 0
		|| !pGameObject)
		return;

	for (auto iter = m_GameObjectLst.begin(); iter != m_GameObjectLst.end(); )
	{
		if (*iter == pGameObject)
		{
			delete *iter;
			*iter = 0;
			iter = m_GameObjectLst.erase(iter);
		}
		else
			++iter;
	}
}

void GameObjectMgr::Shutdown()
{
	if (m_GameObjectLst.size() == 0)
	{
		m_GameObjectLst.clear();
		return;
	};

	for (auto iter : m_GameObjectLst)
	{
		if (iter)
		{
			delete iter;
			iter = 0;
		}
	}

	m_GameObjectLst.clear();
}

int GameObjectMgr::Get_PolySize()
{
	int Polycnt = 0;
	for (auto iter : m_GameObjectLst)
	{
		if (iter)
		{
			Polycnt += (iter->GetVertexCount()/3);
		}
	}

	return Polycnt;
}
