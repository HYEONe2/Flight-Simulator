#include "TextClass.h"

TextClass::TextClass()
{
	m_pFont = 0;
	m_pFontShader = 0;
	m_pFpsSentence = 0;
	m_pCpuSentence = 0;
	m_pPolySentence = 0;
}

TextClass::TextClass(const TextClass& other)
{
}

TextClass::~TextClass()
{
}

bool TextClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int
	screenWidth, int screenHeight, D3DXMATRIX baseViewMatrix)
{
	bool result;

	// Store the screen width and height.
	m_iScreenWidth = screenWidth;
	m_iScreenHeight = screenHeight;
	// Store the base view matrix.
	m_matBaseView = baseViewMatrix;

	// Create the font object.
	m_pFont = new FontClass;
	if (!m_pFont)
	{
		return false;
	}
	// Initialize the font object.
	result = m_pFont->Initialize(device, "../Engine/data/Font.txt", L"../Engine/data/Font.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		return false;
	}

	// Create the font shader object.
	m_pFontShader = new FontShaderClass;
	if (!m_pFontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_pFontShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_pFpsSentence, 16, device);
	if (!result)
	{
		return false;
	}
	// Initialize the first sentence.
	result = InitializeSentence(&m_pCpuSentence, 16, device);
	if (!result)
	{
		return false;
	}
	// Initialize the first sentence.
	result = InitializeSentence(&m_pPolySentence, 64, device);
	if (!result)
	{
		return false;
	}

	return true;
}

void TextClass::Shutdown()
{
	// Release the first sentence.
	ReleaseSentence(&m_pFpsSentence);
	// Release the second sentence.
	ReleaseSentence(&m_pCpuSentence);
	// Release the first sentence.
	ReleaseSentence(&m_pPolySentence);

	// Release the second sentence.
	if (m_pFontShader)
	{
		m_pFontShader->Shutdown();
		delete m_pFontShader;
		m_pFontShader = 0;
	}
	// Release the font object.
	if (m_pFont)
	{
		m_pFont->Shutdown();
		delete m_pFont;
		m_pFont = 0;
	}
	return;
}

bool TextClass::SetFps(int fps, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char fpsString[16];
	float red, green, blue;
	bool result;
	// Truncate the fps to below 10,000.
	if (fps > 9999)
	{
		fps = 9999;
	}
	// Convert the fps integer to string format.
	_itoa_s(fps, tempString, 10);
	// Setup the fps string.
	strcpy_s(fpsString, "Fps: ");
	strcat_s(fpsString, tempString);
	// If fps is 60 or above set the fps color to green.
	if (fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
	}
	// If fps is below 60 set the fps color to yellow.
	if (fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}
	// If fps is below 30 set the fps color to red.
	if (fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}
	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_pFpsSentence, fpsString, 20, 20, red, green, blue, deviceContext);
	if (!result)
	{
		return false;
	}
	return true;
}

bool TextClass::SetCpu(int cpu, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char cpuString[16];
	bool result;
	// Convert the cpu integer to string format.
	_itoa_s(cpu, tempString, 10);
	// Setup the cpu string.
	strcpy_s(cpuString, "Cpu: ");
	strcat_s(cpuString, tempString);
	strcat_s(cpuString, "%");
	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_pCpuSentence, cpuString, 20, 40, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}
	return true;
}

bool TextClass::SetSentence(int Cnt, ID3D11DeviceContext *deviceContext)
{
	char tempString[30];
	char polyString[30];
	bool result;
	// Convert the cpu integer to string format.
	_itoa_s(Cnt, tempString, 10);
	// Setup the cpu string.
	strcpy_s(polyString, "Polygon Count: ");
	strcat_s(polyString, tempString);
	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_pPolySentence, polyString, 20, 60, 0.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}
	return true;
}


