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

	// ボーンの行列領域を確保
	AllocateAllBoneMatrix(m_RootFrame);
	m_AnimController->SetTrackSpeed(0, 0.5f);

	// 追加
	//アニメーショントラックの取得
	for (int i = 0; i < m_AnimController->GetNumAnimationSets(); i++)
	{
		//アニメーション取得
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
	// ボーンのマトリクス分の領域を確保してデータを保存する
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

	// 子供があるかどうか
	if (frame->pFrameFirstChild != NULL)
	{
		if (FAILED(AllocateAllBoneMatrix(frame->pFrameFirstChild)))
		{
			return E_FAIL;
		}
	}

	// 兄弟があるかどうか
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
	// フレームの行列を更新
	UpdateFrame(m_RootFrame, matrix);
	// フレーム描画
	DrawFrame(m_RootFrame);
}

void SkinMeshFile::DrawFrame(LPD3DXFRAME frame)
{
	FrameData *frame_data = (FrameData*)frame;
	LPD3DXMESHCONTAINER container_data = frame_data->pMeshContainer;

	// コンテナの数だけ描画する
	while (container_data != NULL)
	{
		DrawMeshContainer(frame, container_data);

		container_data = container_data->pNextMeshContainer;
	}
	
	// 兄弟がいれば再帰で呼び出す
	if (frame_data->pFrameSibling != NULL)
	{
		DrawFrame(frame_data->pFrameSibling);
	}

	// 子がいれば再帰で呼び出す
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

		// ボーンの数まわす
		for(DWORD i = 0; i < original_container->m_BoneNum; i++)
		{
			// ブレンドするボーンの数
			DWORD bone_blend_num = 0;

			// ボーンIDからブレンドする個数を割り出す
			for (DWORD j = 0; j < original_container->m_BoneWeightNum; j++)
			{
				if (bone_buffer[i].BoneId[j] != UINT_MAX)
				{
					bone_blend_num++;
				}
			}
			
			// 頂点ブレンドの設定
			// 第二引数には_D3DVERTEXBLENDFLAGSが使われているので
			// 対象となっているボーンの数と差異に注意
			pDevice->SetRenderState(D3DRS_VERTEXBLEND, bone_blend_num - 1);

			for(DWORD j = 0; j < original_container->m_BoneWeightNum; j++) 
			{
				DWORD matrix_index = bone_buffer[i].BoneId[j];
				D3DXMATRIX matrix;

				if (matrix_index != UINT_MAX)
				{
					// オフセット行列(m_BoneOffsetMatrix) * ボーンの行列(m_BoneMatrix)で最新の位置を割り出す
					matrix = original_container->m_BoneOffsetMatrix[matrix_index] * (*original_container->m_BoneMatrix[matrix_index]);
					pDevice->SetTransform( D3DTS_WORLDMATRIX(j), &matrix );
				}
			}

			pDevice->SetMaterial( &original_container->pMaterials[bone_buffer[i].AttribId].MatD3D );
			pDevice->SetTexture( 0, original_container->m_TextureList[bone_buffer[i].AttribId] );
			original_container->MeshData.pMesh->DrawSubset(i);	
		}
	// 通常のXFile描画
	} else {
		// 描画位置行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &frame_data->m_CombinedTransformationMatrix);

		// メッシュの描画
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

	// 姿勢行列の更新
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

	// 兄弟があれば再帰で呼び出す
    if (frame->pFrameSibling != NULL)
    {
        UpdateFrame(frame->pFrameSibling, parent_matrix);
    }

	// 子供がいれば再帰で呼び出す
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
		// 0.016秒ずつアニメーションを進める
		m_AnimController->AdvanceTime(0.016f, NULL);
	}
}

// 追加
void SkinMeshFile::ChangeAnim(UINT newAnimID)
{
	// 存在するアニメーション番号か
	if (newAnimID < m_AnimController->GetNumAnimationSets())
	{
		// 今のアニメーションと違うか
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
