#ifndef _SHADER_H_
#define _SHADER_H_

class CCamera;

class CShader
{
public:
	CShader()
	{
		m_hTech = NULL;
		D3DXMatrixIdentity(&m_World);
	}
	~CShader(){}

	void Init(CCamera* camera);
	void Uninit();
	bool Load();
	void Draw();

private:
	D3DXMATRIX m_World;	// �`��Ɏg���ϊ��s��

	CCamera* m_pCamera;

	LPD3DXEFFECT m_pEffect;
	D3DXHANDLE m_hTech;			// ���݂̃e�N�j�b�N�̃n���h��
	D3DXHANDLE m_hTechNext;		// ���̃e�N�j�b�N�̃n���h��
};

#endif // !_SHADER_H_