bool TextClass::Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX
	orthoMatrix)
{
	bool result;

	if (!m_pFpsSentence)
		return false;

	// Draw the first sentence.
	result = RenderSentence(deviceContext, m_pFpsSentence, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	// Draw the second sentence.
	result = RenderSentence(deviceContext, m_pCpuSentence, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	// Draw the first sentence.
	result = RenderSentence(deviceContext, m_pPolySentence, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	
	return true;
}

bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;
	// Create a new sentence object.
	*sentence = new SentenceType;
	if (!*sentence)
	{
		return false;
	}
	// Initialize the sentence buffers to null.
	(*sentence)->pVertexBuffer = 0;
	(*sentence)->pIndexBuffer = 0;
	// Set the maximum length of the sentence.
	(*sentence)->iMaxLength = maxLength;
	// Set the number of vertices in the vertex array.
	(*sentence)->iVertexCount = 6 * maxLength;
	// Set the number of indexes in the index array.
	(*sentence)->iIndexCount = (*sentence)->iVertexCount;
	// Create the vertex array.
	vertices = new VertexType[(*sentence)->iVertexCount];
	if (!vertices)
	{
		return false;
	}
	// Create the index array.
	indices = new unsigned long[(*sentence)->iIndexCount];
	if (!indices)
	{
		return false;
	}
	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->iVertexCount));
	// Initialize the index array.
	for (i = 0; i < (*sentence)->iIndexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->iVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->pVertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->iIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->pIndexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;
	// Release the index array as it is no longer needed.
	delete[] indices;
	indices = 0;
	return true;
}

bool TextClass::UpdateSentence(SentenceType* sentence, char* text, int positionX, int positionY, float red, float
	green, float blue, ID3D11DeviceContext* deviceContext)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;

	// Store the color of the sentence.
	sentence->fRed = red;
	sentence->fGreen = green;
	sentence->fBlue = blue;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(text);
	
	// Check for possible buffer overflow.
	if (numLetters > sentence->iMaxLength)
	{
		return false;
	}
	// Create the vertex array.
	vertices = new VertexType[sentence->iVertexCount];
	if (!vertices)
	{
		return false;
	}
	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * sentence->iVertexCount));

	// Calculate the X and Y pixel position on the screen to start drawing to.
	drawX = (float)(((m_iScreenWidth / 2) * -1) + positionX);
	drawY = (float)((m_iScreenHeight / 2) - positionY);

	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	m_pFont->BuildVertexArray((void*)vertices, text, drawX, drawY);

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(sentence->pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0,
		&mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;
	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->iVertexCount));
	// Unlock the vertex buffer.
	deviceContext->Unmap(sentence->pVertexBuffer, 0);
	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;
	return true;
}

void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if (*sentence)
	{
		// Release the sentence vertex buffer.
		if ((*sentence)->pVertexBuffer)
		{
			(*sentence)->pVertexBuffer->Release();
			(*sentence)->pVertexBuffer = 0;
		}
		// Release the sentence index buffer.
		if ((*sentence)->pIndexBuffer)
		{
			(*sentence)->pIndexBuffer->Release();
			(*sentence)->pIndexBuffer = 0;
		}
		// Release the sentence.
		delete *sentence;
		*sentence = 0;
	}
	return;
}

bool TextClass::RenderSentence(ID3D11DeviceContext* deviceContext, SentenceType* sentence, D3DXMATRIX
	worldMatrix, D3DXMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	D3DXVECTOR4 pixelColor;
	bool result;
	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &sentence->pVertexBuffer, &stride, &offset);
	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(sentence->pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// Create a pixel color vector with the input sentence color.
	pixelColor = D3DXVECTOR4(sentence->fRed, sentence->fGreen, sentence->fBlue, 1.0f);
	// Render the text using the font shader.
	result = m_pFontShader->Render(deviceContext, sentence->iIndexCount, worldMatrix, m_matBaseView,
		orthoMatrix, m_pFont->GetTexture(), pixelColor);
	if (!result)
	{
		false;
	}
	return true;
}