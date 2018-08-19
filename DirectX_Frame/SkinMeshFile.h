#ifndef SKINMESH_FILE_H_
#define SKINMESH_FILE_H_

#include <string>
#include <d3d9.h>
#include <d3dx9.h>

#include "SkinMeshData.h"

// 階層付きXFile
class SkinMeshFile
{
public:
	SkinMeshFile() :
		m_SkinMeshData(),
		m_RootFrame(NULL),
		m_AnimController(NULL)
	{}

	~SkinMeshFile();

	/*
		XFile読み込み
			戻り値：
				読み込み結果：
					成功：
						true
					失敗：
						false
			引数：
				std::string file_name：
					ファイル名
			内容：
				XFileの読み込みを行う
	*/
	bool Load(std::string file_name);


	/*
		ボーン行列の領域確保(全ボーン)
			戻り値：
				結果
					成功：S_OK
					失敗：E_FAIL

			引数：					
				LPD3DXFRAME  
					対象フレーム

			内容：
				対象フレームのボーン行列のメモリ領域の確保関数を実行する
				子供、兄弟に対してこの関数を再帰として使用し、
				末端まで確保を行うようにする
	*/
	HRESULT AllocateAllBoneMatrix(LPD3DXFRAME  );	

	/*
		ボーン行列の領域確保(全ボーン)
			戻り値：
				結果
					成功：S_OK
					失敗：E_FAIL

			引数：					
				LPD3DXMESHCONTAINER  
					確保対象のメッシュコンテナ

			内容：
				コンテナで使用しているボーン行列分のメモリ領域を確保する
				
	*/
	HRESULT AllocateBoneMatrix(LPD3DXMESHCONTAINER  );

	/*
		描画
			戻り値：
				なし

			引数：
				LPD3DXMATRIX matrix
					描画で使用するワールド座標行列

			内容：
				XFileを描画する
				この関数内でルートフレームを引数とした
				DrawFrameを使用する
				その際にこのXFileを描画するオブジェクトの
				ワールド座標行列を引数で渡す
	*/
	void Draw(LPD3DXMATRIX matrix);

	/*
		フレームの描画
			戻り値：
				なし

			引数：
				LPD3DXFRAME frame：
					フレームデータ

			内容：
				引数で指定されたフレームを描画する
				この関数内でフレームが保持している
				全てのメッシュコンテナを描画(DrawMeshContainer)する
	*/
	void DrawFrame(LPD3DXFRAME frame);

	/*
		メッシュコンテナの描画
			戻り値：
				なし

			引数：
				LPD3DXFRAME frame：
					フレームデータ

				LPD3DXMESHCONTAINER container：
					メッシュコンテナ
			内容：
				指定されたメッシュコンテナを描画する
				描画の内容は通常のXFileの描画方法と同じ方法で
				描画できる
	*/
	void DrawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER container);

	/*
		フレームの更新
			戻り値：
				なし

			引数：
				LPD3DXFRAME base：
					更新フレーム

				LPD3DXMATRIX parent_matrix：
					親の姿勢行列

			内容：
				親の姿勢行列を元にして自分の姿勢行列を更新する
				子、兄弟がいる場合はそれを再帰で呼び出す
	*/
	void UpdateFrame(LPD3DXFRAME base, LPD3DXMATRIX parent_matrix);

	/*
		アニメーションの更新
			戻り値：
				なし
			引数：
				なし
			内容：
				アニメーションを更新させる
	*/
	void UpdateAnim(void);

	// 追加
	// アニメーション切替
	void ChangeAnim(UINT newAnimID);
private:
	// 階層データ
	SkinMeshData *m_SkinMeshData;

	// ルートフレーム
	LPD3DXFRAME m_RootFrame;

	// アニメーション管理
    LPD3DXANIMATIONCONTROLLER m_AnimController;

	// 追加
	// 現在のトラック

	// アニメーション
	LPD3DXANIMATIONSET m_AnimSet[20];
	//現在のアニメーション
	DWORD m_CurrentAnim;
	//現在のアニメーションデータトラック
	D3DXTRACK_DESC m_CurrentTrackDesc;
};

#endif