#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

#include "TextureClass.h"

class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct ModelCount
	{
		int vertexCount;
		int textureCount;
		int normalCount;
		int faceCount;
	};
	struct OBJType
	{
		float x, y, z;
	};
	struct FaceType
	{
		int x, y, z, w;
		int tu, tv, tz, tw;
		int nx, ny, nz, nw;
	};

public:
	ID3D11ShaderResourceView* GetTexture();
	int GetVertexCount();
	int GetIndexCount();

public:
	bool SetTexture(ID3D11Device*, WCHAR*);

public:
	ModelClass();
	ModelClass(const ModelClass&);
	virtual ~ModelClass();

	bool Initialize(ID3D11Device*, WCHAR*);
	bool InitializeForCube(ID3D11Device*, char*, WCHAR*); 
	// obj model
	bool Initialize(ID3D11Device*, WCHAR*, WCHAR*);
	// RectPolygon Obj Model
	bool InitializeForRectObj(ID3D11Device*, WCHAR*, WCHAR*);
	// Terrain model
	bool InitializeForPlane(ID3D11Device*, WCHAR*);
	bool InitializeForCube(ID3D11Device*, WCHAR*);
	
public:
	void Render(ID3D11DeviceContext*);
	virtual void Shutdown();

private:
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();
	bool LoadModel(char*);
	void ReleaseModel(); 

private:
	bool InitializeBuffers(ID3D11Device*);
	bool InitializeBuffersForOBJ(ID3D11Device*);
	bool InitializeBuffersForPlane(ID3D11Device*);
	bool InitializeBuffersForCube(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	bool LoadOBJModel(WCHAR*);
	bool ReadFileCounts(WCHAR*, ModelCount&);

	bool LoadDataStructures(WCHAR*, ModelCount);	
	//Rect Polygon Model
	bool LoadRectOBJModel(WCHAR*);
	bool LoadRectDataStructures(WCHAR*, ModelCount);


private:
	ID3D11Buffer *m_pVertexBuffer, *m_pIndexBuffer;
	int m_iVertexCount, m_iIndexCount;

private:
	TextureClass* m_pTexture;
	ModelType* m_pModel;
};