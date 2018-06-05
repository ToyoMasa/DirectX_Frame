//======================================================================
//	�����蔻�菈�� [collision.cpp]�@�i2017/12/05�j
//	Author : �L�� ���r
//======================================================================
#include "common.h"
#include "collision.h"
#include <cmath>

//======================================================================
//	���Ƌ��̓����蔻��
//======================================================================
bool isCollisionSphere(Sphere &sphere1, Sphere &sphere2)
{
	return
		(sphere2.pos.x - sphere1.pos.x) * (sphere2.pos.x - sphere1.pos.x) + 
		(sphere2.pos.y - sphere1.pos.y) * (sphere2.pos.y - sphere1.pos.y) + 
		(sphere2.pos.z - sphere1.pos.z) * (sphere2.pos.z - sphere1.pos.z) <=
		(sphere1.rad + sphere2.rad) * (sphere1.rad + sphere2.rad);
}

//======================================================================
//	OBB�Ɠ_�̋����𑪒�
//======================================================================
float LenOBBToPoint(OBB &obb, D3DXVECTOR3 &point)
{
	D3DXVECTOR3 Vec(0, 0, 0);   // �ŏI�I�ɒ��������߂�x�N�g��

	// �e���ɂ��Ă͂ݏo�������̃x�N�g�����Z�o
	for (int i = 0; i<3; i++)
	{
		float L = obb.GetLen(i);
		if (L <= 0) continue;  // L=0�͌v�Z�ł��Ȃ�
		float s = D3DXVec3Dot(&(point - obb.GetPos()), &obb.GetDirect(i)) / L;

		// s�̒l����A�͂ݏo��������������΂��̃x�N�g�������Z
		s = fabs(s);
		if (s > 1)
		{
			Vec += (1 - s)*L*obb.GetDirect(i);   // �͂ݏo���������̃x�N�g���Z�o
		}
	}

	return D3DXVec3Length(&Vec);   // �������o��
}

//======================================================================
//	OBB�Ƌ��̓����蔻��
//======================================================================
bool isCollisionOBBtoSphere(OBB &obb, Sphere &sphere)
{
	return LenOBBToPoint(obb, sphere.pos) <= sphere.rad;
}

// �������ɓ��e���ꂽ���������瓊�e���������Z�o
float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}

