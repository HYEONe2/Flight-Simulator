#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

#include "TextureClass.h"

class FontClass
{
private:
	struct FontType
	{
		float fLeft, fRight;
		int iSize;
	};
	struct VertexType
	{
		D3DXVECTOR3 vPos;
		D3DXVECTOR2 vTex;
	};

public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();
	
	ID3D11ShaderResourceView* GetTexture();
	void BuildVertexArray(void*, char*, float, float);

private:
	bool LoadFontData(char*);
	bool LoadTexture(ID3D11Device*, WCHAR*);

	void ReleaseFontData();
	void ReleaseTexture();

private:
	FontType* m_pFont;
	TextureClass* m_pTexture;
};