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

void CPlayer::Init(int modelId, D3DXVECTOR3 spawnPos)
{
	m_Model = CSceneModel::Create(MODEL_SOURCE[modelId]);
	m_Pos = spawnPos;
	m_Model->Move(m_Pos);
	m_Camera = CCamera::Create();
}

void CPlayer::Uninit()
{
	m_Camera->Release();
}

void CPlayer::Update()
{
	CInputKeyboard *inputKeyboard;
	CInputMouse *inputMouse;
	float mouseX, mouseY, mouseZ;

	// キーボード取得
	inputKeyboard = CManager::GetInputKeyboard();

	// マウス取得
	inputMouse = CManager::GetInputMouse();
	mouseX = (float)inputMouse->GetAxisX();
	mouseY = (float)inputMouse->GetAxisY();
	mouseZ = (float)inputMouse->GetAxisZ();

	float moveX = 0.0f, moveY = 0.0f;
	if (inputKeyboard->GetKeyPress(DIK_A))
	{
		moveX = -1.0f;
	}
	if (inputKeyboard->GetKeyPress(DIK_D))
	{
		moveX = 1.0f;
	}
	if (inputKeyboard->GetKeyPress(DIK_W))
	{
		moveY = 1.0f;
	}
	if (inputKeyboard->GetKeyPress(DIK_S))
	{
		moveY = -1.0f;
	}

	{
		D3DXVECTOR3 newPos = GetPos();
		newPos.x += moveX * PLAYER_MOVE_SPEED;
		newPos.z += moveY * PLAYER_MOVE_SPEED;
		Set(newPos);
	}

	m_Model->Move(m_Pos);

	m_Camera->SetAt(m_Pos);
	m_Camera->SetPos(D3DXVECTOR3(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z - 2.0f));
	m_Camera->Update();
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
