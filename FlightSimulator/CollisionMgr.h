#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <list>
using namespace std;

#include "Collision.h"

class CollisionMgr
{
public:
	CollisionMgr();
	~CollisionMgr();

public:
	bool PushCollObject(Collision::COLLISION_TAG, Collision*);

	bool UpdateCollsion(Collision::COLLISION_TAG, Collision::COLLISION_TAG);

	void EraseGameObject(Collision::COLLISION_TAG,Collision**);
	void Shutdown();
	
private:
	list<Collision*>	m_listCollision[Collision::COL_END];

};

