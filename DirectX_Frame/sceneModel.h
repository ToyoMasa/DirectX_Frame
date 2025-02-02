//======================================================================
//	3Dモデルヘッダ[sceneModel]
//
//======================================================================
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

#include <string>
#include <fbxsdk.h>
#pragma comment (lib, "libfbxsdk-mt.lib")

// モデル管理用ID
typedef enum
{
	MODEL_ID_UFO = 0,		// UFO
	MODEL_ID_XBOT,
	MODEL_ID_SKYBOX,
	MODEL_ID_SKYDOME,
	MODEL_ID_PLAYER,
	MODEL_ID_ENEMY01,
	MODEL_ID_TARGET,
	MODEL_ID_MAX,
} MODEL_ID;

// モデル読み込み用のソース
static const std::string MODEL_SOURCE[] =
{
	"data/models/player_ufo.x",
	"data/models/xbot2.x",
	"data/models/skybox.x",
	"data/models/sky.x",
	"data/models/player.x",
	"data/models/enemy01.x",
	"data/models/target.x",
};

class CSceneModel : public CScene
{
public:
	//======================================================================
	//	コンストラクタ
	//======================================================================
	CSceneModel::CSceneModel(int priority) : CScene(priority)
	{
		D3DXMatrixIdentity(&m_World);
		D3DXMatrixIdentity(&m_Move);
		D3DXMatrixIdentity(&m_Rotate);
		D3DXMatrixIdentity(&m_RotX);
		D3DXMatrixIdentity(&m_RotY);
		D3DXMatrixIdentity(&m_RotZ);
		D3DXMatrixIdentity(&m_Scale);
		m_MaterialNum = 0;
		m_TextureNum = 0;
		m_Texture = NULL;
		m_Material = NULL;
		m_isIgnoreLight = false;
	}

	//======================================================================
	//	デストラクタ
	//======================================================================
	CSceneModel::~CSceneModel()
	{
	}

	void Init(const std::string& modelName);
	void Uninit();
	void Update();
	void Draw();
	void SetWorld(D3DXMATRIX move);
	void Move(D3DXVECTOR3 pos);
	void Rotate(D3DXVECTOR3 rot);
	void Rotate(D3DXMATRIX rot);
	void Scale(D3DXVECTOR3 scale);
	static CSceneModel* Create(const std::string& modelName);
	static CSceneModel* Create(const std::string& modelName, bool isIgnore);

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
	bool				m_isIgnoreLight;// 影を付けるかどうか
};

#endif //!_SCENEMODEL_H_