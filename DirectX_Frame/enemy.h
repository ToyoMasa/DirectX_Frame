#ifndef _ENEMY_H_
#define _ENEMY_H_

class CCamera;
class CField;
static const float ENEMY_MOVE_SPEED = 0.03f;

class CEnemy : public CScene
{
public:
	CEnemy::CEnemy(int priority) : CScene(priority)
	{
		m_Model = NULL;
		m_Forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_WalkSpeed = 0.02f;
		m_CameraLength = 2.0f;
		m_CapsuleCollision.Set(Point(m_Pos.x, m_Pos.y + 0.5f, m_Pos.z), Point(m_Pos.x, m_Pos.y + 1.0f, m_Pos.z), 0.5f);
	}
	~CEnemy() {}

	void Init(int modelId, D3DXVECTOR3 spawnPos);
	void Uninit();
	void Update();
	void Draw();
	void SetField(CField* field) { m_Field = field; }
	static CEnemy* Create(int modelId, D3DXVECTOR3 spawnPos);
	Capsule GetCapsule() { return m_CapsuleCollision; }

private:
	CSceneModel *m_Model;
	D3DXVECTOR3 m_Forward;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Up;
	CField *m_Field;
	Capsule m_CapsuleCollision;
	float m_WalkSpeed;
	float m_CameraLength;
};

#endif // !_ENEMY_H_
