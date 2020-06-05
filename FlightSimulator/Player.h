#pragma once
#include "GameObject.h"

class D3DClass;
class BitmapClass;
class CameraClass;
class InputClass;
class TextureShaderClass;

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
	void InitBitmap(ID3D11Device*, int, int, WCHAR*);

	virtual bool Frame(float);
	void RenderBitmap(D3DClass*, TextureShaderClass*);
	void Shutdown();

private:
	void Move(float);

private:
	BitmapClass* m_pBitmap;
	CameraClass* m_pCamera;
	InputClass* m_pInput;
};

