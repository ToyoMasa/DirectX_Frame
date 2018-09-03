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
#include "sceneShadow.h"
#include "texture.h"
#include "billboard.h"
#include "character.h"
#include "player.h"
#include "input.h"
#include "field.h"
#include "enemy.h"
#include "game.h"
#include "PlayerAnim.h"
#include "wall.h"

static const float VALUE_ROTATE_MOUSE = 0.003f;

void CPlayer::Init(int modelId, D3DXVECTOR3 spawnPos)
{
	m_Model = CSceneSkinMesh::Create(SKINMESH_SOURCE[SM_ID_PLAYER]);
	m_Model->ChangeAnim(PLAYER_IDLE, 0.0f);

	m_Pos = spawnPos;
	m_Model->Move(m_Pos);
	m_Camera = CCamera::Create(D3DXVECTOR3(m_Pos.x + 0.0f, m_Pos.y + 1.5f, m_Pos.z - 2.0f), m_Pos);
	m_Forward = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	m_Text_Attack = CScene2D::Create(TEX_ID_ATTACK, 128, 64);
	m_Text_Attack->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200.0f, 0.0f));
	m_Caution = CScene2D::Create(TEX_ID_CAUTION, 440, 80);
	m_Caution->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_Caution->SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	m_Caution->SetVisible(false);

	m_BloodEffect = CEffekseer::Create(CEffekseer::Effect_BloodLoss, m_Camera);
	m_BloodEffect->RepeatEffect(false);
	m_BloodEffect->SetScale(0.1f, 0.1f, 0.1f);
	m_BloodEffect->SetVisible(true);

	m_Knife = CSound::Create(SOUND_LABEL_SE_KNIFE);
	m_Hit = CSound::Create(SOUND_LABEL_SE_HIT);
}

void CPlayer::Uninit()
{
	if (m_Camera)
	{
		m_Camera->Release();
	}
	if (m_Model)
	{
		m_Model->Release();
	}
	if (m_Knife)
	{
		m_Knife->Release();
	}
}

void CPlayer::Update()
{
	CInputKeyboard *inputKeyboard;
	CInputMouse *inputMouse;
	float mouseX, mouseY, mouseZ;

	if (m_isPreDeath)
	{
		if (m_Model->GetWeightTime() >= 5.0f)
		{
			CModeGame::PlayerDied();
		}
	}
	else
	{
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

		if (!m_Model->GetPlayMontage())
		{
			{// 移動・回転
				D3DXVECTOR3 cameraFront = m_Camera->GetFront();
				D3DXVECTOR3 cameraRight = m_Camera->GetRight();
				D3DXVECTOR3 newPos = m_Pos;
				D3DXVECTOR3 moveVec = { moveX, 0.0f, moveZ };

				D3DXVec3Normalize(&moveVec, &moveVec);

				// 前方向ベクトルを地面と平行に正規化
				cameraFront.y = 0;
				D3DXVec3Normalize(&cameraFront, &cameraFront);

				newPos += cameraFront * PLAYER_MOVE_SPEED * moveVec.z;
				newPos += cameraRight * PLAYER_MOVE_SPEED * moveVec.x;
				newPos.y = m_Field->GetHeight(newPos);

				// コリジョンの計算
				m_CapsuleCollision.Set(Point(newPos.x, newPos.y + 0.25f, newPos.z), Point(newPos.x, newPos.y + 1.0f, newPos.z), 0.25f);

				// キャラクターとの当たり判定
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

							//if (isCollisionCapsule(m_AttackingCollsion, enemy->GetCapsule()) && !m_Text_Attack->GetVisible())
							//{
							//	m_Text_Attack->SetVisible(true);
							//}
						}
					}
				}

				// 壁との当たり判定
				newPos = HitWall(newPos);

				if (moveX != 0 || moveZ != 0)
				{
					Rotate(newPos - m_Pos);
				}
				m_Camera->Move(newPos - m_Pos);
				SetPos(newPos);

			}

			if (moveX != 0 || moveZ != 0)
			{
				m_Model->ChangeAnim(PLAYER_RUNNING, 0.3f);
			}
			else
			{
				m_Model->ChangeAnim(PLAYER_IDLE, 0.3f);
			}
		}

		m_Model->Move(m_Pos);
		m_Shadow->Move(m_Pos);

		// 当たり判定の移動
		m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.25f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.25f);
		D3DXVECTOR3 attackPos = m_Pos + m_Forward * 1.0f;
		m_AttackingCollsion.Set(Point(attackPos.x, attackPos.y + 0.25f, attackPos.z), Point(attackPos.x, attackPos.y + 1.0f, attackPos.z), 0.5f);

		// 攻撃
		if (inputMouse->GetLeftTrigger() || inputKeyboard->GetKeyTrigger(DIK_SPACE))
		{
			if (!m_isPreAttack)
			{
				Attack();
			}
		}

		if (m_isPreAttack)
		{
			if (m_Model->GetWeightTime() >= 1.5f)
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
								//if (enemy->GetEnemyType() == ENEMY_TYPE_TARGET)
								//{
								//	CModeGame::TargetKilled();
								//}
								//enemy->Release();

								D3DXVECTOR3 bloodPos = enemy->GetPos();
								bloodPos.y += 1.2f;
								m_BloodEffect->SetPosition(bloodPos);
								m_BloodEffect->Play();

								enemy->Death();
							}
						}
					}
				}
				m_isPreAttack = false;
			}
			else
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
								D3DXVECTOR3 rotatePos = enemy->GetPos() - m_Pos;

								Rotate(rotatePos);
							}
						}
					}
				}
			}
		}

		D3DXVECTOR3 len = D3DXVECTOR3(0, 0, 0) - m_Pos;
		if (D3DXVec3Length(&len) > 40 && !m_isGameOver)
		{
			m_Caution->SetVisible(true);

			if (D3DXVec3Length(&len) > 50)
			{
				CModeGame::PlayerDied();
				m_Caution->SetVisible(false);
				m_isGameOver = true;
			}
		}
		else
		{
			m_Caution->SetVisible(false);
		}

		// カメラの更新
		m_Camera->SetAt(D3DXVECTOR3(m_Pos.x, m_Pos.y + 1.5f, m_Pos.z));
		m_Camera->Rotation(PI * mouseX * VALUE_ROTATE_MOUSE, PI * mouseY * VALUE_ROTATE_MOUSE);
		m_Camera->Update();
	}
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
	m_Model->PlayMontage(PLAYER_STAB, 0.2f, 3.4f, PLAYER_IDLE, 2.0f);
	m_Knife->Play();

	m_isPreAttack = true;
}

void CPlayer::Death()
{
	m_Model->PlayMontage(PLAYER_DEATH, 0.3f, 8.0f, PLAYER_DEATH, 0.75f);
	m_Hit->Play();

	m_isPreDeath = true;
}