//======================================================================
//	OBB���m�̓����蔻��
//======================================================================
bool isCollisionOBBs(OBB &obb1, OBB &obb2)
{
	// �e�����x�N�g���̊m��
	// �iN***:�W���������x�N�g���j
	D3DXVECTOR3 NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen(0);
	D3DXVECTOR3 NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen(1);
	D3DXVECTOR3 NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen(2);
	D3DXVECTOR3 NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen(0);
	D3DXVECTOR3 NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen(1);
	D3DXVECTOR3 NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen(2);
	D3DXVECTOR3 Interval = obb1.GetPos() - obb2.GetPos();

	// ������ : Ae1
	float rA = D3DXVec3Length(&Ae1);
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = fabs(D3DXVec3Dot(&Interval, &NAe1));
	if (L > rA + rB)
		return false; // �Փ˂��Ă��Ȃ�

					  // ������ : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe2));
	if (L > rA + rB)
		return false;

	// ������ : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe3));
	if (L > rA + rB)
		return false;

	// ������ : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = fabs(D3DXVec3Dot(&Interval, &NBe1));
	if (L > rA + rB)
		return false;

	// ������ : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = fabs(D3DXVec3Dot(&Interval, &NBe2));
	if (L > rA + rB)
		return false;

	// ������ : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NBe3));
	if (L > rA + rB)
		return false;

	// ������ : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}

// �w�莲�ԍ��̕����x�N�g�����擾
D3DXVECTOR3 OBB::GetDirect(int elem)
{
	return m_NormaDirect[elem];
}

// �w�莲�����̒������擾
float OBB::GetLen(int elem)
{
	return m_fLength[elem];
}

// �ʒu���擾
D3DXVECTOR3 OBB::GetPos()
{
	return m_Pos;
}

//======================================================================
//	���ƕ��ʂ̓����蔻��(�Ώۂ̋�, ���ʏ�̓_�C���ʂ̖@���x�N�g��)
//======================================================================
bool isCollisionSpheretoPlane(Sphere &sphere, D3DXVECTOR3 &v, D3DXVECTOR3 &n)
{
	return distancePointToPlane(n, sphere.pos, v) <= sphere.rad;
}

//======================================================================
//	�����ƕ��ʂ̓����蔻��(�����̎n�_�C�����̏I�_, ���ʂ̖@���x�N�g��)
//======================================================================
bool isCollisionLinetoPlane(D3DXVECTOR3 &v1, D3DXVECTOR3 &v2, D3DXVECTOR3 &n)
{
	return D3DXVec3Dot(&v1, &n) * D3DXVec3Dot(&v2, &n) <= 0;
}

//======================================================================
//	�_�ƕ��ʂ̋������擾(���ʂ̖@���x�N�g��, �_�̍��W, ���ʏ�̓_�̍��W)
//======================================================================
float distancePointToPlane(D3DXVECTOR3 &vn, D3DXVECTOR3 &p1, D3DXVECTOR3 &p2)
{
	D3DXVECTOR3 v = p2 - p1;
	return fabs(D3DXVec3Dot(&vn, &v));
}

//======================================================================
//	2D�p�~�Ɖ~�̓����蔻��
//======================================================================
bool isCollisionCircle2D(float x0, float y0, float r0, float x1, float y1, float r1)
{
	float x = x1 - x0;
	float y = y1 - y0;
	float l = x * x + y * y;	//�Εӂ̓��̒����i��擯�m�Ōv�Z����j

	return l < (r0 + r1) * (r0 + r1);
}

//======================================================================
//�@2D�p���Ɛ��̓����蔻��
//======================================================================
bool isCollisionLine2D(D3DXVECTOR3 r1, D3DXVECTOR3 r2, D3DXVECTOR3 p1, D3DXVECTOR3 p2)
{
	float t1, t2;

	//2�_r1-r2��ʂ钼���ɑ΂��Ap1�Ap2���ǂ̈ʒu�ɂ��邩�v�Z����
	t1 = (r1.x - r2.x) * (p1.y - r1.z) + (r1.y - r2.z) * (r1.x - p1.x);
	t2 = (r1.x - r2.x) * (p2.y - r1.z) + (r1.y - r2.z) * (r1.x - p2.x);

	//���ꂼ��̐������قȂ�i�ς����ɂȂ�j���A0�i�_��������ɂ���j
	//�Ȃ�N���X���Ă���
	if (t1 * t2 < 0 || t1 == 0 || t2 == 0)
	{
		return true; //�N���X���Ă���
	}
	else
	{
		return false; //�N���X���Ȃ�
	}
}

bool onPolygon(D3DXVECTOR3 &target, D3DXVECTOR3 &p0, D3DXVECTOR3 &p1, D3DXVECTOR3 &p2)
{
	float cross1, cross2, cross3;
	D3DXVECTOR3 V0P, V1P, V2P, V01, V12, V20;

	V0P = target - p0;
	V1P = target - p1;
	V2P = target - p2;
	V01 = p1 - p0;
	V12 = p2 - p1;
	V20 = p0 - p1;

	cross1 = V01.x * V0P.z - V01.z * V0P.x;
	cross2 = V12.x * V1P.z - V12.z * V1P.x;
	cross3 = V20.x * V2P.z - V20.z * V2P.x;

	if (cross1 <= 0.0f)
	{
		if (cross2 <= 0.0f)
		{
			if (cross3 <= 0.0f)
			{
				return true;
			}
		}
	}

	return false;
}
