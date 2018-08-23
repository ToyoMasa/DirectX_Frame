#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"
#include "sceneSkinMesh.h"
#include "Effekseer.h"

static const float PLAYER_MOVE_SPEED = 0.08f;

class CScene2D;

class CPlayer : public CCharacter
{
public:
	CPlayer::CPlayer() : CCharacter()
	{
		m_Type = CHARACTER_PLAYER;
		m_CameraLength = 2.0f;
		m_Camera = NULL;
		m_Text_Attack = NULL;
		m_isPreAttack = false;
	}
	~CPlayer(){}

	void Init(int modelId, D3DXVECTOR3 spawnPos);
	void Uninit()override;
	void Update()override;
	void Draw();
	CCamera* GetCamera() { return m_Camera; }
	static CPlayer* Create(int modelId, D3DXVECTOR3 spawnPos);

	void Attack();

private:
	CCamera* m_Camera;
	float m_CameraLength;
	CScene2D* m_Text_Attack;
	Capsule m_AttackingCollsion;
	bool m_isPreAttack;

	CEffekseer* m_BloodEffect;
};

#endif // !_PLAYER_H_
