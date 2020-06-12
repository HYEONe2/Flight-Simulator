#pragma once
#include "GameObject.h"

class D3DClass;
class CameraClass;

class Skybox :
	public GameObject
{
public:
	Skybox();
	Skybox(Skybox&);
	virtual ~Skybox();

public:
	void Init();
	virtual bool Frame(float);

private:
	void Shutdown();

public:
	void SetD3D(D3DClass* pD3D) { m_pD3D = pD3D; }
	void SetCamera(CameraClass* pCamera) { m_pCamera = pCamera; }

private:
	D3DClass* m_pD3D;
	CameraClass* m_pCamera;
};

