#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

#include "textureclass.h"

class BitmapClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool Initialize(ID3D11Device*, int, int, WCHAR*);
	bool Initialize(ID3D11Device*, int, int, WCHAR*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	bool LoadTexture(ID3D11Device*, WCHAR*);
	
	void ShutdownBuffers();
	void ReleaseTexture();

	bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer *m_pVertexBuffer, *m_pIndexBuffer;
	int m_iVertexCount, m_iIndexCount;
	TextureClass* m_pTexture;
	
	int m_iScreenWidth, m_iScreenHeight;
	int m_iBitmapWidth, m_iBitmapHeight;
	int m_iPreviousPosX, m_iPreviousPosY;
};