#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"
static const float PLAYER_MOVE_SPEED = 0.03f;

class CPlayer : public CCharacter
{
public:
	CPlayer::CPlayer() : CCharacter()
	{
		m_Type = CHARACTER_PLAYER;
		m_CameraLength = 2.0f;
		m_Camera = NULL;
	}
	~CPlayer(){}

	void Init(int modelId, D3DXVECTOR3 spawnPos);
	void Uninit()override;
	void Update()override;
	void Draw();
	void Rotate(float x, float z);
	void Rotate(D3DXVECTOR3 vec);
	CCamera* GetCamera() { return m_Camera; }
	static CPlayer* Create(int modelId, D3DXVECTOR3 spawnPos);

private:
	CCamera* m_Camera;
	float m_CameraLength;
	CSceneModelFBX* m_FBX;
};

#endif // !_PLAYER_H_
