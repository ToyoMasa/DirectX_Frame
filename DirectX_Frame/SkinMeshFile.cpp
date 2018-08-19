#include <map>
#include "common.h"
#include "main.h"
#include "SkinMeshFile.h"

extern std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;

SkinMeshFile::~SkinMeshFile()
{
	if (m_SkinMeshData != NULL)
	{
		m_SkinMeshData->DestroyFrame(m_RootFrame);
		delete (m_SkinMeshData);
	}
	if (m_AnimController != NULL)
	{
		m_AnimController->Release();
	}
	for (int i = 0; i < 20; i++)
	{
		if (m_AnimSet[i] != NULL)
		{
			m_AnimSet[i]->Release();
		}
	}
}

bool SkinMeshFile::Load(std::string file_name)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return false;
	}

	m_SkinMeshData = new SkinMeshData();

	if (FAILED(D3DXLoadMeshHierarchyFromXA(
		file_name.c_str(),
		D3DXMESH_MANAGED,
		pDevice,
		m_SkinMeshData,
		NULL,
		&m_RootFrame,
		&m_AnimController) ) )
	{
		return false;
	}

	// �{�[���̍s��̈���m��
	AllocateAllBoneMatrix(m_RootFrame);
	m_AnimController->SetTrackSpeed(0, 0.5f);

	// �ǉ�
	//�A�j���[�V�����g���b�N�̎擾
	for (int i = 0; i < m_AnimController->GetNumAnimationSets(); i++)
	{
		//�A�j���[�V�����擾
		m_AnimController->GetAnimationSet(i, &(m_AnimSet[i]));
	}
	m_CurrentAnim = 0;
	m_AnimController->GetTrackDesc(0, &m_CurrentTrackDesc);

	return true;
}

HRESULT SkinMeshFile::AllocateBoneMatrix(LPD3DXMESHCONTAINER container)
{
    FrameData *pFrame=NULL;
	DWORD bone_num = 0;

    MeshContainer *original_container = (MeshContainer*)container;
    if (original_container->pSkinInfo == NULL)
	{
		return S_OK;
	}

	bone_num = original_container->pSkinInfo->GetNumBones();
	// �{�[���̃}�g���N�X���̗̈���m�ۂ��ăf�[�^��ۑ�����
    original_container->m_BoneMatrix = new D3DXMATRIX*[bone_num];
    for (DWORD i = 0; i < bone_num; i++)
    {
		pFrame = (FrameData*)D3DXFrameFind( m_RootFrame, container->pSkinInfo->GetBoneName(i) );
        if (pFrame == NULL)
		{
			return E_FAIL;
		}
		original_container->m_BoneMatrix[i] = &pFrame->m_CombinedTransformationMatrix;
	}   

	return S_OK;
}

HRESULT SkinMeshFile::AllocateAllBoneMatrix(LPD3DXFRAME frame)
{
	if (frame->pMeshContainer != NULL)
	{
		if (FAILED(AllocateBoneMatrix(frame->pMeshContainer)))
		{
			return E_FAIL;
		}
	}

	// �q�������邩�ǂ���
	if (frame->pFrameFirstChild != NULL)
	{
		if (FAILED(AllocateAllBoneMatrix(frame->pFrameFirstChild)))
		{
			return E_FAIL;
		}
	}

	// �Z�킪���邩�ǂ���
	if (frame->pFrameSibling != NULL)
	{
		if (FAILED(AllocateAllBoneMatrix(frame->pFrameSibling)))
		{
			return E_FAIL;
		}		
	}

	return S_OK;
}


void SkinMeshFile::Draw(LPD3DXMATRIX matrix)
{
	// �t���[���̍s����X�V
	UpdateFrame(m_RootFrame, matrix);
	// �t���[���`��
	DrawFrame(m_RootFrame);
}

void SkinMeshFile::DrawFrame(LPD3DXFRAME frame)
{
	FrameData *frame_data = (FrameData*)frame;
	LPD3DXMESHCONTAINER container_data = frame_data->pMeshContainer;

	// �R���e�i�̐������`�悷��
	while (container_data != NULL)
	{
		DrawMeshContainer(frame, container_data);

		container_data = container_data->pNextMeshContainer;
	}
	
	// �Z�킪����΍ċA�ŌĂяo��
	if (frame_data->pFrameSibling != NULL)
	{
		DrawFrame(frame_data->pFrameSibling);
	}

	// �q������΍ċA�ŌĂяo��
	if (frame_data->pFrameFirstChild != NULL)
	{
		DrawFrame(frame_data->pFrameFirstChild);
	}
}
	
