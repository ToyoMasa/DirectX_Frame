//======================================================================
//	3D�|���S���w�b�_[scene3D]
//
//======================================================================
#ifndef _SCENESKINMESH_H_
#define _SCENESKINMESH_H_

#include <string>
#include "SkinMeshFile.h"

class CSceneSkinMesh : public CScene
{
public:
	CSceneSkinMesh::CSceneSkinMesh(int priority) : CScene(priority)
	{
		D3DXMatrixIdentity(&m_World);
		D3DXMatrixIdentity(&m_Move);
		D3DXMatrixIdentity(&m_Rotate);
		D3DXMatrixIdentity(&m_RotX);
		D3DXMatrixIdentity(&m_RotY);
		D3DXMatrixIdentity(&m_RotZ);
		D3DXMatrixIdentity(&m_Scale);

		m_SkinMeshFile = NULL;
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

	static CSceneSkinMesh* Create(const std::string& modelName);

private:
	D3DXMATRIX			m_World;		// ���[���h�ϊ��s��
	D3DXMATRIX			m_Move;			// ���s�ړ��s��
	D3DXMATRIX			m_Rotate;		// ��]�s��
	D3DXMATRIX			m_RotX;			// X����]�s��
	D3DXMATRIX			m_RotY;			// Y����]�s��
	D3DXMATRIX			m_RotZ;			// Z����]�s��
	D3DXMATRIX			m_Scale;		// �g��k���s��
	SkinMeshFile*		m_SkinMeshFile;
};

#endif
