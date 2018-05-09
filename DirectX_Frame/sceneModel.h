//======================================================================
//	3Dモデルヘッダ[sceneModel]
//
//======================================================================
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

#include <string>

// モデル管理用ID
typedef enum
{
	MODEL_ID_UFO = 0,		// UFO
	MODEL_ID_MAX,
} MODEL_ID;

// モデル読み込み用のソース
static const std::string MODEL_SOURCE[] =
{
	"data/models/player_ufo.x",
};

class CSceneModel : public CGameObject
{
public:
	CSceneModel();
	~CSceneModel();

	void Init(const std::string& modelName);
	void Uninit();
	void Update();
	void Draw();
	void SetWorld(D3DXMATRIX move);
	void Move(D3DXVECTOR3 pos);
	void Rotate(D3DXVECTOR3 rot);
	void Scale(D3DXVECTOR3 scale);
	static CSceneModel* Create(const std::string& modelName);

private:
	D3DXMATRIX			m_World;		// ワールド変換行列
	D3DXMATRIX			m_Move;			// 平行移動行列
	D3DXMATRIX			m_Rotate;		// 回転行列
	D3DXMATRIX			m_RotX;			// X軸回転行列
	D3DXMATRIX			m_RotY;			// Y軸回転行列
	D3DXMATRIX			m_RotZ;			// Z軸回転行列
	D3DXMATRIX			m_Scale;		// 拡大縮小行列
	LPD3DXMESH			m_Mesh;			// メッシュ
	DWORD				m_MaterialNum;	// マテリアル数
	int					m_TextureNum;	// テクスチャ数
	LPD3DXBUFFER		m_Material;		// マテリアル
	LPDIRECT3DTEXTURE9 *m_Texture;		// テクスチャ
};

#endif //!_SCENEMODEL_H_