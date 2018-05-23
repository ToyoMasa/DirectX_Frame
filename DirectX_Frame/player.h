#ifndef _PLAYER_H_
#define _PLAYER_H_

class CPlayer : CScene
{
public:
	CPlayer::CPlayer(int priority) : CScene(priority)
	{
		m_Model = NULL;
		m_Forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_WalkSpeed = 0.02f;
	}
	~CPlayer(){}

	void Init(int modelId, D3DXVECTOR3 spawnPos);
	void Uninit();
	void Update();
	void Draw();
	static CPlayer* Create(int modelId, D3DXVECTOR3 spawnPos);

private:
	CSceneModel *m_Model;
	D3DXVECTOR3 m_Forward;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Up;
	float m_WalkSpeed;
};

#endif // !_PLAYER_H_
