#include "common.h"
#include "main.h"
#include "mode.h"
#include "scene.h"
#include "scene2D.h"
#include "fade.h"
#include "texture.h"

D3DXVECTOR2 CFade::m_TexSize;
int CFade::m_Alpha;
int CFade::m_TexId;
bool CFade::m_FadeIn = false;
bool CFade::m_FadeOut = false;

void CFade::Init()
{
	m_TexId = TEX_ID_BLACK;
	CTexture::Load(m_TexId);

	m_TexSize = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

	m_Alpha = 255;
}

void CFade::Uninit()
{
	// �e�N�X�`���̉��
	CTexture::Release(m_TexId);
}

void CFade::Update()
{
	if (m_FadeIn)
	{
		if (m_Alpha > 0)
		{
			m_Alpha -= 255 / 120;
		}
		else
		{
			m_FadeIn = false;
		}
	}

	if (m_FadeOut)
	{
		if (m_Alpha < 255)
		{
			m_Alpha += 255 / 120;
		}
		else
		{
			m_FadeOut = false;
		}
	}

}

void CFade::Draw()
{
	if (m_FadeIn || m_FadeOut)
	{
		LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
		if (pDevice == NULL)
		{
			return;
		}

		VERTEX_2D vertex[4];
		vertex[0].pos = D3DXVECTOR4(0 - 0.5f, 0, 0, 1);
		vertex[1].pos = D3DXVECTOR4(SCREEN_WIDTH - 0.5f, 0, 0, 1);
		vertex[2].pos = D3DXVECTOR4(0 - 0.5f, SCREEN_HEIGHT, 0, 1);
		vertex[3].pos = D3DXVECTOR4(SCREEN_WIDTH - 0.5f, SCREEN_HEIGHT, 0, 1);

		vertex[0].texcoord = D3DXVECTOR2(0, 0);
		vertex[1].texcoord = D3DXVECTOR2(1, 0);
		vertex[2].texcoord = D3DXVECTOR2(0, 1);
		vertex[3].texcoord = D3DXVECTOR2(1, 1);

		vertex[0].color =
			vertex[1].color =
			vertex[2].color =
			vertex[3].color = D3DCOLOR_RGBA(255, 255, 255, m_Alpha);

		pDevice->SetTexture(0, CTexture::GetTexture(m_TexId));
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ���e�X�g(3�Z�b�g)
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// ���e�X�g��ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 128);					// ��2������0�`255�̍D���Ȓl
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// ��2�����͕s����(GREATER�͑�Ȃ�)�A��̒l���傫����΍��i

		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vertex[0], sizeof(VERTEX_2D));

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// ���e�X�g��OFF
	}
}

void CFade::FadeIn()
{
	m_FadeIn = true;
	m_FadeOut = false;

	m_Alpha = 255;
}

void CFade::FadeOut()
{
	m_FadeOut = true;
	m_FadeIn = false;

	m_Alpha = 0;
}
