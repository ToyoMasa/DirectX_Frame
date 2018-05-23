//======================================================================
//	フィールド　（2018/05/23)
//	Author : 豊村 昌俊
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

	m_NumVertex = (sizeX + 1) * (sizeY + 1);				// 頂点数の計算
	m_NumPrimitive = sizeX * 2 * sizeY + 4 * (sizeY - 1);	// プリティブ数の計算
	m_NumIndex = m_NumPrimitive + 2;						// インデックス数の計算

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