void SkinMeshFile::DrawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER container)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

    FrameData *frame_data = (FrameData*)frame;
    MeshContainer *original_container = (MeshContainer*)container;

	if (original_container->pSkinInfo != NULL)
	{
		LPD3DXBONECOMBINATION bone_buffer = (LPD3DXBONECOMBINATION)original_container->m_BoneBuffer->GetBufferPointer();	

		// �{�[���̐��܂킷
		for(DWORD i = 0; i < original_container->m_BoneNum; i++)
		{
			// �u�����h����{�[���̐�
			DWORD bone_blend_num = 0;

			// �{�[��ID����u�����h�����������o��
			for (DWORD j = 0; j < original_container->m_BoneWeightNum; j++)
			{
				if (bone_buffer[i].BoneId[j] != UINT_MAX)
				{
					bone_blend_num++;
				}
			}
			
			// ���_�u�����h�̐ݒ�
			// �������ɂ�_D3DVERTEXBLENDFLAGS���g���Ă���̂�
			// �ΏۂƂȂ��Ă���{�[���̐��ƍ��قɒ���
			pDevice->SetRenderState(D3DRS_VERTEXBLEND, bone_blend_num - 1);

			for(DWORD j = 0; j < original_container->m_BoneWeightNum; j++) 
			{
				DWORD matrix_index = bone_buffer[i].BoneId[j];
				D3DXMATRIX matrix;

				if (matrix_index != UINT_MAX)
				{
					// �I�t�Z�b�g�s��(m_BoneOffsetMatrix) * �{�[���̍s��(m_BoneMatrix)�ōŐV�̈ʒu������o��
					matrix = original_container->m_BoneOffsetMatrix[matrix_index] * (*original_container->m_BoneMatrix[matrix_index]);
					pDevice->SetTransform( D3DTS_WORLDMATRIX(j), &matrix );
				}
			}

			pDevice->SetMaterial( &original_container->pMaterials[bone_buffer[i].AttribId].MatD3D );
			pDevice->SetTexture( 0, original_container->m_TextureList[bone_buffer[i].AttribId] );
			original_container->MeshData.pMesh->DrawSubset(i);	
		}
	// �ʏ��XFile�`��
	} else {
		// �`��ʒu�s��̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &frame_data->m_CombinedTransformationMatrix);

		// ���b�V���̕`��
		for (int i = 0; i < original_container->NumMaterials; i++)
		{
			pDevice->SetMaterial( &original_container->pMaterials[i].MatD3D );
			pDevice->SetTexture( 0, original_container->m_TextureList[i] );
			original_container->MeshData.pMesh->DrawSubset(i);
		}
	}

}

void SkinMeshFile::UpdateFrame(LPD3DXFRAME base, LPD3DXMATRIX parent_matrix)
{
	FrameData *frame = (FrameData*)base;

	// �p���s��̍X�V
    if (parent_matrix != NULL)
	{
        D3DXMatrixMultiply(&frame->m_CombinedTransformationMatrix, 
						&frame->TransformationMatrix,
						parent_matrix);
	}
    else
	{
        frame->m_CombinedTransformationMatrix = frame->TransformationMatrix;
	}

	// �Z�킪����΍ċA�ŌĂяo��
    if (frame->pFrameSibling != NULL)
    {
        UpdateFrame(frame->pFrameSibling, parent_matrix);
    }

	// �q��������΍ċA�ŌĂяo��
    if (frame->pFrameFirstChild != NULL)
    {
        UpdateFrame(frame->pFrameFirstChild,
							&frame->m_CombinedTransformationMatrix);
    }
}

void SkinMeshFile::UpdateAnim()
{
	if (m_AnimController != NULL)
	{
		// 0.016�b���A�j���[�V������i�߂�
		m_AnimController->AdvanceTime(0.016f, NULL);
	}
}

// �ǉ�
void SkinMeshFile::ChangeAnim(UINT newAnimID)
{
	// ���݂���A�j���[�V�����ԍ���
	if (newAnimID < m_AnimController->GetNumAnimationSets())
	{
		// ���̃A�j���[�V�����ƈႤ��
		if (newAnimID != m_CurrentAnim)
		{
			m_CurrentAnim = newAnimID;
			m_AnimController->SetTrackAnimationSet(0, m_AnimSet[m_CurrentAnim]);

			D3DXTRACK_DESC CurrentTrackDesc;
			m_AnimController->GetTrackDesc(0, &CurrentTrackDesc);
			CurrentTrackDesc.Position = 0;
			m_AnimController->SetTrackDesc(0, &CurrentTrackDesc);
		}
	}

}
