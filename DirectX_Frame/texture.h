//======================================================================
//	�e�N�X�`���Ǘ��w�b�_[texture]
//
//======================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <map>

// �e�N�X�`���Ǘ��pID
typedef enum
{
	TEX_ID_FIELD001 = 0,			// �t�B�[���h
	TEX_ID_CURSOR,					// �J�[�\��
	TEX_ID_TREE,					// �c���[
	TEX_ID_SKY,						// ��
	TEX_ID_NUMBER001,				// ����
	TEX_ID_TITLE,				// �^�C�g��
	TEX_ID_RESULT,				// ���U���g
	TEX_ID_MAX,
} TEXTURE_ID;

// �e�N�X�`���ǂݍ��ݗp�̃\�[�X
static const std::string TEXTURE_SOURCE[] =
{
	"data/textures/field001.jpg",
	"data/textures/yajirusi.png",
	"data/textures/tree.png",
	"data/textures/sky001.jpg",
	"data/textures/number001.png",
	"data/textures/title.png",
	"data/textures/result.png",
};

// �e�N�X�`�������[�h����Ă��邩�������邽�߂̃}�b�v
static std::map<int, std::string> MAP_TEXTURES;				// �e�N�X�`���̃t�@�C���p�X�Ǘ�
static std::map<std::string, bool> MAP_LOADING_TEXTURES;	// ���łɓ����e�N�X�`�����ǂݍ��܂�Ă��Ȃ���
static std::map<int, int> MAP_TEXTURE_USE_NUM;				// ���̃e�N�X�`�����g���Ă��鐔

class CTexture
{
public:
	CTexture()
	{
		m_Texture = NULL;
		m_Height = 0;
		m_Width = 0;
	}
	~CTexture();

	static void Init();
	static void Load(int id);
	static void Release(int id);
	static void LoadAll();
	static void ReleaseAll();
	static LPDIRECT3DTEXTURE9 GetTexture(int id);

	LPDIRECT3DTEXTURE9 GetTexture() { return m_Texture; }
	void LoadTexture(int id);
	void ReleaseTexture();

private:
	LPDIRECT3DTEXTURE9 m_Texture;
	float m_Width;
	float m_Height;
};

static CTexture TEXTURES[TEX_ID_MAX];

#endif // !_TEXTURE_H_
