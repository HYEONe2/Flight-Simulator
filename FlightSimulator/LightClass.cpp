#include "LightClass.h"

LightClass::LightClass()
{
}

LightClass::LightClass(const LightClass& other)
{
}

LightClass::~LightClass()
{
}

void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_vAmbientColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_vDiffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightClass::SetDirection(float x, float y, float z)
{
	m_vDir = D3DXVECTOR3(x, y, z);
	return;
}

void LightClass::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_vSpecularColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightClass::SetSpecularPower(float power)
{
	m_fSpecularPower = power;
	return;
}

D3DXVECTOR4 LightClass::GetAmbientColor()
{
	return m_vAmbientColor;
}

D3DXVECTOR4 LightClass::GetDiffuseColor()
{
	return m_vDiffuseColor;
}

D3DXVECTOR3 LightClass::GetDirection()
{
	return m_vDir;
}

D3DXVECTOR4 LightClass::GetSpecularColor()
{
	return m_vSpecularColor;
}

float LightClass::GetSpecularPower()
{
	return m_fSpecularPower;
}