//======================================================================
//	ゲーム管理
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
//	静的メンバ変数
//======================================================================
CInputKeyboard *CManager::m_InputKeyboard = NULL;		// キーボードへのポインタ
CInputMouse *CManager::m_InputMouse = NULL;			// マウスへのポインタ
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

	// imguiの初期化と設定
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Init(hWnd, CRenderer::GetDevice());
	ImGui::StyleColorsClassic();
#endif

	// キーボード処理初期化
	m_InputKeyboard = new CInputKeyboard;
	m_InputKeyboard->Init(hInstance, hWnd);

	// マウス処理初期化
	m_InputMouse = new CInputMouse;
	m_InputMouse->Init(hInstance, hWnd);

	// テクスチャの初期化
	CTexture::Init();

	// フィールド
	CField* field = CField::Create(TEX_ID_FIELD001, 2.0f, 20, 20, true);

	// プレイヤー
	player = CPlayer::Create(MODEL_ID_XBOT, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	player->SetField(field);

	// 敵
	enemy = CEnemy::Create(MODEL_ID_XBOT, D3DXVECTOR3(0.0f, 0.0f, 5.0f));
	enemy->SetField(field);

	// 空
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

	// 全てのテクスチャの解放
	CTexture::ReleaseAll();

	// キーボードの開放処理
	if (m_InputKeyboard)
	{
		m_InputKeyboard->Uninit();
		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// マウスの開放処理
	if (m_InputMouse)
	{
		m_InputMouse->Uninit();
		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	// imguiの終了処理
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Uninit();
#endif

	// レンダラークラスの終了処理
	CRenderer::Uninit();
}

void CManager::Update()
{
	// キーボード更新処理
	if (m_InputKeyboard)
	{
		m_InputKeyboard->Update();
	}

	// マウス更新処理
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

	//Direct3Dによる描画の開始
	if (SUCCEEDED(hr))
	{
		//描画
		CScene::DrawAll();

		CBillBoard::DrawAll(player->GetCamera());

		// デバッグ用imguiウィンドウの描画
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
