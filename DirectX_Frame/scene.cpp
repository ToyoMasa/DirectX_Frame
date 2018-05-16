#include "common.h"

//======================================================================
//	Ã“Iƒƒ“ƒo•Ï”‚Ì‰Šú‰»
//======================================================================
CScene *CScene::m_Scene[10] = { NULL };

CScene::CScene()
{
	for (int i = 0; i < 10; i++)
	{
		if (m_Scene[i] == NULL)
		{
			m_Scene[i] = this;
			break;
		}
	}
}

void CScene::Set(D3DXVECTOR3& pos)
{
	m_Pos = pos;
}

void CScene::Release()
{
	for (int i = 0; i < 10; i++)
	{
		if (m_Scene[i] == this)
		{
			m_Scene[i] = NULL;
			Uninit();
			delete this;
			break;
		}
	}
}

void CScene::UpdateAll()
{
	for (int i = 0; i < 10; i++)
	{
		if (m_Scene[i] != NULL)
		{
			m_Scene[i]->Update();
		}
	}
}

void CScene::DrawAll()
{
	for (int i = 0; i < 10; i++)
	{
		if (m_Scene[i] != NULL)
		{
			m_Scene[i]->Draw();
		}
	}
}

void CScene::ReleaseAll()
{
	for (int i = 0; i < 10; i++)
	{
		if (m_Scene[i] != NULL)
		{
			m_Scene[i]->Release();
		}
	}
}
