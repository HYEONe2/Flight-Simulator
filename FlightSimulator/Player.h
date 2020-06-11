#pragma once
#include "GameObject.h"

#include "CameraClass.h"

class D3DClass;
class BitmapClass;
class InputClass;
class LightShaderClass;
class LightClass;

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

public:
	void Init();
	void Init(CameraClass*, InputClass*);
	void InitCockPit(ID3D11Device*, WCHAR*);

	virtual bool Frame(float);
	void RenderCockpit(D3DClass*, LightShaderClass*, LightClass*);
	void Shutdown();

private:
	void Move(float);
	void CheckSpeed(CameraClass::MOVE, float, bool = false);

private:
	ModelClass* m_pCockpit;
	CameraClass* m_pCamera;
	InputClass* m_pInput;

	int m_iScreenWidth;
	int m_iScreenHeight;

	float m_fSpeed = 0.f;
	float m_fMaxSpeed = 5.f;

	float m_fRotSpeed = 0.f;
	float m_fRotSpeedL = 0.f;
	float m_fRotMinSpeed = -0.0002f;
	float m_fRotMaxSpeed = 0.0002f;
};

