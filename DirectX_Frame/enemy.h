#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"

static const float ENEMY_MOVE_SPEED = 0.03f;

class CEnemy : public CCharacter
{
public:
	CEnemy::CEnemy() : CCharacter() { m_Type = CHARACTER_ENEMY; }
	~CEnemy() {}

	void Init(int modelId, D3DXVECTOR3 spawnPos);
	void Uninit();
	void Update();
	void SetField(CField* field) { m_Field = field; }
	static CEnemy* Create(int modelId, D3DXVECTOR3 spawnPos);
	Capsule GetCapsule() { return m_CapsuleCollision; }

private:
};

#endif // !_ENEMY_H_
