//======================================================================
//	カメラ処理ヘッダ[camera.h]
//
//======================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

static const float NEAR_CLIP = 0.01f;
static const float FAR_CLIP = 1000.0f;
static const float CAMERA_MOOVE_SPEED = 0.35f;	// 移動速度
static const float CAMERA_AT_RAD = 0.3f;		// 回転速度

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
	D3DXVECTOR3 m_Pos, m_At, m_Rot;			// カメラ座標, 注視点座標, 回転座標
	D3DXVECTOR3 m_Front, m_Right, m_Up;		// 単位ベクトル
	D3DXMATRIX m_Projection;				// プロジェクション変換行列
	D3DXMATRIX m_View;						// ビュー変換行列
	float m_ArmLength;						// カメラの位置と注視点間の長さ
	float m_ArmLength2D;					// カメラの位置と注視点間の長さ(平面）
	float m_Fov;							// FOV
	float m_Dot;							// 内積の値
};

#endif // !_CAMERA_H_
