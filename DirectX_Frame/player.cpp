//======================================================================
//	プレイヤー　（2018/05/23）
//	Author : 豊村 昌俊
//======================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "camera.h"
#include "scene.h"
#include "scene2D.h"
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
	//m_FBX = CSceneModelFBX::Create(FBX_MODEL_SOURCE[FBX_ID_XBOT]);
	m_Pos = spawnPos;
	m_Model->Move(m_Pos);
	m_Camera = CCamera::Create(D3DXVECTOR3(0.0f, 1.5f, -2.0f), m_Pos);
	m_Forward.z = -1.0f;

	m_Text_Attack = CScene2D::Create(TEX_ID_ATTACK, 128, 64);
	m_Text_Attack->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200.0f, 0.0f));
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

	// 攻撃可能か表示を一旦リセット
	m_Text_Attack->SetVisible(false);

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
		Rotate(m_Camera->GetFront());

		D3DXVECTOR3 cameraFront = m_Camera->GetFront();
		D3DXVECTOR3 cameraRight = m_Camera->GetRight();
		D3DXVECTOR3 newPos = m_Pos;
		D3DXVECTOR3 moveVec = { moveX, 0.0f, moveZ };
		
		D3DXVec3Normalize(&moveVec, &moveVec);

		// 前方向ベクトルを地面と平行に正規化
		cameraFront.y = 0;
		D3DXVec3Normalize(&cameraFront, &cameraFront);

		newPos += cameraRight * PLAYER_MOVE_SPEED * moveX;
		newPos += cameraFront * PLAYER_MOVE_SPEED * moveZ;
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
					}

					if (isCollisionCapsule(m_AttackingCollsion, enemy->GetCapsule()) && !m_Text_Attack->GetVisible())
					{
						m_Text_Attack->SetVisible(true);
					}
				}
			}
		}

		m_Camera->Move(newPos - m_Pos);
		SetPos(newPos);
	}

	m_Model->Move(m_Pos);
	// 当たり判定の移動
	m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.25f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.25f);
	D3DXVECTOR3 attackPos = m_Pos + m_Forward * 0.5f;
	m_AttackingCollsion.Set(Point(attackPos.x, attackPos.y + 0.25f, attackPos.z), Point(attackPos.x, attackPos.y + 1.0f, attackPos.z), 0.5f);

	// 攻撃
	if (inputMouse->GetLeftTrigger() || inputKeyboard->GetKeyTrigger(DIK_SPACE))
	{
		Attack();
	}

	m_Camera->SetAt(D3DXVECTOR3(m_Pos.x, m_Pos.y + 1.5f, m_Pos.z));
	m_Camera->Rotation(PI * mouseX * VALUE_ROTATE_MOUSE, PI * mouseY * VALUE_ROTATE_MOUSE);
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

void CPlayer::Attack()
{
	if (m_Text_Attack->GetVisible())
	{
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			CCharacter* obj = CCharacter::GetCharacter(i);
			if (obj != NULL)
			{
				if (obj->GetType() == CHARACTER_ENEMY)
				{
					CEnemy* enemy = (CEnemy*)obj;
					if (isCollisionCapsule(m_AttackingCollsion, enemy->GetCapsule()))
					{
						enemy->Release();
					}
				}
			}
		}
	}
}

//
//void CPlayer::Rotate(float x, float z)
//{
//	D3DXMATRIX mtxRot;
//	D3DXVECTOR3 v1 = m_Forward;
//	D3DXVECTOR3 v2 = { -z, 0, x };
//
//	v1.y = 0.0f;
//
//	D3DXVec3Normalize(&v1, &v1);
//	D3DXVec3Normalize(&v2, &v2);
//
//	// 今向いている方角と入力された方角の内積を取る
//	float fInner = D3DXVec3Dot(&v1, &v2);
//
//	// 回転行列(Y軸回転)を作る(回転速度)
//	D3DXMatrixRotationY(&mtxRot, fInner / 10);
//	m_Rotate *= mtxRot;
//	m_Model->Rotate(m_Rotate);
//
//	D3DXVec3TransformNormal(&m_Forward, &m_Forward, &mtxRot);	// ベクトルの座標変換(出力, 入力, 変換行列)
//	D3DXVec3TransformNormal(&m_Right, &m_Right, &mtxRot);	// ベクトルの座標変換(出力, 入力, 変換行列)
//	D3DXVec3Normalize(&m_Forward, &m_Forward);
//	D3DXVec3Normalize(&m_Right, &m_Right);
//}

//void CPlayer::Rotate(D3DXVECTOR3 vec)
//{
//	D3DXMATRIX mtxRot;
//	D3DXVECTOR3 v1 = m_Forward;
//	D3DXVECTOR3 v2 = { -vec.z, 0, vec.x };
//
//	v1.y = 0.0f;
//
//	D3DXVec3Normalize(&v1, &v1);
//	D3DXVec3Normalize(&v2, &v2);
//
//	// 今向いている方角と入力された方角の内積を取る
//	float fInner = D3DXVec3Dot(&v1, &v2);
//
//	// 回転行列(Y軸回転)を作る(回転速度)
//	D3DXMatrixRotationY(&mtxRot, fInner / 10);
//	m_Rotate *= mtxRot;
//	m_Model->Rotate(m_Rotate);
//
//	D3DXVec3TransformNormal(&m_Forward, &m_Forward, &mtxRot);	// ベクトルの座標変換(出力, 入力, 変換行列)
//	D3DXVec3TransformNormal(&m_Right, &m_Right, &mtxRot);	// ベクトルの座標変換(出力, 入力, 変換行列)
//	D3DXVec3Normalize(&m_Forward, &m_Forward);
//	D3DXVec3Normalize(&m_Right, &m_Right);
//}