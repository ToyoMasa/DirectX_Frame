//======================================================================
//	�t�B�[���h�@�i2018/05/23)
//	Author : �L�� ���r
//======================================================================
#include "common.h"
#include "main.h"
#include "scene.h"
#include "scene3D.h"
#include "texture.h"
#include "billboard.h"
#include "field.h"

void CField::Init(int texId, float meshSize, int sizeX, int sizeY)
{
	m_TextureID = texId;
	m_MeshSize = meshSize;

	m_NumVertex = (sizeX + 1) * (sizeY + 1);				// ���_���̌v�Z
	m_NumPrimitive = sizeX * 2 * sizeY + 4 * (sizeY - 1);	// �v���e�B�u���̌v�Z
	m_NumIndex = m_NumPrimitive + 2;						// �C���f�b�N�X���̌v�Z

	CScene3D::Create(texId, meshSize, sizeX, sizeY, m_NumPrimitive, m_NumVertex, m_NumIndex);
}

void CField::Uninit()
{
	if (m_Vertex != NULL)
	{
		delete m_Vertex;
		m_Vertex = NULL;
	}

	if (m_Index != NULL)
	{
		delete m_Index;
		m_Index = NULL;
	}
}

void CField::Update()
{

}

void CField::Draw()
{

}

CField* CField::Create(int texId, float meshSize, int sizeX, int sizeY)
{
	CField* field = new CField(0);
	field->Init(texId, meshSize, sizeX, sizeY);

	return field;
}
