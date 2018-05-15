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

//======================================================================
//	�ÓI�����o�ϐ��̏�����
//======================================================================
CSceneModel *CManager::m_Model;
CCamera		*CManager::m_Camera;
CLight		*CManager::m_Light;
CScene		*CManager::m_Scene[2] = { NULL };

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

	m_Scene[0] = CScene2D::Create(TEX_ID_CURSOR, 128, 128);
	m_Scene[0]->Set(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	m_Scene[1] = CScene3D::Create(TEX_ID_FIELD001);

	m_Model = CSceneModel::Create(MODEL_SOURCE[MODEL_ID_UFO]);

	m_Model->Move(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	m_Camera = CCamera::Create();

	m_Light = CLight::Create(0);

	CBillBoard::Init();

	return true;
}

void CManager::Uninit()
{
	for (int i = 0; i < 2; i++)
	{
		m_Scene[i]->Release();
	}

	m_Model->Release();

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
	for (int i = 0; i < 2; i++)
	{
		m_Scene[i]->Update();
	}

	m_Model->Update();

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
		for (int i = 0; i < 2; i++)
		{
			m_Scene[i]->Draw();
		}

		CBillBoard::DrawBegin();
		CBillBoard::DrawFixedY(TEX_ID_TREE, D3DXVECTOR3(1.0f, 1.0f, 0.0f), 1.0f, m_Camera);
		CBillBoard::Draw(TEX_ID_TREE, D3DXVECTOR3(-1.0f, 1.0f, 0.0f), 1.0f, m_Camera);
		CBillBoard::DrawEnd();

		m_Model->Draw();

		// �f�o�b�O�pimgui�E�B���h�E�̕`��
#if defined(_DEBUG) || defined(DEBUG)
		CImGui::BeginDraw();
		CImGui::EndDraw();
#endif

		CRenderer::DrawEnd();
	}
}
