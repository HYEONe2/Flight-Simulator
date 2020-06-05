#include "GameObjectMgr.h"

#include "D3DClass.h"
#include "GameObject.h"
#include "CameraClass.h"
#include "LightClass.h"
#include "LightShaderClass.h"
#include "TextureShaderClass.h"

#include "Player.h"

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

void GameObjectMgr::Render(D3DClass * pD3D, LightShaderClass* pLightShader, TextureShaderClass* pTextureShader, CameraClass * pCamera, LightClass * pLight)
{
	if (m_GameObjectLst.size() == 0)
		return;

	for (auto iter : m_GameObjectLst)
	{
		if (!iter->GetTexture())
		{
			dynamic_cast<Player*>(iter)->RenderBitmap(pD3D, pTextureShader);
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
