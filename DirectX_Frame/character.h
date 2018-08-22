#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "sceneSkinMesh.h"

class CCamera;
class CField;

static const int CHARACTER_MAX = 100;

enum CHARACTER_TYPE
{
	CHARACTER_NONE,
	CHARACTER_PLAYER,
	CHARACTER_ENEMY
};

class CCharacter
{
public:
	CCharacter::CCharacter()
	{
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			if (m_Characters[i] == NULL)
			{
				m_Characters[i] = this;
				m_Type = CHARACTER_NONE;
				break;
			}
		}

		m_Model = NULL;
		m_Forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_WalkSpeed = 0.02f;
		m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.5f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.5f);
		D3DXMatrixIdentity(&m_Rotate);
	}
	~CCharacter() {}

	void Init() {}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	static void UpdateAll();
	Capsule GetCapsule() { return m_CapsuleCollision; }
	CHARACTER_TYPE GetType() { return m_Type; }
	void SetField(CField* field) { m_Field = field; }
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	D3DXVECTOR3 GetPos() { return m_Pos; }
	D3DXVECTOR3 GetForward() { return m_Forward; }
	void Rotate(D3DXVECTOR3 vec);
	void Release();
	CSceneSkinMesh* GetModel() { return m_Model; }

	D3DXVECTOR3 PushOut(D3DXVECTOR3 newPos, D3DXVECTOR3 oldPos, D3DXVECTOR3 normal);

	static void ReleaseAll();
	static CCharacter* GetCharacter(int id) { return m_Characters[id]; }

protected:
	//CSceneModel *m_Model;
	CSceneSkinMesh *m_Model;
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_OldPos;
	D3DXVECTOR3 m_Forward;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Up;
	D3DXMATRIX	m_Rotate;		// ‰ñ“]s—ñ
	CField *m_Field;
	Capsule m_CapsuleCollision;
	float m_WalkSpeed;
	CHARACTER_TYPE m_Type;

private:
	static CCharacter* m_Characters[CHARACTER_MAX];
};

#endif // !_CHARACTER_H_
