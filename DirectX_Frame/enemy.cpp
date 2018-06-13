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
#include "texture.h"
#include "billboard.h"
#include "player.h"
#include "enemy.h"
#include "input.h"
#include "field.h"

static const float VALUE_ROTATE_MOUSE = 0.003f;

void CEnemy::Init(int modelId, D3DXVECTOR3 spawnPos)
{
	m_Model = CSceneModel::Create(MODEL_SOURCE[modelId]);
	m_Pos = spawnPos;
	m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.25f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.25f);
	m_Model->Move(m_Pos);
	m_Type = SCENE_TYPE_ENEMY;
}

void CEnemy::Uninit()
{

}

void CEnemy::Update()
{
	m_Model->Move(m_Pos);
	// 当たり判定の移動
	m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.25f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.25f);
}

void CEnemy::Draw()
{
}

CEnemy* CEnemy::Create(int modelId, D3DXVECTOR3 spawnPos)
{
	CEnemy* enemy = new CEnemy(LAYER_OBJECT3D);
	enemy->Init(modelId, spawnPos);

	return enemy;
}
