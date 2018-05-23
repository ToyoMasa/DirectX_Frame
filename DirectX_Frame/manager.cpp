//======================================================================
//	�Q�[���Ǘ�
//
//======================================================================
#include "common.h"
#include "main.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneModel.h"
#include "camera.h"
#include "light.h"
#include "manager.h"
#include "texture.h"
#include "billboard.h"
#include "field.h"
#include "player.h"

//======================================================================
//	�ÓI�����o�ϐ��̏�����
//======================================================================
CCamera		*CManager::m_Camera;
CLight		*CManager::m_Light;

int tree1, tree2;

bool CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (!CRenderer::Init(hWnd, bWindow))
	{
		return false;
	}

	// imgui�̏������Ɛݒ�
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Init(hWnd, CRenderer::GetDevice());
	ImGui::StyleColorsClassic();
#endif

	// �e�N�X�`���̏�����
	CTexture::Init();

	// �t�B�[���h
	CField::Create(TEX_ID_FIELD001, 1.0f, 4, 4);

	CScene2D* test = CScene2D::Create(TEX_ID_CURSOR, 128, 128);
	test->Set(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	CPlayer::Create(MODEL_ID_UFO, D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	m_Camera = CCamera::Create();

	m_Light = CLight::Create(0);

	CBillBoard::Init();
	tree1 = CBillBoard::Create(TEX_ID_TREE);
	tree2 = CBillBoard::Create(TEX_ID_TREE);

	CBillBoard::Set(tree1, TEX_ID_TREE, D3DXVECTOR3(1.0f, 1.0f, 0.0f), 1.0f);
	CBillBoard::Set(tree2, TEX_ID_TREE, D3DXVECTOR3(-1.0f, 1.0f, 0.0f), 1.0f);

	return true;
}

void CManager::Uninit()
{
	CScene::ReleaseAll();

	m_Camera->Release();

	m_Light->Release();

	CBillBoard::Uninit();

	// �S�Ẵe�N�X�`���̉��
	CTexture::ReleaseAll();

	// imgui�̏I������
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Uninit();
#endif

	// �����_���[�N���X�̏I������
	CRenderer::Uninit();
}

void CManager::Update()
{
	CScene::UpdateAll();

	m_Camera->Update();

	CBillBoard::Update();
}

void CManager::Draw()
{
	HRESULT hr;

	hr = CRenderer::DrawBegin();

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(hr))
	{
		//�`��
		CScene::DrawAll();

		CBillBoard::DrawAll(m_Camera);

		// �f�o�b�O�pimgui�E�B���h�E�̕`��
#if defined(_DEBUG) || defined(DEBUG)
		CImGui::BeginDraw();
		CImGui::EndDraw();
#endif

		CRenderer::DrawEnd();
	}
}
