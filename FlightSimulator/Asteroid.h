#pragma once
#include "GameObject.h"

class Player;
class Asteroid : public GameObject
{
public:
	Asteroid();
	Asteroid(Asteroid&);
	virtual ~Asteroid();

public:
	void Init();
	void Init(D3DXVECTOR3);
	virtual bool Frame(float);
	void Shutdown();
	void Set_Player(GameObject*);

private:
	void Move(float);

private:
	GameObject* m_pPlayer;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vDir;
	bool m_bIsCloser;


};

