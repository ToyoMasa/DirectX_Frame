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
	void SetPos(D3DXVECTOR3 pos);
	void SetAt(D3DXVECTOR3 at);
	void SetFov(float fov);
	void Move(float horizontal, float vertical);
	void Rotation(float horizontal, float vertical);
	static CCamera* Create();

private:
	D3DXVECTOR3 m_Pos, m_At;				// �J�������W, �����_���W
	D3DXVECTOR3 m_Front, m_Right, m_Up;		// �P�ʃx�N�g��
	D3DXMATRIX m_Projection;				// �v���W�F�N�V�����ϊ��s��
	D3DXMATRIX m_View;						// �r���[�ϊ��s��
	float m_Fov;							// FOV
	float m_Dot;							// ���ς̒l
};

#endif // !_CAMERA_H_
