//======================================================================
//	3Dモデルの描画
//
//======================================================================
#include "common.h"
#include "main.h"
#include "scene3D.h"
#include "texture.h"

static const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL);

VERTEX_3D v[] = {
	//		位置座標							法線ベクトル						色							UV座標
	//上の面														    
	{ D3DXVECTOR3(-2.0f,  0.0f,  2.0f), D3DXVECTOR3(0.0f,  1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	{ D3DXVECTOR3( 2.0f,  0.0f,  2.0f), D3DXVECTOR3(0.0f,  1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },
	{ D3DXVECTOR3(-2.0f,  0.0f, -2.0f), D3DXVECTOR3(0.0f,  1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) },
	{ D3DXVECTOR3( 2.0f,  0.0f, -2.0f), D3DXVECTOR3(0.0f,  1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) },
};

WORD index[] =
{
	//前の面
	0, 1, 2,
	1, 3, 2,
};

//======================================================================
//	コンストラクタ
//======================================================================
CScene3D::CScene3D()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;
}

//======================================================================
//	デストラクタ
//======================================================================
CScene3D::~CScene3D()
{
}

//======================================================================
//	初期処理関数
//======================================================================
void CScene3D::Init(int texId)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

	m_TexId = texId;
	CTexture::Load(m_TexId);

	HRESULT hr;

	// 頂点バッファ							↓大きい分には問題ない
	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファの読み込みに失敗しました", "エラー", MB_OK);
		return;
	}

	// インデックスバッファ					↓大きい分には問題ない			↓sizeがDWORDなら32
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "インデックスバッファの読み込みに失敗しました", "エラー", MB_OK);
		return;
	}

	VERTEX_3D* pV;

	// 頂点バッファ
	m_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	memcpy(pV, &v[0], sizeof(v));

	m_VertexBuffer->Unlock();

	LPWORD pIndex;
	m_IndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

	memcpy(pIndex, &index[0], sizeof(index));

	m_IndexBuffer->Unlock();

	// マテリアルの設定
	m_Mat.Diffuse.r = 1.0f;
	m_Mat.Diffuse.g = 1.0f;
	m_Mat.Diffuse.b = 1.0f;
	m_Mat.Diffuse.a = 1.0f;
	// アンビエントカラー（紫）
	m_Mat.Ambient.r = 0.8f;
	m_Mat.Ambient.g = 0.7f;
	m_Mat.Ambient.b = 0.9f;
	m_Mat.Ambient.a = 1.0f;

	D3DXMatrixIdentity(&m_World);
}

//======================================================================
//	終了処理関数
//======================================================================
void CScene3D::Uninit()
{
	// テクスチャの解放
	CTexture::Release(m_TexId);

	//頂点バッファの解放
	if (m_VertexBuffer != NULL)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}

	//インデックスバッファの解放
	if (m_IndexBuffer != NULL)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = NULL;
	}
}

//======================================================================
//	更新関数
//======================================================================
void CScene3D::Update()
{
}

//======================================================================
//	描画関数
//======================================================================
void CScene3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

	// FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// 頂点バッファとインデックスバッファの設定
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_IndexBuffer);

	//各種行列の設定(自分のやりたいとこ);
	pDevice->SetMaterial(&m_Mat);

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTransform(D3DTS_WORLD, &m_World);

	pDevice->SetTexture(0, CTexture::GetTexture(m_TexId));

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}

CScene3D* CScene3D::Create(int texId)
{
	CScene3D* scene3D = new CScene3D();
	scene3D->Init(texId);

	return scene3D;
}
