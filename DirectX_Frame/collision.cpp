//======================================================================
//	当たり判定処理 [collision.cpp]　（2017/12/05）
//	Author : 豊村 昌俊
//======================================================================
#include "common.h"
#include "collision.h"
#include <cmath>

//======================================================================
//	球と球の当たり判定
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
//	OBBと点の距離を測定
//======================================================================
float LenOBBToPoint(OBB &obb, D3DXVECTOR3 &point)
{
	D3DXVECTOR3 Vec(0, 0, 0);   // 最終的に長さを求めるベクトル

	// 各軸についてはみ出た部分のベクトルを算出
	for (int i = 0; i<3; i++)
	{
		float L = obb.GetLen(i);
		if (L <= 0) continue;  // L=0は計算できない
		float s = D3DXVec3Dot(&(point - obb.GetPos()), &obb.GetDirect(i)) / L;

		// sの値から、はみ出した部分があればそのベクトルを加算
		s = fabs(s);
		if (s > 1)
		{
			Vec += (1 - s)*L*obb.GetDirect(i);   // はみ出した部分のベクトル算出
		}
	}

	return D3DXVec3Length(&Vec);   // 長さを出力
}

//======================================================================
//	OBBと球の当たり判定
//======================================================================
bool isCollisionOBBtoSphere(OBB &obb, Sphere &sphere)
{
	return LenOBBToPoint(obb, sphere.pos) <= sphere.rad;
}

// 分離軸に投影された軸成分から投影線分長を算出
float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}

//======================================================================
//	OBB同士の当たり判定
//======================================================================
bool isCollisionOBBs(OBB &obb1, OBB &obb2)
{
	// 各方向ベクトルの確保
	// （N***:標準化方向ベクトル）
	D3DXVECTOR3 NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen(0);
	D3DXVECTOR3 NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen(1);
	D3DXVECTOR3 NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen(2);
	D3DXVECTOR3 NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen(0);
	D3DXVECTOR3 NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen(1);
	D3DXVECTOR3 NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen(2);
	D3DXVECTOR3 Interval = obb1.GetPos() - obb2.GetPos();

	// 分離軸 : Ae1
	float rA = D3DXVec3Length(&Ae1);
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = fabs(D3DXVec3Dot(&Interval, &NAe1));
	if (L > rA + rB)
		return false; // 衝突していない

					  // 分離軸 : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe2));
	if (L > rA + rB)
		return false;

	// 分離軸 : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe3));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = fabs(D3DXVec3Dot(&Interval, &NBe1));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = fabs(D3DXVec3Dot(&Interval, &NBe2));
	if (L > rA + rB)
		return false;

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NBe3));
	if (L > rA + rB)
		return false;

	// 分離軸 : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離軸 : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

// 指定軸番号の方向ベクトルを取得
D3DXVECTOR3 OBB::GetDirect(int elem)
{
	return m_NormalDirect[elem];
}

// 指定軸方向の長さを取得
float OBB::GetLen(int elem)
{
	return m_fLength[elem];
}

// 位置を取得
D3DXVECTOR3 OBB::GetPos()
{
	return m_Pos;
}

//======================================================================
//	球と平面の当たり判定(対象の球, 平面上の点，平面の法線ベクトル)
//======================================================================
bool isCollisionSpheretoPlane(Sphere &sphere, D3DXVECTOR3 &v, D3DXVECTOR3 &n)
{
	return distancePointToPlane(n, sphere.pos, v) <= sphere.rad;
}

//======================================================================
//	線分と平面の当たり判定(線分の始点，線分の終点, 平面の法線ベクトル)
//======================================================================
bool isCollisionLinetoPlane(D3DXVECTOR3 &v1, D3DXVECTOR3 &v2, D3DXVECTOR3 &n)
{
	return D3DXVec3Dot(&v1, &n) * D3DXVec3Dot(&v2, &n) <= 0;
}

