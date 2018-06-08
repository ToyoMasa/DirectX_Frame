#ifndef _PLAYER_H_
#define _PLAYER_H_

class CCamera;
class CField;
static const float PLAYER_MOVE_SPEED = 0.03f;

class CPlayer : public CScene
{
public:
	CPlayer::CPlayer(int priority) : CScene(priority)
	{
		m_Model = NULL;
		m_Forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_WalkSpeed = 0.02f;
		m_CameraLength = 2.0f;
		m_Camera = NULL;
	}
	~CPlayer(){}

	void Init(int modelId, D3DXVECTOR3 spawnPos);
	void Uninit();
	void Update();
	void Draw();
	CCamera* GetCamera() { return m_Camera; }
	void SetField(CField* field) { m_Field = field; }
	static CPlayer* Create(int modelId, D3DXVECTOR3 spawnPos);

private:
	CSceneModel *m_Model;
	D3DXVECTOR3 m_Forward;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Up;
	CCamera *m_Camera;
	CField *m_Field;
	float m_WalkSpeed;
	float m_CameraLength;
};

#endif // !_PLAYER_H_
