//======================================================================
//	�r���{�[�h�����w�b�_[billboard.h]
//
//======================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include <string>

bool BillBoardInit(void);			// �r���{�[�h�̏�����
void BillBoardUninit(void);			// �r���{�[�h�̏I������
void BillBoardUpdate(void);			// �r���{�[�h�̍X�V

									//************************************************************************
									//	�r���{�[�h�`��i��ݒu���j
									//	�������@�g�p����e�N�X�`���ԍ�
									//	�������@�`�悷��ꏊ
									//	��O�����@�T�C�Y
									//************************************************************************
void BillBoardDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale);						// ����̃r���{�[�h�̕`��
void BillBoardDrawCircle(D3DXVECTOR3 vPos, float scale);						// ����̃r���{�[�h�̕`��
void BillBoardColorDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale, D3DCOLOR color);

void BillBoardAnimDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale, int tcx, int tcy, int tcw, int tch); // �A�j���[�V�����r���{�[�h�̕`��
void BillBoardAnimDrawCircle(int texNum, float width, float height, D3DXVECTOR3 vPos, float scale, int tcx, int tcy, int tcw, int tch); // �A�j���[�V�����r���{�[�h�̕`��

void BillBoardStaticDrawCircle(int texNum, D3DXVECTOR3 vPos, float scale);					// ��]���Ȃ��r���{�[�h�̕`��

																							//************************************************************************
																							//	�r���{�[�h�`��i�ݒu���j
																							//	�������@�g�p����e�N�X�`���ԍ�
																							//	�������@�`�悷��ꏊ
																							//	��O�����@�T�C�Y
																							//************************************************************************
void BillBoardDrawStand(int texNum, D3DXVECTOR3 vPos, float scale);
void BillBoardDrawStand(int texNum, float posX, float posY, float posZ, float scale);		// ��������I�u�W�F�N�g�r���{�[�h�̕`��


class CBillBoard
{
public:
	CBillBoard();
	~CBillBoard();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawStand();

private:
	LPDIRECT3DTEXTURE9		m_Texture;
	D3DMATERIAL9			m_Mat;					// ���f��1�����ɂ�1��
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;			//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9  m_IndexBuffer;			//�C���f�b�N�X�o�b�t�@
	D3DXMATRIX				m_World;				//���[���h�ϊ��s��
	D3DXMATRIX				m_Move;					//���W�ϊ��s��
	D3DXMATRIX				m_Scale;				//�g��k���s��
};


#endif // !_BILLBOARD_H_
