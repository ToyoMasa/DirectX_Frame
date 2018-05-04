//======================================================================
//	�e�N�X�`���Ǘ�
//
//======================================================================
#include "common.h"
#include "main.h"
#include "texture.h"

//======================================================================
//	�ÓI�����o�ϐ��̏�����
//======================================================================
int CTexture::sm_NumTextures = 0;

CTexture::CTexture()
{
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
}

CTexture::~CTexture()
{
}

void CTexture::Init()
{
	for (int i = 0; i < TEX_ID_MAX; i++)
	{
		MAP_TEXTURES[i] = TEXTURE_SOURCE[i];
	}
}