//======================================================================
//	点と平面の距離を取得(平面の法線ベクトル, 点の座標, 平面上の点の座標)
//======================================================================
float distancePointToPlane(D3DXVECTOR3 &vn, D3DXVECTOR3 &p1, D3DXVECTOR3 &p2)
{
	D3DXVECTOR3 v = p2 - p1;
	return fabs(D3DXVec3Dot(&vn, &v));
}

//======================================================================
//	2D用円と円の当たり判定
//======================================================================
bool isCollisionCircle2D(float x0, float y0, float r0, float x1, float y1, float r1)
{
	float x = x1 - x0;
	float y = y1 - y0;
	float l = x * x + y * y;	//斜辺の二乗の長さ（二乗同士で計算する）

	return l < (r0 + r1) * (r0 + r1);
}

//======================================================================
//　2D用線と線の当たり判定
//======================================================================
bool isCollisionLine2D(D3DXVECTOR3 &r1, D3DXVECTOR3 &r2, D3DXVECTOR3 &p1, D3DXVECTOR3 &p2)
{
	float t1, t2;

	//2点r1-r2を通る直線に対し、p1、p2がどの位置にあるか計算する
	t1 = (r1.x - r2.x) * (p1.y - r1.z) + (r1.y - r2.z) * (r1.x - p1.x);
	t2 = (r1.x - r2.x) * (p2.y - r1.z) + (r1.y - r2.z) * (r1.x - p2.x);

	//それぞれの正負が異なる（積が負になる）か、0（点が直線上にある）
	//ならクロスしている
	if (t1 * t2 < 0 || t1 == 0 || t2 == 0)
	{
		return true; //クロスしている
	}
	else
	{
		return false; //クロスしない
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

// 点と直線の最短距離
// p : 点
// l : 直線
// h : 点から下ろした垂線の足（戻り値）
// t :ベクトル係数（戻り値）
// 戻り値: 最短距離
float calcPointLineDist(const Point &p, const Line &l, Point &h, float &s) {

	float lenSqV = l.v.lengthSq();
	float t = 0.0f;
	if (lenSqV > 0.0f)
		t = l.v.dot(p - l.p) / lenSqV;

	h = l.p + s * l.v;
	return (h - p).length();
}

// ∠p1p2p3は鋭角？
bool isSharpAngle(const Point &p1, const Point &p2, const Point &p3)
{
	Vec3 p12(p1 - p2);

	return p12.isSharpAngle(p3 - p2);
}

// 点と線分の最短距離
// p : 点
// seg : 線分
// h : 最短距離となる端点（戻り値）
// t : 端点位置（ t < 0: 始点の外, 0 <= t <= 1: 線分内, t > 1: 終点の外 ） 
// 戻り値: 最短距離
float calcPointSegmentDist(const Point &p, const Segment &seg, Point &h, float &t) {

	const Point e = seg.getEndPoint();

	// 垂線の長さ、垂線の足の座標及びtを算出
	float len = calcPointLineDist(p, Line(seg.p, e - seg.p), h, t);

	if (isSharpAngle(p, seg.p, e) == false) {
		// 始点側の外側
		h = seg.p;
		return (seg.p - p).length();
	}
	else if (isSharpAngle(p, e, seg.p) == false) {
		// 終点側の外側
		h = e;
		return (e - p).length();
	}

	return len;
}

// 2直線の最短距離
// l1 : L1
// l2 : L2
// p1 : L1側の垂線の足（戻り値）
// p2 : L2側の垂線の足（戻り値）
// t1 : L1側のベクトル係数（戻り値）
// t2 : L2側のベクトル係数（戻り値）
// 戻り値: 最短距離
float calcLineLineDist(const Line &l1, const Line &l2, Point &p1, Point &p2, float &t1, float &t2) {

	// 2直線が平行？
	if (l1.v.isParallel(l2.v) == true) {

		// 点P11と直線L2の最短距離の問題に帰着
		float len = calcPointLineDist(l1.p, l2, p2, t2);
		p1 = l1.p;
		t1 = 0.0f;

		return len;
	}

	// 2直線はねじれ関係
	float DV1V2 = l1.v.dot(l2.v);
	float DV1V1 = l1.v.lengthSq();
	float DV2V2 = l2.v.lengthSq();
	Vec3 P21P11 = l1.p - l2.p;
	t1 = (DV1V2 * l2.v.dot(P21P11) - DV2V2 * l1.v.dot(P21P11)) / (DV1V1 * DV2V2 - DV1V2 * DV1V2);
	p1 = l1.getPoint(t1);
	t2 = l2.v.dot(p1 - l2.p) / DV2V2;
	p2 = l2.getPoint(t2);

	return (p2 - p1).length();
}

// 0〜1の間にクランプ
void clamp01(float &v) {
	if (v < 0.0f)
		v = 0.0f;
	else if (v > 1.0f)
		v = 1.0f;
}

// 2線分の最短距離
// s1 : S1(線分1)
// s2 : S2(線分2)
// p1 : S1側の垂線の足（戻り値）
// p2 : S2側の垂線の足（戻り値）
// t1 : S1側のベクトル係数（戻り値）
// t2 : S2側のベクトル係数（戻り値）
// 戻り値: 最短距離
float calcSegmentSegmentDist(const Segment &s1, const Segment &s2, Point &p1, Point &p2, float &t1, float &t2) 
{

	// S1が縮退している？
	if (s1.v.lengthSq() < _OX_EPSILON_) {
		// S2も縮退？
		if (s2.v.lengthSq() < _OX_EPSILON_) {
			// 点と点の距離の問題に帰着
			float len = (s2.p - s1.p).length();
			p1 = s1.p;
			p2 = s2.p;
			t1 = t2 = 0.0f;
			return len;
		}
		else {
			// S1の始点とS2の最短問題に帰着
			float len = calcPointSegmentDist(s1.p, s2, p2, t2);
			p1 = s1.p;
			t1 = 0.0f;
			clamp01(t2);
			return len;
		}
	}

	// S2が縮退している？
	else if (s2.v.lengthSq() < _OX_EPSILON_) {
		// S2の始点とS1の最短問題に帰着
		float len = calcPointSegmentDist(s2.p, s1, p1, t1);
		p2 = s2.p;
		clamp01(t1);
		t2 = 0.0f;
		return len;
	}

	/* 線分同士 */

	// 2線分が平行だったら垂線の端点の一つをP1に仮決定
	if (s1.v.isParallel(s2.v) == true) {
		t1 = 0.0f;
		p1 = s1.p;
		float len = calcPointSegmentDist(s1.p, s2, p2, t2);
		if (0.0f <= t2 && t2 <= 1.0f)
			return len;
	}
	else {
		// 線分はねじれの関係
		// 2直線間の最短距離を求めて仮のt1,t2を求める
		float len = calcLineLineDist(s1, s2, p1, p2, t1, t2);
		if (
			0.0f <= t1 && t1 <= 1.0f &&
			0.0f <= t2 && t2 <= 1.0f
			) {
			return len;
		}
	}

	// 垂線の足が外にある事が判明
	// S1側のt1を0〜1の間にクランプして垂線を降ろす
	clamp01(t1);
	p1 = s1.getPoint(t1);
	float len = calcPointSegmentDist(p1, s2, p2, t2);
	if (0.0f <= t2 && t2 <= 1.0f)
		return len;

	// S2側が外だったのでS2側をクランプ、S1に垂線を降ろす
	clamp01(t2);
	p2 = s2.getPoint(t2);
	len = calcPointSegmentDist(p2, s1, p1, t1);
	if (0.0f <= t1 && t1 <= 1.0f)
		return len;

	// 双方の端点が最短と判明
	clamp01(t1);
	p1 = s1.getPoint(t1);
	return (p2 - p1).length();
}

// カプセル同士の衝突判定
// c1 : S1(線分1)
// c2 : S2(線分2)
// 戻り値: 衝突していたらtrue
bool isCollisionCapsule(const Capsule &c1, const Capsule &c2) {
	Point p1, p2;
	float t1, t2;
	float d = calcSegmentSegmentDist(c1.s, c2.s, p1, p2, t1, t2);
	return (d <= c1.r + c2.r);
}
