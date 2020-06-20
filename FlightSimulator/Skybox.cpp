#include "Skybox.h"

#include "D3DClass.h"
#include "CameraClass.h"

#include <iostream>
using namespace std;

Skybox::Skybox()
{
	Init();
}

Skybox::Skybox(Skybox &)
{
}

Skybox::~Skybox()
{
	Shutdown();
}

void Skybox::Init()
{
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 1000.f, 1000.f, 1000.f);
	SetWorld(matScale);

	m_eTag = TAG_SKYBOX;
}

bool Skybox::Frame(float fFrameTime)
{
	//SetPos(m_pCamera->GetPos());

	return true;
}

void Skybox::Shutdown()
{
}

