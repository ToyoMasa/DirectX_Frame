#ifndef _SHADER_H_
#define _SHADER_H_

class CShader
{
public:
	CShader()
	{
		m_hTech = NULL;
	}
	~CShader(){}

	void Init(CCamera* camera);
	bool Load();
	void Draw();

private:
	D3DXMATRIX m_World;	// 描画に使う変換行列

	CCamera* m_pCamera;

	LPD3DXEFFECT m_pEffect;
	D3DXHANDLE m_hTech;			// 現在のテクニックのハンドル
	D3DXHANDLE m_hTechNext;		// 次のテクニックのハンドル
};

#endif // !_SHADER_H_
