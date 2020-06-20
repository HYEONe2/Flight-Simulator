#pragma once
#include "GameObject.h"

class D3DClass;
class LightShaderClass;
class LightClass;
class ModelClass;
class CameraClass;

class HpUI :
	public GameObject
{
public:
	HpUI();
	HpUI(HpUI&);
	virtual ~HpUI();

public:
	void SetCamera(CameraClass* pCamera) { m_pCamera = pCamera; }
	void SetPlayer(GameObject* pPlayer) { m_pPlayer= pPlayer; }
	void SetRender(bool bRender) { m_bRender = bRender; }

public:
	void Init();
	void Init(D3DClass*);

	virtual bool Frame(float);
	void Render(D3DClass*, LightShaderClass*, LightClass*);

private:
	void Shutdown();

private:
	CameraClass* m_pCamera = nullptr;
	GameObject* m_pPlayer = nullptr;

	int m_iPlayerHp = 0;
	bool m_bRender = false;
};

