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
	D3DXMATRIX m_World;	// �`��Ɏg���ϊ��s��

	CCamera* m_pCamera;

	LPD3DXEFFECT m_pEffect;
	D3DXHANDLE m_hTech;			// ���݂̃e�N�j�b�N�̃n���h��
	D3DXHANDLE m_hTechNext;		// ���̃e�N�j�b�N�̃n���h��
};

#endif // !_SHADER_H_
