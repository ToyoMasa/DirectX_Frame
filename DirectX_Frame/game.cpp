//======================================================================
//	ゲーム画面管理
//
//======================================================================
#include "common.h"
#include "main.h"
#include "mode.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneModel.h"
#include "sceneSkinMesh.h"
#include "SkinMeshFile.h"
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
#include "number.h"
#include "game.h"
#include "result.h"
#include "particle.h"
#include "emitter.h"
#include "action.h"
#include "root.h"
#include "fade.h"
#include "Effekseer.h"
#include "wall.h"

CBillBoard *CModeGame::tree1 = NULL;
CBillBoard *CModeGame::tree2 = NULL;
CPlayer *CModeGame::player = NULL;
CEnemy *CModeGame::enemy[2] = { NULL };
CEnemy *CModeGame::Target = NULL;
CLight *CModeGame::m_Light;
bool CModeGame::m_PlayerDied = false;
bool CModeGame::m_TargetDied = false;
CScene2D *CModeGame::Load = NULL;
CScene2D *CModeGame::LoadFrame = NULL;
CScene2D *CModeGame::LoadGage = NULL;
int CModeGame::m_NumKill = 0;
int CModeGame::m_NumSneak = 0;

float g_test = 0;

void CModeGame::Init()
{
	// テクスチャの初期化
	CTexture::Init();

	Load = CScene2D::Create(TEX_ID_NOWLOADING, 1545 / 2.0f, 414 / 2.0f);
	Load->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));

	LoadFrame = CScene2D::Create(TEX_ID_LOADFRAME, 960, 64);
	LoadFrame->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0));

	LoadGage = CScene2D::Create(TEX_ID_LOADGAGE, 950, 54);
	LoadGage->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0));

	HRESULT hr;
	hr = CRenderer::DrawBegin();

	// ロード画面を描画
	if (SUCCEEDED(hr))
	{
		//描画
		Load->Draw();
		LoadFrame->Draw();

		CRenderer::DrawEnd();
	}

	// ルートの設定
	CRoot::Set();

	// フェード
	CFade::FadeIn();

	// フィールド
	CField* field = CField::Create(TEX_ID_FIELD001, 20.0f, 20, 20, true);

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.1f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.1f / 2.0f, SCREEN_HEIGHT / 2 + 200.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();

			CRenderer::DrawEnd();
		}
	}

	// プレイヤー
	player = CPlayer::Create(MODEL_ID_PLAYER, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	player->SetField(field);

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.3f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.3f / 2.0f, SCREEN_HEIGHT / 2 + 200.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();

			CRenderer::DrawEnd();
		}
	}

	// 敵
	enemy[0] = CEnemy::Create(SM_ID_ENEMY01, D3DXVECTOR3(7.0f, 0.0f, 5.0f), 1, field);

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.5f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.5f / 2.0f, SCREEN_HEIGHT / 2 + 200.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();

			CRenderer::DrawEnd();
		}
	}

	enemy[1] = CEnemy::Create(SM_ID_ENEMY01, D3DXVECTOR3(0.0f, 0.0f, -8.0f), 1, field);
	enemy[1]->SetAction(CActionMoveToRandom::Create(enemy[1], 3.0f, 3.5f, 0.02f));

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.75f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.75f / 2.0f, SCREEN_HEIGHT / 2 + 200.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();

			CRenderer::DrawEnd();
		}
	}

	Target = CEnemy::Create(SM_ID_ENEMY02, D3DXVECTOR3(0.0f, 0.0f, 8.0f), 1, field, ENEMY_TYPE_TARGET);
	Target->SetAction(CActionWait::Create(Target));

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950, 54));
		LoadGage->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();

			CRenderer::DrawEnd();
		}
	}

	// 空
	CSkyBox::Create(player);

	// ライト
	m_Light = CLight::Create(0);

	CBillBoard::Init();

	MakeMap();

	// スコア等のリセット
	m_PlayerDied = false;
	m_TargetDied = false;
	m_NumKill = 0;
	m_NumSneak = 0;

	// ロード画面を解放
	Load->Release();
	LoadFrame->Release();
	LoadGage->Release();
}

