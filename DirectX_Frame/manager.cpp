//======================================================================
//	ゲーム管理
//
//======================================================================
#include "common.h"
#include "main.h"
#include "manager.h"
#include "texture.h"

//======================================================================
//	静的メンバ変数の初期化
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

	// imguiの初期化と設定
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Init(hWnd, CRenderer::GetDevice());
	ImGui::StyleColorsClassic();
#endif

	// テクスチャの初期化
	CTexture::Init();

	m_Scene[0] = CScene2D::Create(TEX_ID_CURSOR, 128, 128);
	m_Scene[0]->Set(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	m_Scene[1] = CScene3D::Create(TEX_ID_FIELD001);

	m_Model = CSceneModel::Create("data/models/player_ufo.x");

	m_Model->Move(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	m_Camera = new CCamera();
	m_Camera->Init(D3DXVECTOR3(0.0f, 3.0f, -3.0f), D3DXVECTOR3(0, 0, 0));

	m_Light = new CLight();
	m_Light->Init(0);

	return true;
}

void CManager::Uninit()
{
	for (int i = 0; i < 2; i++)
	{
		m_Scene[i]->Uninit();
		delete m_Scene[i];
	}

	m_Model->Uninit();
	delete m_Model;

	m_Camera->Uninit();
	delete m_Camera;

	m_Light->Uninit();
	delete m_Light;

	// 全てのテクスチャの解放
	CTexture::ReleaseAll();

	// imguiの終了処理
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Uninit();
#endif
}

void CManager::Update()
{
	for (int i = 0; i < 2; i++)
	{
		m_Scene[i]->Update();
	}

	m_Model->Update();

	m_Camera->Update();
}

void CManager::Draw()
{
	HRESULT hr;

	hr = CRenderer::DrawBegin();

	//Direct3Dによる描画の開始
	if (SUCCEEDED(hr))
	{
		//描画
		for (int i = 0; i < 2; i++)
		{
			m_Scene[i]->Draw();
		}

		m_Model->Draw();

		// デバッグ用imguiウィンドウの描画
#if defined(_DEBUG) || defined(DEBUG)
		CImGui::BeginDraw();
		CImGui::EndDraw();
#endif

		CRenderer::DrawEnd();
	}
}
