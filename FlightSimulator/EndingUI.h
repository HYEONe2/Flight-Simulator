#pragma once
#include "GameObject.h"

class D3DClass;
class TextureShaderClass;
class ModelClass;
class CameraClass;

class EndingUI :
	public GameObject
{
public:
	EndingUI();
	EndingUI(EndingUI&);
	virtual ~EndingUI();

public:
	void SetCamera(CameraClass* pCamera) { m_pCamera = pCamera; }
	void SetRender(bool bRender) { m_bRender = bRender; }
	void SetIsSuccess(bool bSuccess) { m_bIsSuccess = bSuccess; }

public:
	void Init();
	void Init(D3DClass*);

	virtual bool Frame(float);
	void Render(D3DClass*, TextureShaderClass*);

private:
	void Shutdown();

private:
	CameraClass* m_pCamera;
	ModelClass* m_pFail;

	bool m_bRender = false;
	bool m_bIsSuccess = false;
};

