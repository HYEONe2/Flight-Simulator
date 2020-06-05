#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class D3DClass;
class GameObject;
class CameraClass;
class LightClass;

class LightShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX matWorld;
		D3DXMATRIX matView;
		D3DXMATRIX matProj;
	};
	struct CameraBufferType
	{
		D3DXVECTOR3 vCameraPos;
		float fPadding;
	};
	struct LightBufferType
	{
		D3DXVECTOR4 vAmbientColor; 
		D3DXVECTOR4 vDiffuseColor;
		D3DXVECTOR3 vLightDir;
		//float padding; // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
		float fSpecularPower;
		D3DXVECTOR4 vSpecularColor;
	};

public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3, D3DXVECTOR4, float);
	bool Render(D3DClass*, GameObject*, CameraClass*, LightClass*);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3, D3DXVECTOR4, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pLayout;
	ID3D11Buffer* m_pMatrixBuffer;
	ID3D11Buffer* m_pLightBuffer;
	ID3D11Buffer* m_pCameraBuffer;
	ID3D11SamplerState* m_pSampleState;
};