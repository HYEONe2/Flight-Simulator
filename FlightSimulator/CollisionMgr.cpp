#include "CollisionMgr.h"

#include<iostream>
using namespace std;

CollisionMgr::CollisionMgr()
{
}

CollisionMgr::~CollisionMgr()
{
	Shutdown();
}

bool CollisionMgr::PushCollObject(Collision::COLLISION_TAG _eTag, Collision *pObject)
{
	m_listCollision[_eTag].push_back(pObject);

	return true;
}

bool CollisionMgr::UpdateCollsion(Collision::COLLISION_TAG _ePlayer, Collision::COLLISION_TAG _eAsteroid)
{
	if (m_listCollision[_ePlayer].size() == 0)
		return false;
	if (m_listCollision[_eAsteroid].size() == 0)
		return false;

	for (auto play : m_listCollision[_ePlayer])
	{
		D3DXVECTOR3 playerPos = play->Get_Pos();
		for (auto aster : m_listCollision[_eAsteroid])
		{			
			D3DXVECTOR3 AsterPos = aster->Get_Pos();
			float fDist = D3DXVec3Length(&(playerPos - AsterPos));
			if (fDist <= aster->Get_Radius() + play->Get_Radius())
			{			
				EraseGameObject(_eAsteroid, &aster);
				return true;
			}
		}
	}
	return false;
}

void CollisionMgr::EraseGameObject(Collision::COLLISION_TAG _eTag, Collision** pObject)
{
	if (m_listCollision[_eTag].size() == 0 || !pObject)
		return;

	auto iter = find(m_listCollision[_eTag].begin(), m_listCollision[_eTag].end(), *pObject);

	if (iter == m_listCollision[_eTag].end())
		return;

	delete *pObject;
	*pObject = 0;
	m_listCollision[_eTag].erase(iter);
}

void CollisionMgr::Shutdown()
{
	for (int i = Collision::COL_PLAYER; i < Collision::COL_END; i++)
	{
		if (m_listCollision[i].size() == 0)
		{
			m_listCollision[i].clear();
		}
	
		for (auto iter : m_listCollision[i])
		{
			if (iter)
			{
				delete iter;
				iter = 0;
			}
		}

		m_listCollision[i].clear();
	}


}
