//======================================================================
//	ビルボード描画　（2018/04/25）
//	Author : 豊村 昌俊
//======================================================================
#include "common.h"
#include "main.h"
#include "billboard.h"
#include "camera.h"
#include "scene3D.h"

static const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL);

//======================================================================
//	グローバル変数
//======================================================================
CScene3D *billboard;

void CBillBoard::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

}
//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 NV; // 法線
//	D3DCOLOR color;
//	D3DXVECTOR2 texcoord;
//} VERTEX3D;
//
//static LPDIRECT3DTEXTURE9 g_pTextures[BB_TEXTURE_MAX];
//static D3DMATERIAL9 g_mat; // モデル1部分につき1個
//static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL; //頂点バッファ
//static LPDIRECT3DINDEXBUFFER9  g_pIndexBuffer = NULL;  //インデックスバッファ
//static D3DXMATRIX g_mtxWorld;			//ワールド変換行列
//static D3DXMATRIX g_mtxMove;			//座標変換行列
//static D3DXMATRIX g_mtxScale;			//拡大縮小行列
//
//bool BillBoardInit(void)			// ビルボードの初期化
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return false;
//	}
//	HRESULT hr;
//
//	for (int i = 0; i < BB_TEXTURE_MAX; i++)
//	{
//		hr = D3DXCreateTextureFromFile(pDevice, g_aBBTextureFileName[i].FileName, &g_pTextures[i]);
//
//		if (FAILED(hr))
//		{
//			MessageBox(NULL, "テクスチャの読み込みに失敗しました", "エラー", MB_OK);
//			return false;
//		}
//	}
//
//	// 頂点バッファ							↓大きい分には問題ない
//	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
//
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, "頂点バッファの読み込みに失敗しました", "エラー", MB_OK);
//		return false;
//	}
//
//	// インデックスバッファ					↓大きい分には問題ない					↓sizeがDWORDなら32
//	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
//
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, "インデックスバッファの読み込みに失敗しました", "エラー", MB_OK);
//		return false;
//	}
//
//	VERTEX3D* pV;
//
//	// 頂点バッファ
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//
//	// インデックスバッファ
//	LPWORD pIndex;
//	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
//
//	pIndex[0] = 0;
//	pIndex[1] = 1;
//	pIndex[2] = 2;
//	pIndex[3] = 3;
//
//	g_pIndexBuffer->Unlock();
//
//	// ワールド座標行列の初期化
//	D3DXMatrixIdentity(&g_mtxWorld);
//	D3DXMatrixIdentity(&g_mtxMove);
//	return true;
//}
//
//void BillBoardUninit(void)			// ビルボードの終了処理
//{
//	for (int i = 0; i < BB_TEXTURE_MAX; i++)
//	{
//		if (g_pTextures[i] != NULL)
//		{//テクスチャの開放
//			g_pTextures[i]->Release();
//			g_pTextures[i] = NULL;
//		}
//	}
//
//	//頂点バッファの解放
//	if (g_pVertexBuffer != NULL)
//	{
//		g_pVertexBuffer->Release();
//		g_pVertexBuffer = NULL;
//	}
//
//	//インデックスバッファの解放
//	if (g_pIndexBuffer != NULL)
//	{
//		g_pIndexBuffer->Release();
//		g_pIndexBuffer = NULL;
//	}
//}
//
//void BillBoardUpdate(void)			// ビルボードの更新
//{
//
//}
//
//void BillBoardDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale)			// ビルボードの描画
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	// ワールド座標行列をセット
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// ビュー行列の逆行列を作成
//	// 平行移動とY軸以外の回転を無効にする
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// テクスチャのセット
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(今から使用する頂点情報)の設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// 頂点バッファとインデックスバッファの設定
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//各種行列の設定(自分のやりたいところでやる)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//}
//
//void BillBoardDrawCircle(D3DXVECTOR3 vPos, float scale)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	// ワールド座標行列をセット
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// ビュー行列の逆行列を作成
//	// 平行移動とY軸以外の回転を無効にする
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// FVF(今から使用する頂点情報)の設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// 頂点バッファとインデックスバッファの設定
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//各種行列の設定(自分のやりたいところでやる)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//}
//
//void BillBoardDrawStand(int texNum, D3DXVECTOR3 vPos, float scale)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	// ワールド座標行列をセット
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y + scale * 0.5f, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// ビュー行列の逆行列を作成
//	// 平行移動とY軸以外の回転を無効にする
//	mtxViewRotInv._21 = 0.0f;
//	mtxViewRotInv._32 = 0.0f;
//	mtxViewRotInv._12 = 0.0f;
//	mtxViewRotInv._23 = 0.0f;
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ライティング使うときに外す
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// αテスト(3つセット)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// αテストのON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 128);					// 第2引数は0～255の好きな値
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// 第2引数は不等号(GREATERは大なり)、上の値より大きければ合格
//
//																	// テクスチャのセット
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(今から使用する頂点情報)の設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// 頂点バッファとインデックスバッファの設定
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//各種行列の設定(自分のやりたいところでやる)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// αテストのON/OFF
//}
//
//void BillBoardDrawStand(int texNum, float posX, float posY, float posZ, float scale)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	// ワールド座標行列をセット
//	D3DXMatrixTranslation(&g_mtxMove, posX, posY + scale * 0.5f, posZ);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// ビュー行列の逆行列を作成
//	// 平行移動とY軸以外の回転を無効にする
//	mtxViewRotInv._21 = 0.0f;
//	mtxViewRotInv._32 = 0.0f;
//	mtxViewRotInv._12 = 0.0f;
//	mtxViewRotInv._23 = 0.0f;
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ライティング使うときに外す
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// αテスト(3つセット)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// αテストのON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 128);					// 第2引数は0～255の好きな値
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// 第2引数は不等号(GREATERは大なり)、上の値より大きければ合格
//
//																	// テクスチャのセット
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(今から使用する頂点情報)の設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// 頂点バッファとインデックスバッファの設定
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//各種行列の設定(自分のやりたいところでやる)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// αテストのON/OFF
//}
//
//// アニメーションビルボードの描画
//void BillBoardAnimDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale, int tcx, int tcy, int tcw, int tch)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	int tw = g_aBBTextureFileName[texNum].width;
//	int th = g_aBBTextureFileName[texNum].height;
//	float u0 = (float)tcx / tw;					//テクスチャの切り取り
//	float v0 = (float)tcy / th;					//
//	float u1 = (float)(tcx + tcw) / tw;
//	float v1 = (float)(tcy + tch) / th;
//
//	VERTEX3D* pV;
//
//	// 頂点バッファ
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) };
//
//	g_pVertexBuffer->Unlock();
//
//	// ワールド座標行列をセット
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// ビュー行列の逆行列を作成
//	// 平行移動とY軸以外の回転を無効にする
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ライティング使うときに外す
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// αテスト(3つセット)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// αテストのON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 16);					// 第2引数は0～255の好きな値
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// 第2引数は不等号(GREATERは大なり)、上の値より大きければ合格
//
//																	// テクスチャのセット
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(今から使用する頂点情報)の設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// 頂点バッファとインデックスバッファの設定
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//各種行列の設定(自分のやりたいところでやる)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// αテストのON/OFF
//
//																// 頂点バッファ
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//}
//
//// 色変えビルボードの描画
//void BillBoardColorDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale, D3DCOLOR color)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	VERTEX3D* pV;
//
//	// 頂点バッファ
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), color, D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), color, D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), color, D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), color, D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//
//	// ワールド座標行列をセット
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// ビュー行列の逆行列を作成
//	// 平行移動とY軸以外の回転を無効にする
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ライティング使うときに外す
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// αテスト(3つセット)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// αテストのON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						// 第2引数は0～255の好きな値
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// 第2引数は不等号(GREATERは大なり)、上の値より大きければ合格
//
//																	// テクスチャのセット
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(今から使用する頂点情報)の設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// 頂点バッファとインデックスバッファの設定
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//各種行列の設定(自分のやりたいところでやる)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// αテストのON/OFF
//
//																// 頂点バッファ
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//}
//
//// アニメーションビルボードの描画
//void BillBoardAnimDrawCircle(int texNum, float width, float height, D3DXVECTOR3 vPos, float scale, int tcx, int tcy, int tcw, int tch)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	int tw = g_aBBTextureFileName[texNum].width;
//	int th = g_aBBTextureFileName[texNum].height;
//	float u0 = (float)tcx / tw;					//テクスチャの切り取り
//	float v0 = (float)tcy / th;					//
//	float u1 = (float)(tcx + tcw) / tw;
//	float v1 = (float)(tcy + tch) / th;
//
//	VERTEX3D* pV;
//
//	// 頂点バッファ
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-width / 2,  height / 2, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) };
//	pV[1] = { D3DXVECTOR3(width / 2,  height / 2, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) };
//	pV[2] = { D3DXVECTOR3(-width / 2, -height / 2, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) };
//	pV[3] = { D3DXVECTOR3(width / 2, -height / 2, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) };
//
//	g_pVertexBuffer->Unlock();
//
//	// ワールド座標行列をセット
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// ビュー行列の逆行列を作成
//	// 平行移動とY軸以外の回転を無効にする
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ライティング使うときに外す
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// αテスト(3つセット)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// αテストのON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 16);					// 第2引数は0～255の好きな値
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// 第2引数は不等号(GREATERは大なり)、上の値より大きければ合格
//
//																	// テクスチャのセット
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(今から使用する頂点情報)の設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// 頂点バッファとインデックスバッファの設定
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//各種行列の設定(自分のやりたいところでやる)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// αテストのON/OFF
//
//																// 頂点バッファ
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//}
//
//// 回転しないビルボードの描画
//void BillBoardStaticDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale)
//{
//}
//
//CBillBoard::CBillBoard()
//{
//	m_Texture = NULL;
//	m_VertexBuffer = NULL;
//	m_IndexBuffer = NULL;
//}
//
//CBillBoard::~CBillBoard()
//{
//}
//
//void CBillBoard::Init()
//{
//
//}
//
//void CBillBoard::Uninit()
//{
//	//頂点バッファの解放
//	if (m_VertexBuffer != NULL)
//	{
//		m_VertexBuffer->Release();
//		m_VertexBuffer = NULL;
//	}
//
//	//インデックスバッファの解放
//	if (m_IndexBuffer != NULL)
//	{
//		m_IndexBuffer->Release();
//		m_IndexBuffer = NULL;
//	}
//}

void CBillBoard::Update()
{

}

void CBillBoard::Draw()
{

}

void CBillBoard::DrawStand()
{

}
