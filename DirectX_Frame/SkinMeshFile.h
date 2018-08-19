#ifndef SKINMESH_FILE_H_
#define SKINMESH_FILE_H_

#include <string>
#include <d3d9.h>
#include <d3dx9.h>

#include "SkinMeshData.h"

// �K�w�t��XFile
class SkinMeshFile
{
public:
	SkinMeshFile() :
		m_SkinMeshData(),
		m_RootFrame(NULL),
		m_AnimController(NULL)
	{}

	~SkinMeshFile();

	/*
		XFile�ǂݍ���
			�߂�l�F
				�ǂݍ��݌��ʁF
					�����F
						true
					���s�F
						false
			�����F
				std::string file_name�F
					�t�@�C����
			���e�F
				XFile�̓ǂݍ��݂��s��
	*/
	bool Load(std::string file_name);


	/*
		�{�[���s��̗̈�m��(�S�{�[��)
			�߂�l�F
				����
					�����FS_OK
					���s�FE_FAIL

			�����F					
				LPD3DXFRAME  
					�Ώۃt���[��

			���e�F
				�Ώۃt���[���̃{�[���s��̃������̈�̊m�ۊ֐������s����
				�q���A�Z��ɑ΂��Ă��̊֐����ċA�Ƃ��Ďg�p���A
				���[�܂Ŋm�ۂ��s���悤�ɂ���
	*/
	HRESULT AllocateAllBoneMatrix(LPD3DXFRAME  );	

	/*
		�{�[���s��̗̈�m��(�S�{�[��)
			�߂�l�F
				����
					�����FS_OK
					���s�FE_FAIL

			�����F					
				LPD3DXMESHCONTAINER  
					�m�ۑΏۂ̃��b�V���R���e�i

			���e�F
				�R���e�i�Ŏg�p���Ă���{�[���s�񕪂̃������̈���m�ۂ���
				
	*/
	HRESULT AllocateBoneMatrix(LPD3DXMESHCONTAINER  );

	/*
		�`��
			�߂�l�F
				�Ȃ�

			�����F
				LPD3DXMATRIX matrix
					�`��Ŏg�p���郏�[���h���W�s��

			���e�F
				XFile��`�悷��
				���̊֐����Ń��[�g�t���[���������Ƃ���
				DrawFrame���g�p����
				���̍ۂɂ���XFile��`�悷��I�u�W�F�N�g��
				���[���h���W�s��������œn��
	*/
	void Draw(LPD3DXMATRIX matrix);

	/*
		�t���[���̕`��
			�߂�l�F
				�Ȃ�

			�����F
				LPD3DXFRAME frame�F
					�t���[���f�[�^

			���e�F
				�����Ŏw�肳�ꂽ�t���[����`�悷��
				���̊֐����Ńt���[�����ێ����Ă���
				�S�Ẵ��b�V���R���e�i��`��(DrawMeshContainer)����
	*/
	void DrawFrame(LPD3DXFRAME frame);

	/*
		���b�V���R���e�i�̕`��
			�߂�l�F
				�Ȃ�

			�����F
				LPD3DXFRAME frame�F
					�t���[���f�[�^

				LPD3DXMESHCONTAINER container�F
					���b�V���R���e�i
			���e�F
				�w�肳�ꂽ���b�V���R���e�i��`�悷��
				�`��̓��e�͒ʏ��XFile�̕`����@�Ɠ������@��
				�`��ł���
	*/
	void DrawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER container);

	/*
		�t���[���̍X�V
			�߂�l�F
				�Ȃ�

			�����F
				LPD3DXFRAME base�F
					�X�V�t���[��

				LPD3DXMATRIX parent_matrix�F
					�e�̎p���s��

			���e�F
				�e�̎p���s������ɂ��Ď����̎p���s����X�V����
				�q�A�Z�킪����ꍇ�͂�����ċA�ŌĂяo��
	*/
	void UpdateFrame(LPD3DXFRAME base, LPD3DXMATRIX parent_matrix);

	/*
		�A�j���[�V�����̍X�V
			�߂�l�F
				�Ȃ�
			�����F
				�Ȃ�
			���e�F
				�A�j���[�V�������X�V������
	*/
	void UpdateAnim(void);

	// �ǉ�
	// �A�j���[�V�����ؑ�
	void ChangeAnim(UINT newAnimID);
private:
	// �K�w�f�[�^
	SkinMeshData *m_SkinMeshData;

	// ���[�g�t���[��
	LPD3DXFRAME m_RootFrame;

	// �A�j���[�V�����Ǘ�
    LPD3DXANIMATIONCONTROLLER m_AnimController;

	// �ǉ�
	// ���݂̃g���b�N

	// �A�j���[�V����
	LPD3DXANIMATIONSET m_AnimSet[20];
	//���݂̃A�j���[�V����
	DWORD m_CurrentAnim;
	//���݂̃A�j���[�V�����f�[�^�g���b�N
	D3DXTRACK_DESC m_CurrentTrackDesc;
};

#endif