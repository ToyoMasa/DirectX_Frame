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
	TEX_ID_MAX,
} TEXTURE_ID;

// テクスチャ読み込み用のソース
static const std::string TEXTURE_SOURCE[] =
{
	"data/textures/field001.jpg",
	"data/textures/yajirusi.png",
};

// テクスチャがロードされているか検索するためのマップ
static std::map<int, std::string> MAP_TEXTURES;
static std::map<int, bool> MAP_LOADING_TEXTURES;

class CTexture
{
public:
	CTexture();
	~CTexture();

	static void Init();
	void Load();
	void Release();

private:
	LPDIRECT3DTEXTURE9 m_Texture;
	float m_Width;
	float m_Height;
	static int sm_NumTextures;
};

static const CTexture TEXTURES[TEX_ID_MAX];

#endif // !_TEXTURE_H_
