//======================================================================
//	エネミー　（2018/06/12）
//	Author : 豊村 昌俊
//======================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "camera.h"
#include "scene.h"
#include "scene3D.h"
#include "sceneModel.h"
#include "sceneSkinMesh.h"
#include "texture.h"
#include "billboard.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "result.h"
#include "input.h"
#include "field.h"
#include "actionBase.h"
#include "action.h"
#include "EnemyAnim.h"
#include "Effekseer.h"

void CEnemy::Init(int modelId, D3DXVECTOR3 spawnPos, int rootId, CField* field)
{
	m_Model = CSceneSkinMesh::Create(SKINMESH_SOURCE[modelId]);
	m_Pos = spawnPos;
	m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.25f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.25f);
	m_Model->Move(m_Pos);
	m_Field = field;
	m_EnemyType = ENEMY_TYPE_PATROL;
	m_Action = CActionMoveToPos::Create(this, rootId, 0.02f);

	m_Forward = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
}

void CEnemy::Init(int modelId, D3DXVECTOR3 spawnPos, CActionBase* action, CField* field, ENEMY_TYPE type)
{
	m_Model = CSceneSkinMesh::Create(SKINMESH_SOURCE[modelId]);
	m_Pos = spawnPos;
	m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.25f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.25f);
	m_Model->Move(m_Pos);
	m_Field = field;
	m_Action = action;
	m_EnemyType = type;

	m_Forward = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
}

void CEnemy::Uninit()
{
	if (m_Model)
	{
		m_Model->Release();
	}
}

void CEnemy::Update()
{
	m_OldPos = m_Pos;

	if (m_isPreDeath)
	{
		if (m_Model->GetWeightTime() >= 8.0f)
		{
			Release();
		}
	}
	else
	{
		m_Action->Update();

		Search();

		m_Pos.y = m_Field->GetHeight(m_Pos);

		// コリジョンの計算
		m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.25f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.25f);
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			CCharacter* obj = CCharacter::GetCharacter(i);
			if (obj != NULL && obj != this)
			{
				if (obj->GetType() == CHARACTER_ENEMY)
				{
					CEnemy* enemy = (CEnemy*)obj;
					if (isCollisionCapsule(m_CapsuleCollision, enemy->GetCapsule()))
					{
						D3DXVECTOR3 vec = m_Pos - enemy->GetPos();
						D3DXVec3Normalize(&vec, &vec);

						m_Pos = enemy->GetPos();
						m_Pos += vec * 0.5f;
					}
				}
			}
		}
		m_Model->Move(m_Pos);
		// 当たり判定の移動
		m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.25f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.25f);
	}
}

CEnemy* CEnemy::Create(int modelId, D3DXVECTOR3 spawnPos, int rootId, CField* field)
{
	CEnemy* enemy = new CEnemy();
	enemy->Init(modelId, spawnPos, rootId, field);

	return enemy;
}

CEnemy* CEnemy::Create(int modelId, D3DXVECTOR3 spawnPos, CActionBase* action, CField* field, ENEMY_TYPE type)
{
	CEnemy* enemy = new CEnemy();
	enemy->Init(modelId, spawnPos, action, field, type);

	return enemy;
}

void CEnemy::Search()
{
	if (!m_FindPlayer)
	{
		D3DXVECTOR3 vec = CModeGame::GetPlayer()->GetPos() - m_Pos;

		// 敵とプレイヤーの距離
		float len = D3DXVec3Length(&vec);

		D3DXVec3Normalize(&vec, &vec);

		float dot = D3DXVec3Dot(&vec, &m_Forward);
		float rad = acosf(dot);

		float degree = D3DXToDegree(rad);

		if (degree < 45.0f && len < 5.0f)
		{
			m_FindPlayer = true;
			SetAction(CActionMoveToPlayer::Create(this, CModeGame::GetPlayer(), 0.025f));
		}
	}
	else
	{
		D3DXVECTOR3 vec = CModeGame::GetPlayer()->GetPos() - m_Pos;

		// 敵とプレイヤーの距離
		float len = D3DXVec3Length(&vec);

		if (len < 0.75f)
		{
			CModeGame::PlayerDied();
		}
	}
}

void CEnemy::SetAction(CActionBase* action)
{
	if (m_Action != NULL)
	{
		m_Action->Release();
	}
	m_Action = action;
}

void CEnemy::Death()
{
	m_Model->PlayMontage(ENEMY_DEATH, 0.3f, 8.0f, ENEMY_DEATH);
	m_Model->SetAnimPlaySpeed(1.5f);
/*
	CEffekseer* effect = CEffekseer::Create(CEffekseer::Effect_BloodLoss, CModeGame::GetCamera());
	effect->RepeatEffect(false);
	effect->SetScale(0.1f, 0.1f, 0.1f);

	D3DXVECTOR3 bloodPos = m_Pos;
	bloodPos.y += 1.25f;
	effect->SetPosition(bloodPos);
	effect->Play();
	effect->SetVisible(true);
*/
	m_isPreDeath = true;
}
