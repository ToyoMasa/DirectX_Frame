//======================================================================
//	�v���C���[�@�i2018/05/23�j
//	Author : �L�� ���r
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
#include "game.h"

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

void CCharacter::Rotate(D3DXVECTOR3 vec)
{
	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxIdentity;	// ��r�p
	D3DXVECTOR3 v1 = m_Forward;
	D3DXVECTOR3 v2 = { vec.x, 0, vec.z };

	v1.y = 0.0f;

	D3DXVec3Normalize(&v1, &v1);
	D3DXVec3Normalize(&v2, &v2);

	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixIdentity(&mtxIdentity);

	// �������Ă�����p�Ɠ��͂��ꂽ���p�̓��ς����
	float fInner = D3DXVec3Dot(&v2, &v1);

	if (fInner != 1)
	{
		float sita = fInner / (D3DXVec3Length(&v1) * D3DXVec3Length(&v2));
		float rad = acosf(fInner);
		float rot = D3DXToDegree(rad);

		CModeGame::test(rot);

		D3DXVECTOR3 cross;
		D3DXVec3Cross(&cross, &v2, &v1);

		if (cross.y < 0.0f)
		{
			if (rot > 7.0f)
			{
				// ��]�s��(Y����])�����(��]���x)
				D3DXMatrixRotationY(&mtxRot, D3DXToRadian(7.0f));
			}
			else
			{
				if (!isnan(rot))
				{
					D3DXMatrixRotationY(&mtxRot, D3DXToRadian(rot));
				}
			}
		}
		else
		{
			if (rot > 7.0f)
			{
				// ��]�s��(Y����])�����(��]���x)
				D3DXMatrixRotationY(&mtxRot, -D3DXToRadian(7.0f));
			}
			else
			{
				if (!isnan(rot))
				{
					D3DXMatrixRotationY(&mtxRot, -D3DXToRadian(rot));
				}
			}
		}

		//mtxIdentity = m_Rotate;
		m_Rotate *= mtxRot;
		m_Model->Rotate(m_Rotate);

		D3DXVec3TransformNormal(&m_Forward, &m_Forward, &mtxRot);	// �x�N�g���̍��W�ϊ�(�o��, ����, �ϊ��s��)
		D3DXVec3TransformNormal(&m_Right, &m_Right, &mtxRot);	// �x�N�g���̍��W�ϊ�(�o��, ����, �ϊ��s��)
		D3DXVec3Normalize(&m_Forward, &m_Forward);

		D3DXVec3Normalize(&m_Right, &m_Right);
	}
}