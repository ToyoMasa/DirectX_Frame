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
	D3DXVECTOR3 v1 = m_Forward;
	D3DXVECTOR3 v2 = { -vec.z, 0, vec.x };

	v1.y = 0.0f;

	D3DXVec3Normalize(&v1, &v1);
	D3DXVec3Normalize(&v2, &v2);

	// �������Ă�����p�Ɠ��͂��ꂽ���p�̓��ς����
	float fInner = D3DXVec3Dot(&v1, &v2);

	// ��]�s��(Y����])�����(��]���x)
	D3DXMatrixRotationY(&mtxRot, fInner / 10);
	m_Rotate *= mtxRot;
	m_Model->Rotate(m_Rotate);

	D3DXVec3TransformNormal(&m_Forward, &m_Forward, &mtxRot);	// �x�N�g���̍��W�ϊ�(�o��, ����, �ϊ��s��)
	D3DXVec3TransformNormal(&m_Right, &m_Right, &mtxRot);	// �x�N�g���̍��W�ϊ�(�o��, ����, �ϊ��s��)
	D3DXVec3Normalize(&m_Forward, &m_Forward);
	D3DXVec3Normalize(&m_Right, &m_Right);
}