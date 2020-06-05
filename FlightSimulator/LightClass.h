#pragma once

#include <d3dx10math.h>
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);

	D3DXVECTOR4 GetAmbientColor();
	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();
	D3DXVECTOR4 GetSpecularColor();
	float GetSpecularPower();

private:
	D3DXVECTOR4 m_vAmbientColor;
	D3DXVECTOR4 m_vDiffuseColor;
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR4 m_vSpecularColor;
	float m_fSpecularPower;
};