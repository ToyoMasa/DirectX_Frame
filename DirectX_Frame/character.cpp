//======================================================================
//	プレイヤー　（2018/05/23）
//	Author : 豊村 昌俊
//======================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "camera.h"
#include "scene.h"
#include "scene3D.h"
#include "sceneModel.h"
#include "texture.h"
#include "billboard.h"
#include "player.h"
#include "input.h"
#include "field.h"
#include "character.h"
#include "enemy.h"

CCharacter *CCharacter::m_Characters[CHARACTER_MAX] = { NULL };

void CCharacter::UpdateAll()
{
	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		if (m_Characters[i] != NULL)
		{
			m_Characters[i]->Update();
		}
	}
}

void CCharacter::Release()
{
	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		if (m_Characters[i] == this)
		{
			m_Characters[i]->Uninit();
			m_Characters[i] = NULL;
			delete this;
			break;
		}
	}
}

void CCharacter::ReleaseAll()
{
	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		if (m_Characters[i] != NULL)
		{
			m_Characters[i]->Release();
		}
	}
}
