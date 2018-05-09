//======================================================================
//	3D���f���w�b�_[sceneModel]
//
//======================================================================
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

#include <string>

// ���f���Ǘ��pID
typedef enum
{
	MODEL_ID_UFO = 0,		// UFO
	MODEL_ID_MAX,
} MODEL_ID;

// ���f���ǂݍ��ݗp�̃\�[�X
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
	D3DXMATRIX			m_World;		// ���[���h�ϊ��s��
	D3DXMATRIX			m_Move;			// ���s�ړ��s��
	D3DXMATRIX			m_Rotate;		// ��]�s��
	D3DXMATRIX			m_RotX;			// X����]�s��
	D3DXMATRIX			m_RotY;			// Y����]�s��
	D3DXMATRIX			m_RotZ;			// Z����]�s��
	D3DXMATRIX			m_Scale;		// �g��k���s��
	LPD3DXMESH			m_Mesh;			// ���b�V��
	DWORD				m_MaterialNum;	// �}�e���A����
	int					m_TextureNum;	// �e�N�X�`����
	LPD3DXBUFFER		m_Material;		// �}�e���A��
	LPDIRECT3DTEXTURE9 *m_Texture;		// �e�N�X�`��
};

#endif //!_SCENEMODEL_H_