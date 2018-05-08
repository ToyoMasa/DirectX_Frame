//======================================================================
//	ビルボード処理ヘッダ[billboard.h]
//
//======================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include <string>

bool BillBoardInit(void);			// ビルボードの初期化
void BillBoardUninit(void);			// ビルボードの終了処理
void BillBoardUpdate(void);			// ビルボードの更新

									//************************************************************************
									//	ビルボード描画（非設置物）
									//	第一引数　使用するテクスチャ番号
									//	第二引数　描画する場所
									//	第三引数　サイズ
									//************************************************************************
void BillBoardDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale);						// 球状のビルボードの描画
void BillBoardDrawCircle(D3DXVECTOR3 vPos, float scale);						// 球状のビルボードの描画
void BillBoardColorDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale, D3DCOLOR color);

void BillBoardAnimDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale, int tcx, int tcy, int tcw, int tch); // アニメーションビルボードの描画
void BillBoardAnimDrawCircle(int texNum, float width, float height, D3DXVECTOR3 vPos, float scale, int tcx, int tcy, int tcw, int tch); // アニメーションビルボードの描画

void BillBoardStaticDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale);					// 回転しないビルボードの描画

																							//************************************************************************
																							//	ビルボード描画（設置物）
																							//	第一引数　使用するテクスチャ番号
																							//	第二引数　描画する場所
																							//	第三引数　サイズ
																							//************************************************************************
void BillBoardDrawStand(int texNum, D3DXVECTOR3 vPos, float scale);
void BillBoardDrawStand(int texNum, float posX, float posY, float posZ, float scale);		// 直立するオブジェクトビルボードの描画


class CBillBoard
{
public:
	CBillBoard();
	~CBillBoard();

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static void DrawStand();

private:
	static int						m_TexId;				// テクスチャ番号
	static D3DMATERIAL9				m_Mat;					// モデル1部分につき1個
	static LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;			// 頂点バッファ
	static LPDIRECT3DINDEXBUFFER9	m_IndexBuffer;			// インデックスバッファ
	static D3DXMATRIX				m_World;				// ワールド変換行列
	static D3DXMATRIX				m_Move;					// 座標変換行列
	static D3DXMATRIX				m_Scale;				// 拡大縮小行列
};


#endif // !_BILLBOARD_H_
