#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"
#include "actionBase.h"

static const float ENEMY_MOVE_SPEED = 0.03f;

class CEnemy : public CCharacter
{
public:
	CEnemy::CEnemy() : CCharacter() 
	{
		m_Type = CHARACTER_ENEMY;
		m_FindPlayer = false;
	}
	~CEnemy() {}

	void Init(int modelId, D3DXVECTOR3 spawnPos, int rootId, CField* field);
	void Uninit();
	void Update();
	void SetField(CField* field) { m_Field = field; }
	void SetAction(CActionBase* action);
	void ReleaseAction() { delete m_Action; }
	static CEnemy* Create(int modelId, D3DXVECTOR3 spawnPos, int rootId, CField* field);
	Capsule GetCapsule() { return m_CapsuleCollision; }
	void Search();

private:
	CActionBase* m_Action;
	bool m_FindPlayer;
};

#endif // !_ENEMY_H_
