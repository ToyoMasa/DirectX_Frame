//======================================================================
//	�r���{�[�h�`��@�i2018/04/25�j
//	Author : �L�� ���r
//======================================================================
#include "common.h"
#include "main.h"
#include "billboard.h"
#include "camera.h"
#include "scene3D.h"

static const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL);

//======================================================================
//	�O���[�o���ϐ�
//======================================================================
CScene3D *billboard;

void CBillBoard::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

}
//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 NV; // �@��
//	D3DCOLOR color;
//	D3DXVECTOR2 texcoord;
//} VERTEX3D;
//
//static LPDIRECT3DTEXTURE9 g_pTextures[BB_TEXTURE_MAX];
//static D3DMATERIAL9 g_mat; // ���f��1�����ɂ�1��
//static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL; //���_�o�b�t�@
//static LPDIRECT3DINDEXBUFFER9  g_pIndexBuffer = NULL;  //�C���f�b�N�X�o�b�t�@
//static D3DXMATRIX g_mtxWorld;			//���[���h�ϊ��s��
//static D3DXMATRIX g_mtxMove;			//���W�ϊ��s��
//static D3DXMATRIX g_mtxScale;			//�g��k���s��
//
//bool BillBoardInit(void)			// �r���{�[�h�̏�����
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return false;
//	}
//	HRESULT hr;
//
//	for (int i = 0; i < BB_TEXTURE_MAX; i++)
//	{
//		hr = D3DXCreateTextureFromFile(pDevice, g_aBBTextureFileName[i].FileName, &g_pTextures[i]);
//
//		if (FAILED(hr))
//		{
//			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
//			return false;
//		}
//	}
//
//	// ���_�o�b�t�@							���傫�����ɂ͖��Ȃ�
//	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
//
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, "���_�o�b�t�@�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
//		return false;
//	}
//
//	// �C���f�b�N�X�o�b�t�@					���傫�����ɂ͖��Ȃ�					��size��DWORD�Ȃ�32
//	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
//
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
//		return false;
//	}
//
//	VERTEX3D* pV;
//
//	// ���_�o�b�t�@
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//
//	// �C���f�b�N�X�o�b�t�@
//	LPWORD pIndex;
//	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
//
//	pIndex[0] = 0;
//	pIndex[1] = 1;
//	pIndex[2] = 2;
//	pIndex[3] = 3;
//
//	g_pIndexBuffer->Unlock();
//
//	// ���[���h���W�s��̏�����
//	D3DXMatrixIdentity(&g_mtxWorld);
//	D3DXMatrixIdentity(&g_mtxMove);
//	return true;
//}
//
//void BillBoardUninit(void)			// �r���{�[�h�̏I������
//{
//	for (int i = 0; i < BB_TEXTURE_MAX; i++)
//	{
//		if (g_pTextures[i] != NULL)
//		{//�e�N�X�`���̊J��
//			g_pTextures[i]->Release();
//			g_pTextures[i] = NULL;
//		}
//	}
//
//	//���_�o�b�t�@�̉��
//	if (g_pVertexBuffer != NULL)
//	{
//		g_pVertexBuffer->Release();
//		g_pVertexBuffer = NULL;
//	}
//
//	//�C���f�b�N�X�o�b�t�@�̉��
//	if (g_pIndexBuffer != NULL)
//	{
//		g_pIndexBuffer->Release();
//		g_pIndexBuffer = NULL;
//	}
//}
//
//void BillBoardUpdate(void)			// �r���{�[�h�̍X�V
//{
//
//}
//
//void BillBoardDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale)			// �r���{�[�h�̕`��
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	// ���[���h���W�s����Z�b�g
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// �r���[�s��̋t�s����쐬
//	// ���s�ړ���Y���ȊO�̉�]�𖳌��ɂ���
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// �e�N�X�`���̃Z�b�g
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(������g�p���钸�_���)�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̐ݒ�
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//�e��s��̐ݒ�(�����̂�肽���Ƃ���ł��)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//}
//
//void BillBoardDrawCircle(D3DXVECTOR3 vPos, float scale)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	// ���[���h���W�s����Z�b�g
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// �r���[�s��̋t�s����쐬
//	// ���s�ړ���Y���ȊO�̉�]�𖳌��ɂ���
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// FVF(������g�p���钸�_���)�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̐ݒ�
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//�e��s��̐ݒ�(�����̂�肽���Ƃ���ł��)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//}
//
//void BillBoardDrawStand(int texNum, D3DXVECTOR3 vPos, float scale)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	// ���[���h���W�s����Z�b�g
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y + scale * 0.5f, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// �r���[�s��̋t�s����쐬
//	// ���s�ړ���Y���ȊO�̉�]�𖳌��ɂ���
//	mtxViewRotInv._21 = 0.0f;
//	mtxViewRotInv._32 = 0.0f;
//	mtxViewRotInv._12 = 0.0f;
//	mtxViewRotInv._23 = 0.0f;
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ���C�e�B���O�g���Ƃ��ɊO��
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// ���e�X�g(3�Z�b�g)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// ���e�X�g��ON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 128);					// ��2������0�`255�̍D���Ȓl
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// ��2�����͕s����(GREATER�͑�Ȃ�)�A��̒l���傫����΍��i
//
//																	// �e�N�X�`���̃Z�b�g
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(������g�p���钸�_���)�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̐ݒ�
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//�e��s��̐ݒ�(�����̂�肽���Ƃ���ł��)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�g��ON/OFF
//}
//
//void BillBoardDrawStand(int texNum, float posX, float posY, float posZ, float scale)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	// ���[���h���W�s����Z�b�g
//	D3DXMatrixTranslation(&g_mtxMove, posX, posY + scale * 0.5f, posZ);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// �r���[�s��̋t�s����쐬
//	// ���s�ړ���Y���ȊO�̉�]�𖳌��ɂ���
//	mtxViewRotInv._21 = 0.0f;
//	mtxViewRotInv._32 = 0.0f;
//	mtxViewRotInv._12 = 0.0f;
//	mtxViewRotInv._23 = 0.0f;
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ���C�e�B���O�g���Ƃ��ɊO��
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// ���e�X�g(3�Z�b�g)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// ���e�X�g��ON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 128);					// ��2������0�`255�̍D���Ȓl
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// ��2�����͕s����(GREATER�͑�Ȃ�)�A��̒l���傫����΍��i
//
//																	// �e�N�X�`���̃Z�b�g
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(������g�p���钸�_���)�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̐ݒ�
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//�e��s��̐ݒ�(�����̂�肽���Ƃ���ł��)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�g��ON/OFF
//}
//
//// �A�j���[�V�����r���{�[�h�̕`��
//void BillBoardAnimDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale, int tcx, int tcy, int tcw, int tch)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	int tw = g_aBBTextureFileName[texNum].width;
//	int th = g_aBBTextureFileName[texNum].height;
//	float u0 = (float)tcx / tw;					//�e�N�X�`���̐؂���
//	float v0 = (float)tcy / th;					//
//	float u1 = (float)(tcx + tcw) / tw;
//	float v1 = (float)(tcy + tch) / th;
//
//	VERTEX3D* pV;
//
//	// ���_�o�b�t�@
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) };
//
//	g_pVertexBuffer->Unlock();
//
//	// ���[���h���W�s����Z�b�g
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// �r���[�s��̋t�s����쐬
//	// ���s�ړ���Y���ȊO�̉�]�𖳌��ɂ���
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ���C�e�B���O�g���Ƃ��ɊO��
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// ���e�X�g(3�Z�b�g)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// ���e�X�g��ON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 16);					// ��2������0�`255�̍D���Ȓl
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// ��2�����͕s����(GREATER�͑�Ȃ�)�A��̒l���傫����΍��i
//
//																	// �e�N�X�`���̃Z�b�g
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(������g�p���钸�_���)�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̐ݒ�
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//�e��s��̐ݒ�(�����̂�肽���Ƃ���ł��)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�g��ON/OFF
//
//																// ���_�o�b�t�@
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//}
//
//// �F�ς��r���{�[�h�̕`��
//void BillBoardColorDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale, D3DCOLOR color)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	VERTEX3D* pV;
//
//	// ���_�o�b�t�@
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), color, D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), color, D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), color, D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), color, D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//
//	// ���[���h���W�s����Z�b�g
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// �r���[�s��̋t�s����쐬
//	// ���s�ړ���Y���ȊO�̉�]�𖳌��ɂ���
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ���C�e�B���O�g���Ƃ��ɊO��
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// ���e�X�g(3�Z�b�g)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// ���e�X�g��ON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						// ��2������0�`255�̍D���Ȓl
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// ��2�����͕s����(GREATER�͑�Ȃ�)�A��̒l���傫����΍��i
//
//																	// �e�N�X�`���̃Z�b�g
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(������g�p���钸�_���)�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̐ݒ�
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//�e��s��̐ݒ�(�����̂�肽���Ƃ���ł��)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�g��ON/OFF
//
//																// ���_�o�b�t�@
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//}
//
//// �A�j���[�V�����r���{�[�h�̕`��
//void BillBoardAnimDrawCircle(int texNum, float width, float height, D3DXVECTOR3 vPos, float scale, int tcx, int tcy, int tcw, int tch)
//{
//	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
//	if (pDevice == NULL)
//	{
//		return;
//	}
//
//	int tw = g_aBBTextureFileName[texNum].width;
//	int th = g_aBBTextureFileName[texNum].height;
//	float u0 = (float)tcx / tw;					//�e�N�X�`���̐؂���
//	float v0 = (float)tcy / th;					//
//	float u1 = (float)(tcx + tcw) / tw;
//	float v1 = (float)(tcy + tch) / th;
//
//	VERTEX3D* pV;
//
//	// ���_�o�b�t�@
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-width / 2,  height / 2, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) };
//	pV[1] = { D3DXVECTOR3(width / 2,  height / 2, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) };
//	pV[2] = { D3DXVECTOR3(-width / 2, -height / 2, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) };
//	pV[3] = { D3DXVECTOR3(width / 2, -height / 2, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) };
//
//	g_pVertexBuffer->Unlock();
//
//	// ���[���h���W�s����Z�b�g
//	D3DXMatrixTranslation(&g_mtxMove, vPos.x, vPos.y, vPos.z);
//	D3DXMatrixScaling(&g_mtxScale, scale, scale, scale);
//
//	g_mtxWorld = g_mtxScale * g_mtxMove;
//
//	D3DXMATRIX mtxViewRotInv = GetView();
//
//	// �r���[�s��̋t�s����쐬
//	// ���s�ړ���Y���ȊO�̉�]�𖳌��ɂ���
//	mtxViewRotInv._41 = 0.0f;
//	mtxViewRotInv._42 = 0.0f;
//	mtxViewRotInv._43 = 0.0f;
//
//	D3DXMatrixTranspose(&mtxViewRotInv, &mtxViewRotInv);
//
//	g_mtxWorld = mtxViewRotInv * g_mtxWorld;
//
//	// ���C�e�B���O�g���Ƃ��ɊO��
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// ���e�X�g(3�Z�b�g)
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// ���e�X�g��ON/OFF
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 16);					// ��2������0�`255�̍D���Ȓl
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	// ��2�����͕s����(GREATER�͑�Ȃ�)�A��̒l���傫����΍��i
//
//																	// �e�N�X�`���̃Z�b�g
//	pDevice->SetTexture(0, g_pTextures[texNum]);
//
//	// FVF(������g�p���钸�_���)�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̐ݒ�
//	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
//	pDevice->SetIndices(g_pIndexBuffer);
//
//	//�e��s��̐ݒ�(�����̂�肽���Ƃ���ł��)
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
//
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�g��ON/OFF
//
//																// ���_�o�b�t�@
//	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	pV[0] = { D3DXVECTOR3(-0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
//	pV[1] = { D3DXVECTOR3(0.5,  0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
//	pV[2] = { D3DXVECTOR3(-0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
//	pV[3] = { D3DXVECTOR3(0.5, -0.5, 0), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) };
//
//	g_pVertexBuffer->Unlock();
//}
//
//// ��]���Ȃ��r���{�[�h�̕`��
//void BillBoardStaticDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale)
//{
//}
//
//CBillBoard::CBillBoard()
//{
//	m_Texture = NULL;
//	m_VertexBuffer = NULL;
//	m_IndexBuffer = NULL;
//}
//
//CBillBoard::~CBillBoard()
//{
//}
//
//void CBillBoard::Init()
//{
//
//}
//
//void CBillBoard::Uninit()
//{
//	//���_�o�b�t�@�̉��
//	if (m_VertexBuffer != NULL)
//	{
//		m_VertexBuffer->Release();
//		m_VertexBuffer = NULL;
//	}
//
//	//�C���f�b�N�X�o�b�t�@�̉��
//	if (m_IndexBuffer != NULL)
//	{
//		m_IndexBuffer->Release();
//		m_IndexBuffer = NULL;
//	}
//}

void CBillBoard::Update()
{

}

void CBillBoard::Draw()
{

}

void CBillBoard::DrawStand()
{

}
