//======================================================================
//	�Q�[���Ǘ�
//
//======================================================================
#include "common.h"
#include "main.h"
#include "scene.h"
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
#include "enemy.h"
#include "input.h"
#include "skybox.h"

//======================================================================
//	�ÓI�����o�ϐ�
//======================================================================
CInputKeyboard *CManager::m_InputKeyboard = NULL;		// �L�[�{�[�h�ւ̃|�C���^
CInputMouse *CManager::m_InputMouse = NULL;			// �}�E�X�ւ̃|�C���^
CLight		*CManager::m_Light;

int tree1, tree2;
bool test = false;
CPlayer* player;
CEnemy* enemy;

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

	// �L�[�{�[�h����������
	m_InputKeyboard = new CInputKeyboard;
	m_InputKeyboard->Init(hInstance, hWnd);

	// �}�E�X����������
	m_InputMouse = new CInputMouse;
	m_InputMouse->Init(hInstance, hWnd);

	// �e�N�X�`���̏�����
	CTexture::Init();

	// �t�B�[���h
	CField* field = CField::Create(TEX_ID_FIELD001, 2.0f, 20, 20, true);

	// �v���C���[
	player = CPlayer::Create(MODEL_ID_XBOT, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	player->SetField(field);

	// �G
	enemy = CEnemy::Create(MODEL_ID_XBOT, D3DXVECTOR3(0.0f, 0.0f, 5.0f));
	enemy->SetField(field);

	// ��
	CSkyBox::Create(player);

	CScene2D* test = CScene2D::Create(TEX_ID_CURSOR, 128, 128);
	test->Set(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	m_Light = CLight::Create(0);

	CBillBoard::Init();

	tree1 = CBillBoard::Create(TEX_ID_TREE);
	tree2 = CBillBoard::Create(TEX_ID_TREE);

	CBillBoard::Set(tree1, TEX_ID_TREE, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 2.0f, 1);
	CBillBoard::Set(tree2, TEX_ID_TREE, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 2.0f, 1);

	return true;
}

void CManager::Uninit()
{
	CScene::ReleaseAll();

	m_Light->Release();

	CBillBoard::Uninit();

	// �S�Ẵe�N�X�`���̉��
	CTexture::ReleaseAll();

	// �L�[�{�[�h�̊J������
	if (m_InputKeyboard)
	{
		m_InputKeyboard->Uninit();
		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// �}�E�X�̊J������
	if (m_InputMouse)
	{
		m_InputMouse->Uninit();
		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	// imgui�̏I������
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Uninit();
#endif

	// �����_���[�N���X�̏I������
	CRenderer::Uninit();
}

void CManager::Update()
{
	// �L�[�{�[�h�X�V����
	if (m_InputKeyboard)
	{
		m_InputKeyboard->Update();
	}

	// �}�E�X�X�V����
	if (m_InputMouse)
	{
		m_InputMouse->Update();
	}

	CScene::UpdateAll();

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

		CBillBoard::DrawAll(player->GetCamera());

		// �f�o�b�O�pimgui�E�B���h�E�̕`��
#if defined(_DEBUG) || defined(DEBUG)
		CImGui::BeginDraw();

		D3DXVECTOR3 pos = player->GetPos();
		ImGui::Begin("Debug Window", 0);
		ImGui::Text("X = %.2f Y = %.2f Z = %.2f", pos.x, pos.y, pos.z);
		if (isCollisionCapsule(player->GetCapsule(), enemy->GetCapsule()))
		{
			ImGui::Text("Hit");
		}
		ImGui::End();

		CImGui::EndDraw();
#endif

		CRenderer::DrawEnd();
	}
}
