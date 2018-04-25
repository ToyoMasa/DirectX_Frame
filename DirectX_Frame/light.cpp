//======================================================================
//	���C�e�B���O���� [Light.cpp]�@�i2017/11/13�j
//	Author : �L�� ���r
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
//								������
//		���[���h���W�Ŋg��k��������Ɩ@���x�N�g���������̂Œ���
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
	light.Type = D3DLIGHT_DIRECTIONAL;	// �f�B���N�V���i�����C�g

										// ���C�g�̃x�N�g��
	D3DXVECTOR3 vecDir(LIGHT_NMR_X, LIGHT_NMR_Y, LIGHT_NMR_Z);

	// vecDir�𐳋K������light�ɑ������
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	// �f�B�t���[�Y�J���[���Z�b�g�i���j�@�f�B���N�V���i���{�A���r�G���g�ɂȂ�
	light.Diffuse.r = DEFAULT_DEFUSE_COLOR;
	light.Diffuse.g = 0.7f;
	light.Diffuse.b = 0.7f;
	light.Diffuse.a = 0.7f;
	light.Ambient.r = 0.2f;
	light.Ambient.g = 0.2f;
	light.Ambient.b = 0.2f;
	light.Ambient.a = 0.2f;

	// ���C�g�ԍ��̃Z�b�g(0�`3)�܂Ŏg����
	pDevice->SetLight(0, &light);
	// 0�Ԃ̃��C�g��ON
	pDevice->LightEnable(0, TRUE);
	// �O���[�o���J���[�̐ݒ�
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

	m_Light.Type = D3DLIGHT_DIRECTIONAL;	// �f�B���N�V���i�����C�g
			
	// ���C�g�̃x�N�g��
	D3DXVECTOR3 vecDir(LIGHT_NMR_X, LIGHT_NMR_Y, LIGHT_NMR_Z);

	// vecDir�𐳋K������light�ɑ������
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);

	// �f�B�t���[�Y�J���[���Z�b�g�i���j�@�f�B���N�V���i���{�A���r�G���g�ɂȂ�
	m_Light.Diffuse.r = DEFAULT_DEFUSE_COLOR;
	m_Light.Diffuse.g = DEFAULT_DEFUSE_COLOR;
	m_Light.Diffuse.b = DEFAULT_DEFUSE_COLOR;
	m_Light.Diffuse.a = DEFAULT_DEFUSE_COLOR;
	m_Light.Ambient.r = DEFAULT_AMBIENT_COLOR;
	m_Light.Ambient.g = DEFAULT_AMBIENT_COLOR;
	m_Light.Ambient.b = DEFAULT_AMBIENT_COLOR;
	m_Light.Ambient.a = DEFAULT_AMBIENT_COLOR;

	// ���C�g�ԍ��̃Z�b�g(0�`3)�܂Ŏg����
	pDevice->SetLight(m_LightID, &m_Light);
	// 0�Ԃ̃��C�g��ON
	pDevice->LightEnable(m_LightID, TRUE);
	// �O���[�o���J���[�̐ݒ�
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(GLOBAL_AMBIENT, GLOBAL_AMBIENT, GLOBAL_AMBIENT, 1.0f));
}

void CLight::Uninit()
{

}

void CLight::SetLight()
{

}
