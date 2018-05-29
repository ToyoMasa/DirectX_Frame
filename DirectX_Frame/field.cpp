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

float fieldHeight[21][21] =
{
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},

	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

	{ 1.5f, 1.2f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
};

void CField::Init(int texId, float meshSize, int sizeX, int sizeY)
{
	m_TextureID = texId;
	m_MeshSize = meshSize;

	m_NumVertex = (sizeX + 1) * (sizeY + 1);				// 頂点数の計算
	m_NumPrimitive = sizeX * 2 * sizeY + 4 * (sizeY - 1);	// プリティブ数の計算
	m_NumIndex = m_NumPrimitive + 2;						// インデックス数の計算

	CScene3D::Create(texId, meshSize, sizeX, sizeY, m_NumPrimitive, m_NumVertex, m_NumIndex);
}

void CField::Init(int texId, float meshSize, int sizeX, int sizeY, bool isHeight)
{
	m_TextureID = texId;
	m_MeshSize = meshSize;

	m_NumVertex = (sizeX + 1) * (sizeY + 1);				// 頂点数の計算
	m_NumPrimitive = sizeX * 2 * sizeY + 4 * (sizeY - 1);	// プリティブ数の計算
	m_NumIndex = m_NumPrimitive + 2;						// インデックス数の計算

	VERTEX_3D* V = new VERTEX_3D[m_NumVertex];
	for (int j = 0; j < sizeY + 1; j++)
	{
		for (int i = 0; i < sizeX + 1; i++)
		{
			V[i + (sizeX + 1) * j] = { D3DXVECTOR3(-(meshSize * sizeX / 2) + (meshSize * i), 0.0f, (meshSize * sizeY / 2) - (meshSize * j)), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2((float)i ,  (float)j) };
		}
	}

	// テスト
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			V[i + 5 * j].pos.y = fieldHeight[j][i];
		}
	}

	LPWORD Index = new WORD[m_NumIndex];

	int numindex = 0;

	for (int j = 0; j < sizeY; j++)
	{
		for (int i = 0; i < sizeX + 1; i++)
		{
			Index[numindex] = j * (sizeX + 1) + i + sizeX + 1;
			numindex++;
			Index[numindex] = j * (sizeX + 1) + i;
			numindex++;

			if (i == sizeX && !(j == sizeY - 1))
			{
				Index[numindex] = j * (sizeX + 1) + i;
				numindex++;
				Index[numindex] = (j + 1) * (sizeX + 1) + sizeX + 1;
				numindex++;
			}
		}
	}

	CScene3D::Create(texId, V, Index, m_NumPrimitive, m_NumVertex, m_NumIndex);

	delete V;
	delete Index;
}

void CField::Uninit()
{

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

CField* CField::Create(int texId, float meshSize, int sizeX, int sizeY, bool isHeight)
{
	CField* field = new CField(0);
	field->Init(texId, meshSize, sizeX, sizeY, isHeight);

	return field;
}
