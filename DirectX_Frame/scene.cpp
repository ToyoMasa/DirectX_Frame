#include "common.h"

//======================================================================
//	Ã“Iƒƒ“ƒo•Ï”‚Ì‰Šú‰»
//======================================================================
CScene *CScene::m_Scene[PRIORITY_MAX][OBJECT_MAX] = { NULL };

CScene::CScene(int priority)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (m_Scene[priority][i] == NULL)
		{
			m_Scene[priority][i] = this;
			m_Type = SCENE_TYPE_NONE;
			m_Visible = true;
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
	for (int j = 0; j < PRIORITY_MAX; j++)
	{
		for (int i = 0; i < OBJECT_MAX; i++)
		{
			if (m_Scene[j][i] == this)
			{
				Uninit();
				m_Scene[j][i] = NULL;
				delete this;
				break;
			}
		}
	}
}

void CScene::UpdateAll()
{
	for (int j = 0; j < PRIORITY_MAX; j++)
	{
		for (int i = 0; i < OBJECT_MAX; i++)
		{
			if (m_Scene[j][i] != NULL)
			{
				m_Scene[j][i]->Update();
			}
		}
	}
}

void CScene::DrawAll()
{
	for (int j = 0; j < PRIORITY_MAX; j++)
	{
		for (int i = 0; i < OBJECT_MAX; i++)
		{
			if (m_Scene[j][i] != NULL)
			{
				if (m_Scene[j][i]->m_Visible)
				{
					m_Scene[j][i]->Draw();
				}
			}
		}
	}
}

void CScene::ReleaseAll()
{
	for (int j = 0; j < PRIORITY_MAX; j++)
	{
		for (int i = 0; i < OBJECT_MAX; i++)
		{
			if (m_Scene[j][i] != NULL)
			{
				m_Scene[j][i]->Release();
			}
		}
	}
}
