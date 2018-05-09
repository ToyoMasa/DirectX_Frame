//======================================================================
//	3D���f���̕`��
//
//======================================================================
#include "common.h"
#include "main.h"
#include "scene3D.h"
#include "texture.h"

static const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL);

VERTEX_3D v[] = {
	//		�ʒu���W							�@���x�N�g��						�F							UV���W
	//��̖�														    
	{ D3DXVECTOR3(-2.0f,  0.0f,  2.0f), D3DXVECTOR3(0.0f,  1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	{ D3DXVECTOR3( 2.0f,  0.0f,  2.0f), D3DXVECTOR3(0.0f,  1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },
	{ D3DXVECTOR3(-2.0f,  0.0f, -2.0f), D3DXVECTOR3(0.0f,  1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) },
	{ D3DXVECTOR3( 2.0f,  0.0f, -2.0f), D3DXVECTOR3(0.0f,  1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) },
};

WORD index[] =
{
	//�O�̖�
	0, 1, 2,
	1, 3, 2,
};

//======================================================================
//	�R���X�g���N�^
//======================================================================
CScene3D::CScene3D()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;
}

//======================================================================
//	�f�X�g���N�^
//======================================================================
CScene3D::~CScene3D()
{
}

//======================================================================
//	���������֐�
//======================================================================
void CScene3D::Init(int texId)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

	m_TexId = texId;
	CTexture::Load(m_TexId);

	HRESULT hr;

	// ���_�o�b�t�@							���傫�����ɂ͖��Ȃ�
	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "���_�o�b�t�@�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
		return;
	}

	// �C���f�b�N�X�o�b�t�@					���傫�����ɂ͖��Ȃ�			��size��DWORD�Ȃ�32
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
		return;
	}

	VERTEX_3D* pV;

	// ���_�o�b�t�@
	m_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	memcpy(pV, &v[0], sizeof(v));

	m_VertexBuffer->Unlock();

	LPWORD pIndex;
	m_IndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

	memcpy(pIndex, &index[0], sizeof(index));

	m_IndexBuffer->Unlock();

	// �}�e���A���̐ݒ�
	m_Mat.Diffuse.r = 1.0f;
	m_Mat.Diffuse.g = 1.0f;
	m_Mat.Diffuse.b = 1.0f;
	m_Mat.Diffuse.a = 1.0f;
	// �A���r�G���g�J���[�i���j
	m_Mat.Ambient.r = 0.8f;
	m_Mat.Ambient.g = 0.7f;
	m_Mat.Ambient.b = 0.9f;
	m_Mat.Ambient.a = 1.0f;

	D3DXMatrixIdentity(&m_World);
}

//======================================================================
//	�I�������֐�
//======================================================================
void CScene3D::Uninit()
{
	// �e�N�X�`���̉��
	CTexture::Release(m_TexId);

	//���_�o�b�t�@�̉��
	if (m_VertexBuffer != NULL)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (m_IndexBuffer != NULL)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = NULL;
	}
}

//======================================================================
//	�X�V�֐�
//======================================================================
void CScene3D::Update()
{
}

//======================================================================
//	�`��֐�
//======================================================================
void CScene3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

	// FVF(������g�p���钸�_���)�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̐ݒ�
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_IndexBuffer);

	//�e��s��̐ݒ�(�����̂�肽���Ƃ�);
	pDevice->SetMaterial(&m_Mat);

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTransform(D3DTS_WORLD, &m_World);

	pDevice->SetTexture(0, CTexture::GetTexture(m_TexId));

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}

CScene3D* CScene3D::Create(int texId)
{
	CScene3D* scene3D = new CScene3D();
	scene3D->Init(texId);

	return scene3D;
}