void CModeGame::Uninit()
{
	CCharacter::ReleaseAll();

	CScene::ReleaseAll();

	CActionBase::ReleaseAll();

	CParticle::ReleaseAll();

	m_Light->Release();

	CBillBoard::Uninit();

	// 全てのテクスチャの解放
	CTexture::ReleaseAll();
}

void CModeGame::Update()
{
	if (!CFade::GetFadeOut())
	{
		CCharacter::UpdateAll();
		CScene::UpdateAll();
		CParticle::UpdateAll();
		CBillBoard::UpdateAll();

		CInputKeyboard *inputKeyboard;
		CInputMouse *inputMouse;
		float mouseX, mouseY, mouseZ;

		// キーボード取得
		inputKeyboard = CManager::GetInputKeyboard();

		// マウス取得
		inputMouse = CManager::GetInputMouse();
		mouseX = (float)inputMouse->GetAxisX();
		mouseY = (float)inputMouse->GetAxisY();
		mouseZ = (float)inputMouse->GetAxisZ();

		if (m_TargetDied)
		{
			CFade::FadeOut(new CModeResult(m_NumKill, m_NumSneak, true));
		}

		if (m_PlayerDied)
		{
			CFade::FadeOut(new CModeResult(m_NumKill, m_NumSneak, false));
		}
	}
}

void CModeGame::Draw()
{
	CScene::DrawAll();
	CBillBoard::DrawAll(player->GetCamera());

	// デバッグ用imguiウィンドウの描画
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::BeginDraw();

	D3DXVECTOR3 pos = player->GetPos();
	ImGui::Begin("Debug Window", 0);
	ImGui::Text("X = %.2f Y = %.2f Z = %.2f", pos.x, pos.y, pos.z);
	//ImGui::Text("test = %.2f", g_test);
	ImGui::End();

	CImGui::EndDraw();
#endif
}

void CModeGame::TargetKilled()
{
	m_TargetDied = true;
}

void CModeGame::test(float test)
{
	g_test = test;
}

void CModeGame::MakeMap()
{
	CWall::Create(D3DXVECTOR3(13.5f, 0.0f, -24.5f), 23.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-13.5f, 0.0f, -24.5f), 23.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-24.5f, 0.0f, -2.0f), 1.0f, 4.0f, 44.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(24.5f, 0.0f, -13.0f), 1.0f, 4.0f, 22.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 24.5f), 50.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(9.5f, 0.0f, 12.5f), 7.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-22.0f, 0.0f, -13.5f), 4.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-8.5f, 0.0f, -16.0f), 1.0f, 4.0f, 4.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-8.5f, 0.0f, -22.0f), 1.0f, 4.0f, 4.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-13.0f, 0.0f, -13.5f), 10.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(7.5f, 0.0f, -18.5f), 1.0f, 4.0f, 11.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-14.5f, 0.0f, 2.5f), 1.0f, 4.0f, 9.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(5.5f, 0.0f, 18.0f), 1.0f, 4.0f, 12.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-12.0f, 0.0f, 18.5f), 4.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-20.0f, 0.0f, 18.5f), 8.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-19.0f, 0.0f, 12.5f), 10.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-11.5f, 0.0f, 21.5f), 1.0f, 4.0f, 5.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-5.0f, 0.0f, 18.5f), 6.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(1.0f, 0.0f, 18.5f), 2.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(1.5f, 0.0f, 21.5f), 1.0f, 4.0f, 5.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-19.0f, 0.0f, -7.5f), 10.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(20.5f, 0.0f, 12.5f), 7.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-24.5f, 0.0f, 23.5f), 1.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(24.5f, 0.0f, 13.0f), 1.0f, 4.0f, 22.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(10.5f, 0.0f, -12.5f), 7.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(21.0f, 0.0f, -12.5f), 6.0f, 4.0f, 1.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-14.5f, 0.0f, 11.0f), 1.0f, 4.0f, 2.0f, TEX_ID_WALL01);
	CWall::Create(D3DXVECTOR3(-14.5f, 0.0f, -6.0f), 1.0f, 4.0f, 2.0f, TEX_ID_WALL01);
}
