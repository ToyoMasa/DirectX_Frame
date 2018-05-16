//======================================================================
//	2Dポリゴンヘッダ[scene2D.h]
//
//======================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

static const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR	color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

class CScene2D :public CScene
{
public:
	//======================================================================
	//	コンストラクタ
	//======================================================================
	CScene2D::CScene2D(int prioriy) :CScene(prioriy)
	{
		m_Pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		m_TexId = 0;
	}

	//======================================================================
	//	デストラクタ
	//======================================================================
	~CScene2D() {}

	void Init(int texid, float texW, float texH);
	void Uninit();
	void Update();
	void Draw();
	static CScene2D* Create(int texid, float texW, float texH);
private:
	D3DXVECTOR2 m_TexSize;
	int m_TexId;
};

#endif //!_SCENE2D_H_