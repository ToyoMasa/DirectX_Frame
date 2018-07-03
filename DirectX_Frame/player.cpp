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
#include "character.h"
#include "player.h"
#include "input.h"
#include "field.h"
#include "enemy.h"

static const float VALUE_ROTATE_MOUSE = 0.003f;

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
	m_Model->Release();
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

	float moveX = 0.0f, moveZ = 0.0f;
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
		moveZ = 1.0f;
	}
	if (inputKeyboard->GetKeyPress(DIK_S))
	{
		moveZ = -1.0f;
	}

	{
		Rotate(moveX, moveZ);

		D3DXVECTOR3 newPos = m_Pos;
		D3DXVECTOR3 moveVec = { moveX, 0.0f, moveZ };
		
		D3DXVec3Normalize(&moveVec, &moveVec);

		newPos += moveVec * PLAYER_MOVE_SPEED;
		newPos.y = m_Field->GetHeight(newPos);

		// コリジョンの計算
		m_CapsuleCollision.Set(Point(newPos.x, newPos.y + 0.25f, newPos.z), Point(newPos.x, newPos.y + 1.0f, newPos.z), 0.25f);
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			CCharacter* obj = CCharacter::GetCharacter(i);
			if (obj != NULL)
			{
				if (obj->GetType() == CHARACTER_ENEMY)
				{
					CEnemy* enemy = (CEnemy*)obj;
					if (isCollisionCapsule(m_CapsuleCollision, enemy->GetCapsule()))
					{
						D3DXVECTOR3 vec = newPos - enemy->GetPos();
						D3DXVec3Normalize(&vec, &vec);

						newPos = enemy->GetPos();
						newPos += vec * 0.5f;

						break;
					}
				}
			}
		}

		SetPos(newPos);
	}

	m_Model->Move(m_Pos);
	// 当たり判定の移動
	m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.25f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.25f);

	// カメラ回転
	//D3DXVECTOR3 mouseRot = m_Camera->GetRot();
	//D3DXVECTOR3 mousePos = m_Camera->GetPos();
	//D3DXVECTOR3 mouseAt = m_Camera->GetAt();

	//if (mouseX < 0)
	//{// 視点移動「左」
	//	mouseRot.y -= PI * mouseX * VALUE_ROTATE_MOUSE;
	//	if (mouseRot.y < -PI)
	//	{
	//		mouseRot.y += PI*2.0f;
	//	}

	//	mousePos.x = mouseAt.x - sinf(mouseRot.y) * m_Camera->GetArmLength2D();
	//	mousePos.z = mouseAt.z - cosf(mouseRot.y) * m_Camera->GetArmLength2D();
	//}
	//else if (mouseX > 0)
	//{// 視点移動「右」
	//	mouseRot.y -= PI * mouseX * VALUE_ROTATE_MOUSE;
	//	if (mouseRot.y > PI)
	//	{
	//		mouseRot.y -= PI*2.0f;
	//	}

	//	mousePos.x = mouseAt.x - sinf(mouseRot.y) * m_Camera->GetArmLength2D();
	//	mousePos.z = mouseAt.z - cosf(mouseRot.y) * m_Camera->GetArmLength2D();
	//}

	//if (mouseY < 0)
	//{// 視点移動「上」
	//	mouseRot.x -= PI * mouseY * VALUE_ROTATE_MOUSE;
	//	if (mouseRot.x >(PI / 2.0f - PI*0.02f))
	//	{
	//		mouseRot.x = (PI / 2.0f - PI*0.02f);
	//	}

	//	mousePos.y = mouseAt.y - sinf(mouseRot.x) * m_Camera->GetArmLength();

	//	m_Camera->SetArmLength2D(cosf(mouseRot.x) * m_Camera->GetArmLength());
	//	mousePos.x = mouseAt.x - sinf(mouseRot.y) * m_Camera->GetArmLength2D();
	//	mousePos.z = mouseAt.z - cosf(mouseRot.y) * m_Camera->GetArmLength2D();
	//}
	//else if (mouseY > 0)
	//{// 視点移動「下」
	//	mouseRot.x -= PI * mouseY * VALUE_ROTATE_MOUSE;
	//	if (mouseRot.x < (-PI / 2.0f + PI*0.02f))
	//	{
	//		mouseRot.x = (-PI / 2.0f + PI*0.02f);
	//	}

	//	mousePos.y = mouseAt.y - sinf(mouseRot.x) * m_Camera->GetArmLength();

	//	m_Camera->SetArmLength2D(cosf(mouseRot.x) * m_Camera->GetArmLength());
	//	mousePos.x = mouseAt.x - sinf(mouseRot.y) * m_Camera->GetArmLength2D();
	//	mousePos.z = mouseAt.z - cosf(mouseRot.y) * m_Camera->GetArmLength2D();
	//}

	//m_Camera->SetPos(mousePos);
	//m_Camera->SetRot(mouseRot);

	m_Camera->SetAt(D3DXVECTOR3(m_Pos.x, m_Pos.y + 1.5f, m_Pos.z));
	m_Camera->SetPos(D3DXVECTOR3(m_Pos.x, m_Pos.y + 2.0f, m_Pos.z - 2.0f));
	m_Camera->Update();
}

void CPlayer::Draw()
{
}

CPlayer* CPlayer::Create(int modelId, D3DXVECTOR3 spawnPos)
{
	CPlayer* player = new CPlayer();
	player->Init(modelId, spawnPos);

	return player;
}

void CPlayer::Rotate(float x, float z)
{
	D3DXMATRIX mtxRot;
	D3DXVECTOR3 v1 = m_Forward;
	D3DXVECTOR3 v2 = { -z, 0, x };

	v1.y = 0.0f;

	D3DXVec3Normalize(&v1, &v1);
	D3DXVec3Normalize(&v2, &v2);

	// 今向いている方角と入力された方角の内積を取る
	float fInner = D3DXVec3Dot(&v1, &v2);

	// 回転行列(Y軸回転)を作る(回転速度)
	D3DXMatrixRotationY(&mtxRot, fInner / 20);
	m_Rotate *= mtxRot;
	m_Model->Rotate(m_Rotate);

	D3DXVec3TransformNormal(&m_Forward, &m_Forward, &mtxRot);	// ベクトルの座標変換(出力, 入力, 変換行列)
	D3DXVec3TransformNormal(&m_Right, &m_Right, &mtxRot);	// ベクトルの座標変換(出力, 入力, 変換行列)
	D3DXVec3Normalize(&m_Forward, &m_Forward);
	D3DXVec3Normalize(&m_Right, &m_Right);
}