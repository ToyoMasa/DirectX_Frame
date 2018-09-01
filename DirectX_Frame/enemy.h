#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"
#include "actionBase.h"

static const float ENEMY_MOVE_SPEED = 0.03f;

typedef enum
{
	ENEMY_TYPE_PATROL = 0,
	ENEMY_TYPE_TARGET,
} ENEMY_TYPE;

class CEnemy : public CCharacter
{
public:
	CEnemy::CEnemy() : CCharacter() 
	{
		m_Type = CHARACTER_ENEMY;
		m_FindPlayer = false;
		m_Action = NULL;
		m_isPreDeath = false;
		m_isPreAttack = false;
	}
	~CEnemy() {}

	void Init(int modelId, D3DXVECTOR3 spawnPos, int rootId, CField* field);
	void Init(int modelId, D3DXVECTOR3 spawnPos, int rootId, CField* field, ENEMY_TYPE type);
	void Init(int modelId, D3DXVECTOR3 spawnPos, CActionBase* action, CField* field, ENEMY_TYPE type);
	void Uninit();
	void Update();
	void SetField(CField* field) { m_Field = field; }
	void SetAction(CActionBase* action);
	void ReleaseAction() { delete m_Action; }
	static CEnemy* Create(int modelId, D3DXVECTOR3 spawnPos, int rootId, CField* field);
	static CEnemy* Create(int modelId, D3DXVECTOR3 spawnPos, int rootId, CField* field, ENEMY_TYPE type);
	static CEnemy* Create(int modelId, D3DXVECTOR3 spawnPos, CActionBase* action, CField* field, ENEMY_TYPE type);
	Capsule GetCapsule() { return m_CapsuleCollision; }
	ENEMY_TYPE GetEnemyType() { return m_EnemyType; }
	void Search();
	void Death();
	void Attack();

private:
	CActionBase* m_Action;
	ENEMY_TYPE m_EnemyType;
	Capsule m_AttackingCollsion;
	bool m_FindPlayer;
	bool m_isPreDeath;
	bool m_isPreAttack;
};

#endif // !_ENEMY_H_
