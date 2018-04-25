//======================================================================
//	2D���f���̕`��
//
//======================================================================
#include "common.h"
#include "main.h"
#include "scene2D.h"

//======================================================================
//	�R���X�g���N�^
//======================================================================
CScene2D::CScene2D()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Texture = NULL;
}

//======================================================================
//	�f�X�g���N�^
//======================================================================
CScene2D::~CScene2D()
{
}

//======================================================================
//	���������֐�
//======================================================================
void CScene2D::Init(float texW, float texH)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

	HRESULT hr;

	hr = D3DXCreateTextureFromFile(pDevice, "data/textures/yajirusi.png", &m_Texture);

	if (FAILED(hr))
	{
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
		return;
	}

	m_texSize = D3DXVECTOR2(texW, texH);
}

//======================================================================
//	�I�������֐�
//======================================================================
void CScene2D::Uninit()
{
	// �e�N�X�`���̉��
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}

//======================================================================
//	�X�V�֐�
//======================================================================
void CScene2D::Update()
{
}

//======================================================================
//	�`��֐�
//======================================================================
void CScene2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

	VERTEX_2D vertex[4];
	vertex[0].pos = D3DXVECTOR4(m_Pos.x - m_texSize.x / 2 - 0.5f, m_Pos.y - m_texSize.y / 2, 0, 1);
	vertex[1].pos = D3DXVECTOR4(m_Pos.x + m_texSize.x / 2 - 0.5f, m_Pos.y - m_texSize.y / 2, 0, 1);
	vertex[2].pos = D3DXVECTOR4(m_Pos.x - m_texSize.x / 2 - 0.5f, m_Pos.y + m_texSize.y / 2, 0, 1);
	vertex[3].pos = D3DXVECTOR4(m_Pos.x + m_texSize.x / 2 - 0.5f, m_Pos.y + m_texSize.y / 2, 0, 1);

	vertex[0].texcoord = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].texcoord = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].texcoord = D3DXVECTOR2(0.0f, 1.0f);
	vertex[3].texcoord = D3DXVECTOR2(1.0f, 1.0f);

	vertex[0].color =
		vertex[1].color =
		vertex[2].color =
		vertex[3].color = 0xffffffff;

	pDevice->SetTexture(0, m_Texture);
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���e�X�g(3�Z�b�g)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// ���e�X�g��ON
	pDevice->SetRenderState(D3DRS_ALPHAREF, 128);					// ��2������0�`255�̍D���Ȓl
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// ��2�����͕s����(GREATER�͑�Ȃ�)�A��̒l���傫����΍��i

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vertex[0], sizeof(VERTEX_2D));

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// ���e�X�g��OFF
}
