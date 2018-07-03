//======================================================================
//	�J���������w�b�_[camera.h]
//
//======================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

static const float NEAR_CLIP = 0.01f;
static const float FAR_CLIP = 1000.0f;
static const float CAMERA_MOOVE_SPEED = 0.35f;	// �ړ����x
static const float CAMERA_AT_RAD = 0.3f;		// ��]���x

class CCamera : public CGameObject
{
public:
	CCamera();
	~CCamera();

	void Init();
	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 at);
	void Uninit();
	void Update();
	D3DXVECTOR3 GetPos() { return m_Pos; }
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetAt() { return m_At; }
	void SetAt(D3DXVECTOR3 at);
	D3DXVECTOR3 GetRot() { return m_Rot; }
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }
	void SetFov(float fov);
	float GetArmLength() { return m_ArmLength; }
	void SetArmLength(float value) { m_ArmLength = value; }
	float GetArmLength2D() { return m_ArmLength2D; }
	void SetArmLength2D(float value) { m_ArmLength2D = value; }
	void Move(float horizontal, float vertical);
	void Rotation(float horizontal, float vertical);
	D3DXMATRIX GetView();
	static CCamera* Create();

private:
	D3DXVECTOR3 m_Pos, m_At, m_Rot;			// �J�������W, �����_���W, ��]���W
	D3DXVECTOR3 m_Front, m_Right, m_Up;		// �P�ʃx�N�g��
	D3DXMATRIX m_Projection;				// �v���W�F�N�V�����ϊ��s��
	D3DXMATRIX m_View;						// �r���[�ϊ��s��
	float m_ArmLength;						// �J�����̈ʒu�ƒ����_�Ԃ̒���
	float m_ArmLength2D;					// �J�����̈ʒu�ƒ����_�Ԃ̒���(���ʁj
	float m_Fov;							// FOV
	float m_Dot;							// ���ς̒l
};

#endif // !_CAMERA_H_
