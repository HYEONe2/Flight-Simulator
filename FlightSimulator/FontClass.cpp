#include "FontClass.h"

#include "fontclass.h"

//The class constructor initializes all the private member variables for the FontClass to null.
FontClass::FontClass()
{
	m_pFont = 0;
	m_pTexture = 0;
}

FontClass::FontClass(const FontClass& other)
{
}

FontClass::~FontClass()
{
}

bool FontClass::Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename)
{
	bool result;
	// Load in the text file containing the font data.
	result = LoadFontData(fontFilename);
	if (!result)
	{
		return false;
	}
	// Load the texture that has the font characters on it.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}
	return true;
}

void FontClass::Shutdown()
{
	// Release the font texture.
	ReleaseTexture();
	// Release the font data.
	ReleaseFontData();
	return;
}

bool FontClass::LoadFontData(char* filename)
{
	ifstream fin;
	int i;
	char temp;

	// Create the font spacing buffer.
	m_pFont = new FontType[95];
	if (!m_pFont)
	{
		return false;
	}

	// Read in the font iSize and spacing between chars.
	fin.open(filename);
	if (fin.fail())
	{
		return false;
	}
	// Read in the 95 used ascii characters for text.
	for (i = 0; i < 95; i++)
	{
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}
		fin >> m_pFont[i].fLeft;
		fin >> m_pFont[i].fRight;
		fin >> m_pFont[i].iSize;
	}
	// Close the file.
	fin.close();
	return true;
}

void FontClass::ReleaseFontData()
{
	// Release the font data array.
	if (m_pFont)
	{
		delete[] m_pFont;
		m_pFont = 0;
	}
	return;
}

bool FontClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;
	// Create the texture object.
	m_pTexture = new TextureClass;
	if (!m_pTexture)
	{
		return false;
	}
	// Initialize the texture object.
	result = m_pTexture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}
	return true;
}

void FontClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_pTexture)
	{
		m_pTexture->Shutdown();
		delete m_pTexture;
		m_pTexture = 0;
	}
	return;
}

ID3D11ShaderResourceView* FontClass::GetTexture()
{
	return m_pTexture->GetTexture();
}

void FontClass::BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY)
{
	VertexType* vertexPtr;
	int numLetters, index, i, letter;
	// Coerce the input vertices into a VertexType structure.
	vertexPtr = (VertexType*)vertices;
	// Get the number of letters in the sentence.
	numLetters = (int)strlen(sentence);
	// Initialize the index to the vertex array.
	index = 0;

	// Draw each letter onto a quad.
	for (i = 0; i < numLetters; i++)
	{
		letter = ((int)sentence[i]) - 32;
		// If the letter is a space then just move over three pixels.
		if (letter == 0)
		{
			drawX = drawX + 3.0f;
		}
		else
		{
			// First triangle in quad.
			// Top fLeft.
			vertexPtr[index].vPos = D3DXVECTOR3(drawX, drawY, 0.0f);
			vertexPtr[index].vTex = D3DXVECTOR2(m_pFont[letter].fLeft, 0.0f);
			index++;
			vertexPtr[index].vPos = D3DXVECTOR3((drawX + m_pFont[letter].iSize), (drawY - 16), 0.0f); // Bottom fRight.
			vertexPtr[index].vTex = D3DXVECTOR2(m_pFont[letter].fRight, 1.0f);
			index++;
			// Bottom fLeft.
			vertexPtr[index].vPos = D3DXVECTOR3(drawX, (drawY - 16), 0.0f);
			vertexPtr[index].vTex = D3DXVECTOR2(m_pFont[letter].fLeft, 1.0f);
			index++;
			// Second triangle in quad.
			vertexPtr[index].vPos = D3DXVECTOR3(drawX, drawY, 0.0f); // Top fLeft.
			vertexPtr[index].vTex = D3DXVECTOR2(m_pFont[letter].fLeft, 0.0f);
			index++;
			// Top fRight.
			vertexPtr[index].vPos = D3DXVECTOR3(drawX + m_pFont[letter].iSize, drawY, 0.0f);
			vertexPtr[index].vTex = D3DXVECTOR2(m_pFont[letter].fRight, 0.0f);
			index++;
			// Bottom fRight.
			vertexPtr[index].vPos = D3DXVECTOR3((drawX + m_pFont[letter].iSize), (drawY - 16), 0.0f);
			vertexPtr[index].vTex = D3DXVECTOR2(m_pFont[letter].fRight, 1.0f);
			index++;
			// Update the x location for drawing by the iSize of the letter and one pixel.
			drawX = drawX + m_pFont[letter].iSize + 1.0f;
		}
	}
	return;
}