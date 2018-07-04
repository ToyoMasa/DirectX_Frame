//======================================================================
//	テクスチャ管理ヘッダ[texture]
//
//======================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <map>

// テクスチャ管理用ID
typedef enum
{
	TEX_ID_FIELD001 = 0,			// フィールド
	TEX_ID_CURSOR,					// カーソル
	TEX_ID_TREE,					// ツリー
	TEX_ID_SKY,						// 空
	TEX_ID_NUMBER001,				// 数字
	TEX_ID_TITLE,				// タイトル
	TEX_ID_RESULT,				// リザルト
	TEX_ID_MAX,
} TEXTURE_ID;

// テクスチャ読み込み用のソース
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

// テクスチャがロードされているか検索するためのマップ
static std::map<int, std::string> MAP_TEXTURES;				// テクスチャのファイルパス管理
static std::map<std::string, bool> MAP_LOADING_TEXTURES;	// すでに同じテクスチャが読み込まれていないか
static std::map<int, int> MAP_TEXTURE_USE_NUM;				// このテクスチャを使っている数

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
