#pragma once
#include "GameObject.h"
class Planet :
	public GameObject
{
public:
	Planet();
	Planet(Planet&);
	virtual ~Planet();

public:
	void Init();
	void Init(float, float _scale = 10.f);
	virtual bool Frame(float);
	void Shutdown();

private:
	void Move(float);

private:
	float m_fDist;
	float m_fScale;

};

