#pragma once

#include "FontClass.h"
#include "FontShaderClass.h"

class TextClass
{
private:
	struct SentenceType
	{
		ID3D11Buffer *pVertexBuffer, *pIndexBuffer;
		int iVertexCount, iIndexCount, iMaxLength;
		float fRed, fGreen, fBlue;
	};
	struct VertexType
	{
		D3DXVECTOR3 vPos;
		D3DXVECTOR2 vTex;
	};

public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();
	
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, D3DXMATRIX);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);

	bool SetFps(int, ID3D11DeviceContext*);
	bool SetCpu(int, ID3D11DeviceContext*);
	bool SetSentence(int, ID3D11DeviceContext*);

private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*, D3DXMATRIX, D3DXMATRIX);
	void ReleaseSentence(SentenceType**);

private:
	FontClass* m_pFont;
	FontShaderClass* m_pFontShader;
	int m_iScreenWidth, m_iScreenHeight;
	D3DXMATRIX m_matBaseView;
	
	SentenceType* m_pFpsSentence;
	SentenceType* m_pCpuSentence;
	SentenceType* m_pPolySentence;
};

