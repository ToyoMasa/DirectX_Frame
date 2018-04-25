//======================================================================
//	ライティング処理 [Light.cpp]　（2017/11/13）
//	Author : 豊村 昌俊
//======================================================================
#include "common.h"
#include "main.h"
#include "camera.h"
#include "light.h"

static const float LIGHT_NMR_X = -1.0f;
static const float LIGHT_NMR_Y = -1.0f;
static const float LIGHT_NMR_Z = 1.0f;
static const float GLOBAL_AMBIENT = 0.35f;
static const float DEFAULT_DEFUSE_COLOR = 0.7f;
static const float DEFAULT_AMBIENT_COLOR = 0.2f;

//======================================================================
//								※注意
//		ワールド座標で拡大縮小をすると法線ベクトルもずれるので注意
//======================================================================

void LightInit(void)
{

}

void LightUninit(void)
{

}

void LightUpdate(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;	// ディレクショナルライト

										// ライトのベクトル
	D3DXVECTOR3 vecDir(LIGHT_NMR_X, LIGHT_NMR_Y, LIGHT_NMR_Z);

	// vecDirを正規化してlightに代入する
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	// ディフューズカラーをセット（白）　ディレクショナル＋アンビエントになる
	light.Diffuse.r = DEFAULT_DEFUSE_COLOR;
	light.Diffuse.g = 0.7f;
	light.Diffuse.b = 0.7f;
	light.Diffuse.a = 0.7f;
	light.Ambient.r = 0.2f;
	light.Ambient.g = 0.2f;
	light.Ambient.b = 0.2f;
	light.Ambient.a = 0.2f;

	// ライト番号のセット(0～3)まで使える
	pDevice->SetLight(0, &light);
	// 0番のライトをON
	pDevice->LightEnable(0, TRUE);
	// グローバルカラーの設定
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(GLOBAL_AMBIENT, GLOBAL_AMBIENT, GLOBAL_AMBIENT, 1.0f));
}

void LightSet(void)
{

}

CLight::CLight()
{
}

CLight::~CLight()
{
}

void CLight::Init(int id)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	m_LightID = id;

	m_Light.Type = D3DLIGHT_DIRECTIONAL;	// ディレクショナルライト
			
	// ライトのベクトル
	D3DXVECTOR3 vecDir(LIGHT_NMR_X, LIGHT_NMR_Y, LIGHT_NMR_Z);

	// vecDirを正規化してlightに代入する
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);

	// ディフューズカラーをセット（白）　ディレクショナル＋アンビエントになる
	m_Light.Diffuse.r = DEFAULT_DEFUSE_COLOR;
	m_Light.Diffuse.g = DEFAULT_DEFUSE_COLOR;
	m_Light.Diffuse.b = DEFAULT_DEFUSE_COLOR;
	m_Light.Diffuse.a = DEFAULT_DEFUSE_COLOR;
	m_Light.Ambient.r = DEFAULT_AMBIENT_COLOR;
	m_Light.Ambient.g = DEFAULT_AMBIENT_COLOR;
	m_Light.Ambient.b = DEFAULT_AMBIENT_COLOR;
	m_Light.Ambient.a = DEFAULT_AMBIENT_COLOR;

	// ライト番号のセット(0～3)まで使える
	pDevice->SetLight(m_LightID, &m_Light);
	// 0番のライトをON
	pDevice->LightEnable(m_LightID, TRUE);
	// グローバルカラーの設定
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(GLOBAL_AMBIENT, GLOBAL_AMBIENT, GLOBAL_AMBIENT, 1.0f));
}

void CLight::Uninit()
{

}

void CLight::SetLight()
{

}
