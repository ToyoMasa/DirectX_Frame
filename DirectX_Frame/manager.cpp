//======================================================================
//	�Q�[���Ǘ�
//
//======================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "texture.h"

//======================================================================
//	�ÓI�����o�ϐ��̏�����
//======================================================================
CScene2D	*CManager::m_Scene2D;
CScene3D	*CManager::m_Scene3D;
CSceneModel *CManager::m_Model;
CCamera		*CManager::m_Camera;
CLight		*CManager::m_Light;

bool CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (!CRenderer::Init(hWnd, bWindow))
	{
		return false;
	}

	// imgui�̏������Ɛݒ�
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Init(hWnd, CRenderer::GetDevice());
#endif

	// �e�N�X�`���̏�����
	CTexture::Init();

	ImGui::StyleColorsClassic();

	m_Scene2D = new CScene2D();
	m_Scene2D->Init(TEX_ID_CURSOR, 128, 128);

	m_Scene3D = new CScene3D();
	m_Scene3D->Init("data/textures/field001.jpg");

	m_Model = new CSceneModel();
	m_Model->Init("data/models/player_ufo.x");

	m_Model->Move(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	m_Camera = new CCamera();
	m_Camera->Init(D3DXVECTOR3(0.0f, 3.0f, -3.0f), D3DXVECTOR3(0, 0, 0));

	m_Light = new CLight();
	m_Light->Init(0);

	return true;
}

void CManager::Uninit()
{
	m_Scene2D->Uninit();
	delete m_Scene2D;

	m_Scene3D->Uninit();
	delete m_Scene3D;

	m_Model->Uninit();
	delete m_Model;

	m_Camera->Uninit();
	delete m_Camera;

	m_Light->Uninit();
	delete m_Light;

	// �S�Ẵe�N�X�`���̉��
	CTexture::ReleaseAll();

	// imgui�̏I������
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Uninit();
#endif
}

void CManager::Update()
{
	m_Scene2D->Set(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	m_Scene3D->Update();

	m_Model->Update();

	m_Camera->Update();
}

void CManager::Draw()
{
	HRESULT hr;

	hr = CRenderer::DrawBegin();

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(hr))
	{
		//�`��
		m_Scene2D->Draw();

		m_Scene3D->Draw();

		m_Model->Draw();

		// �f�o�b�O�pimgui�E�B���h�E�̕`��
#if defined(_DEBUG) || defined(DEBUG)
		CImGui::BeginDraw();
		CImGui::EndDraw();
#endif

		CRenderer::DrawEnd();
	}
}
