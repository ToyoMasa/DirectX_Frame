//======================================================================
//	キャラクターの基底クラス[character.h]
//
//======================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "sceneSkinMesh.h"

class CCamera;
class CField;
class CSceneShadow;

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
	CCharacter();
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
	void SetRotation(D3DXVECTOR3 vec);
	void Rotate(D3DXVECTOR3 vec);
	void Release();
	CSceneSkinMesh* GetModel() { return m_Model; }

	D3DXVECTOR3 PushOut(D3DXVECTOR3 newPos, D3DXVECTOR3 oldPos, D3DXVECTOR3 normal);
	D3DXVECTOR3 HitWall(D3DXVECTOR3 newPos);

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
	D3DXMATRIX	m_Rotate;		// 回転行列
	CField *m_Field;
	Capsule m_CapsuleCollision;
	float m_WalkSpeed;
	CHARACTER_TYPE m_Type;
	CSceneShadow *m_Shadow;
private:
	static CCharacter* m_Characters[CHARACTER_MAX];
};

#endif // !_CHARACTER_H_
