#include "Skybox.h"

#include "D3DClass.h"
#include "CameraClass.h"
#include "TextureShaderClass.h"

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
	return true;
}

void Skybox::Render(D3DClass *pD3D, TextureShaderClass *pTextureShader)
{
	dynamic_cast<ModelClass*>(this)->Render(pD3D->GetDeviceContext());
	pTextureShader->Render(pD3D->GetDeviceContext(), dynamic_cast<ModelClass*>(this)->GetIndexCount(), m_matWorld, m_pCamera->GetView(),
		pD3D->GetProj(), dynamic_cast<ModelClass*>(this)->GetTexture());
}

void Skybox::Shutdown()
{
}

