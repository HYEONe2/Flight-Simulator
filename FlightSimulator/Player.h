#pragma once
#include "GameObject.h"

#include "CameraClass.h"

class D3DClass;
class InputClass;
class LightShaderClass;
class LightClass;
class Collision;

class Player :
	public GameObject
{
public:
	Player();
	Player(Player&);
	virtual ~Player();

public:
	void SetCamera(CameraClass* pCamera) { m_pCamera = pCamera; }
	void SetInput(InputClass* pInput) { m_pInput = pInput; }
	void SetEffectOn() { m_bRenderEffect = true; m_fStayTime = 0; }
	Collision* Get_Collision() { return m_pCollision; }


public:
	void Init();
	void Init(CameraClass*, InputClass*);
	void Init(ID3D11Device*);

	virtual bool Frame(float);
	void Render(D3DClass*, LightShaderClass*, LightClass*);
	void RenderCockpit(D3DClass*, LightShaderClass*, LightClass*);
	void RenderEffect(D3DClass*, LightShaderClass*, LightClass*);

private:
	void Move(float);
	void CheckSpeed(CameraClass::MOVE, float, bool = false);
	void Shutdown();

private:
	InputClass* m_pInput;
	CameraClass* m_pCamera;
	ModelClass* m_pCockpit;
	ModelClass* m_pEffect;
	Collision* m_pCollision;

	float m_fSpeed = 0.f;
	float m_fMaxSpeed = 10.f;

	float m_fRotSpeed[2] { 0.f,0.f };
	float m_fRotSpeedLimit[2]{ -0.0001f , 0.0001f};

	bool m_bRenderEffect = false;
	bool m_bReverse = false;
	float m_fAlpha = 0.f;
	float m_fStayTime = 0.f;
};

