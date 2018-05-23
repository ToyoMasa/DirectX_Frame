//======================================================================
//	プレイヤー　（2018/05/23）
//	Author : 豊村 昌俊
//======================================================================
#include "common.h"
#include "main.h"
#include "camera.h"
#include "scene.h"
#include "scene3D.h"
#include "sceneModel.h"
#include "texture.h"
#include "billboard.h"
#include "player.h"

void CPlayer::Init(int modelId, D3DXVECTOR3 spawnPos)
{
	m_Model = CSceneModel::Create(MODEL_SOURCE[modelId]);
	m_Pos = spawnPos;
	m_Model->Move(m_Pos);
}

void CPlayer::Uninit()
{

}

void CPlayer::Update()
{

}

void CPlayer::Draw()
{

}

CPlayer* CPlayer::Create(int modelId, D3DXVECTOR3 spawnPos)
{
	CPlayer* player = new CPlayer(1);
	player->Init(modelId, spawnPos);

	return player;
}
