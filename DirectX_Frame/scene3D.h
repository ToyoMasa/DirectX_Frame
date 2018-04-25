//======================================================================
//	3Dポリゴンヘッダ[scene3D]
//
//======================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include <string>

static const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL);

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 NV; // 法線
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} VERTEX_3D;

class CScene3D:public CScene
{
public:
	CScene3D();
	~CScene3D();

	void Init(const std::string& texName);
	void Uninit();
	void Update();
	void Draw();
private:
	LPDIRECT3DTEXTURE9		m_Texture;		// テクスチャ
	D3DMATERIAL9			m_Mat;			// マテリアル
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer; // 頂点バッファ
	LPDIRECT3DINDEXBUFFER9  m_IndexBuffer;  // インデックスバッファ
	D3DXMATRIX				m_World;

	int m_NumVertex;
	int m_NumPrimitive;
};

#endif //!_SCENE3D_H_
