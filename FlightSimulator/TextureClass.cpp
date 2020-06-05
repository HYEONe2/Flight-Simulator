#include "TextureClass.h"

TextureClass::TextureClass()
{
	m_pTexture = 0;
}

TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;
	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_pTexture, NULL);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void TextureClass::Shutdown()
{
	// Release the texture resource.
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = 0;
	}
	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_pTexture;
}