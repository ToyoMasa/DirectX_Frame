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
#include "shader.h"

CBillBoard *CModeGame::tree1 = NULL;
CBillBoard *CModeGame::tree2 = NULL;
CPlayer *CModeGame::player = NULL;
CEnemy *CModeGame::enemy[ENEMY_NUM] = { NULL };
CEnemy *CModeGame::Target = NULL;
CLight *CModeGame::m_Light;
bool CModeGame::m_PlayerDied = false;
bool CModeGame::m_TargetDied = false;
bool CModeGame::m_PlayBGM = false;
bool CModeGame::m_Pause = false;
CScene2D *CModeGame::Load = NULL;
CScene2D *CModeGame::LoadFrame = NULL;
CScene2D *CModeGame::LoadGage = NULL;
CScene2D *CModeGame::GameClear = NULL;
CScene2D *CModeGame::GameOver = NULL;
CScene2D *CModeGame::Mission = NULL;
CScene2D *CModeGame::Wanted = NULL;
CScene2D *CModeGame::Tutorial = NULL;
CScene2D *CModeGame::Tutorial2 = NULL;
CScene2D *CModeGame::Black = NULL;
CScene2D *CModeGame::Pause = NULL;
CScene2D *CModeGame::HowToUse = NULL;
CSound *CModeGame::BGM = NULL;
CSound *CModeGame::GameEnd_SE = NULL;
int CModeGame::m_NumKill = 0;
int CModeGame::m_NumSneak = 0; 
int CModeGame::m_CountResult = 0;
int CModeGame::m_Count = 0;

float g_test = 0;

void CModeGame::Init()
{
	// テクスチャの初期化
	CTexture::Init();

	BGM = CSound::Create(SOUND_LABEL_BGM_LOAD);
	BGM->Play();

	Black = CScene2D::Create(TEX_ID_BLACK, SCREEN_WIDTH, SCREEN_HEIGHT);
	Black->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
	Black->SetColor(D3DCOLOR_RGBA(0, 0, 0, 128));
	Black->SetVisible(false);

	Wanted = CScene2D::Create(TEX_ID_WANTED, 280, 400);
	Wanted->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50.0f, 0));

	Tutorial = CScene2D::Create(TEX_ID_TUTORIAL, 760, 400);
	Tutorial->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 0));

	Tutorial2 = CScene2D::Create(TEX_ID_TURORIAL_PAUSE, 920, 130);
	Tutorial2->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100.0f, 0));

	Load = CScene2D::Create(TEX_ID_NOWLOADING, 1545 / 6.0f, 414 / 6.0f);
	Load->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 230.0f, 0));

	LoadFrame = CScene2D::Create(TEX_ID_LOADFRAME, 960, 64);
	LoadFrame->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0));

	LoadGage = CScene2D::Create(TEX_ID_LOADGAGE, 950, 54);
	LoadGage->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0));

	GameClear = CScene2D::Create(TEX_ID_MISSION_COMPLETE, 1039, 128);
	GameClear->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
	GameClear->SetVisible(false);

	GameOver = CScene2D::Create(TEX_ID_MISSION_FAILED, 923, 128);
	GameOver->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
	GameOver->SetVisible(false);

	Mission = CScene2D::Create(TEX_ID_MISSION, 250, 65);
	Mission->Set(D3DXVECTOR3(140, 40, 0));
	Mission->SetVisible(false);

	Pause = CScene2D::Create(TEX_ID_PAUSE, 172, 97);
	Pause->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0));
	Pause->SetVisible(false);

	HowToUse = CScene2D::Create(TEX_ID_HOWTOUSE, 360, 90);
	HowToUse->Set(D3DXVECTOR3(200, SCREEN_HEIGHT - 60.0f, 0));

	HRESULT hr;
	hr = CRenderer::DrawBegin();

	// ロード画面を描画
	if (SUCCEEDED(hr))
	{
		//描画
		Load->Draw();
		LoadFrame->Draw();
		Wanted->Draw();

		CRenderer::DrawEnd();
	}

	// ルートの設定
	CRoot::Set();

	// フェード
	CFade::FadeIn();

	// フィールド
	CField* field = CField::Create(NULL, 10.0f, 20, 20, true);

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.1f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.1f / 2.0f, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Wanted->Draw();

			CRenderer::DrawEnd();
		}
	}

	// プレイヤー
	player = CPlayer::Create(MODEL_ID_PLAYER, D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	player->SetField(field);
	CManager::SetCamera(player->GetCamera());

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.2f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.2f / 2.0f, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Wanted->Draw();

			CRenderer::DrawEnd();
		}
	}

	//// 敵
	enemy[0] = CEnemy::Create(SM_ID_ENEMY01, D3DXVECTOR3(7.0f, 0.0f, 5.0f), 1, field);

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.3f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.3f / 2.0f, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Wanted->Draw();

			CRenderer::DrawEnd();
		}
	}

	enemy[1] = CEnemy::Create(SM_ID_ENEMY01, D3DXVECTOR3(22.0f, 0.0f, 3.0f), 1, field);
	enemy[1]->SetRotation(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	enemy[1]->SetAction(CActionWait::Create(enemy[1]));

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.4f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.4f / 2.0f, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Wanted->Draw();

			CRenderer::DrawEnd();
		}
	}

	enemy[2] = CEnemy::Create(SM_ID_ENEMY01, D3DXVECTOR3(-1.0f, 0.0f, 17.0f), 1, field);
	enemy[2]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	enemy[2]->SetAction(CActionWait::Create(enemy[2]));

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.5f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.5f / 2.0f, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Wanted->Draw();

			CRenderer::DrawEnd();
		}
	}

	enemy[3] = CEnemy::Create(SM_ID_ENEMY01, D3DXVECTOR3(3.0f, 0.0f, -22.0f), 1, field);
	enemy[3]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	enemy[3]->SetAction(CActionWait::Create(enemy[3]));

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.6f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.6f / 2.0f, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Tutorial->Draw();
			Tutorial2->Draw();

			CRenderer::DrawEnd();
		}
	}

	enemy[4] = CEnemy::Create(SM_ID_ENEMY01, D3DXVECTOR3(-20.0f, 0.0f, 8.5f), 5, field);

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.7f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.7f / 2.0f, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Tutorial->Draw();
			Tutorial2->Draw();

			CRenderer::DrawEnd();
		}
	}

	enemy[5] = CEnemy::Create(SM_ID_ENEMY01, D3DXVECTOR3(-11.0f, 0.0f, -16.0f), 10, field);

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.8f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.8f / 2.0f, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Tutorial->Draw();
			Tutorial2->Draw();

			CRenderer::DrawEnd();
		}
	}

	enemy[6] = CEnemy::Create(SM_ID_ENEMY01, D3DXVECTOR3(15.0f, 0.0f, 20.0f), 13, field);

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950 * 0.9f, 54));
		LoadGage->Set(D3DXVECTOR3((SCREEN_WIDTH / 2 - 950 / 2.0f) + 950 * 0.9f / 2.0f, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Tutorial->Draw();
			Tutorial2->Draw();

			CRenderer::DrawEnd();
		}
	}

	// ターゲット
	Target = CEnemy::Create(SM_ID_ENEMY02, D3DXVECTOR3(0.0f, 0.0f, 8.0f), 1, field, ENEMY_TYPE_TARGET);
	Target->SetAction(CActionWait::Create(Target));

	{
		hr = CRenderer::DrawBegin();
		LoadGage->SetSize(D3DXVECTOR2(950, 54));
		LoadGage->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0));

		// ロード画面を描画
		if (SUCCEEDED(hr))
		{
			//描画
			Load->Draw();
			LoadFrame->Draw();
			LoadGage->Draw();
			Tutorial->Draw();
			Tutorial2->Draw();

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
	m_PlayBGM = false;
	m_NumKill = 0;
	m_NumSneak = 0;
	m_CountResult = 0;
	GameEnd_SE = NULL;

	// ロード画面を解放
	Load->Release();
	LoadFrame->Release();
	LoadGage->Release();
	Wanted->Release();
	Tutorial2->Release();

	Tutorial->SetVisible(false);
	Tutorial->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100.0f, 0));
	Mission->SetVisible(true);

	// 曲を変更
	BGM->Release();
}

void CModeGame::Uninit()
{
	CCharacter::ReleaseAll();

	CScene::ReleaseAll();

	CSound::ReleaseAll();

	CActionBase::ReleaseAll();

	CParticle::ReleaseAll();

	m_Light->Release();

	CBillBoard::Uninit();

	// 全てのテクスチャの解放
	CTexture::ReleaseAll();
}

void CModeGame::Update()
{
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

	if (!CFade::GetFade())
	{
		if (!m_PlayBGM)
		{
			BGM = CSound::Create(SOUND_LABEL_BGM_GAME);
			BGM->Play();
			m_PlayBGM = true;
		}
	}

	if (!CFade::GetFadeOut())
	{
		if (m_Pause)
		{
			m_Count++;

			if (m_Count / 256 % 2 == 0.0f)
			{
				Pause->SetColor(D3DCOLOR_RGBA(255, 255, 255, m_Count % 256));
			}
			else
			{
				Pause->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255 - (m_Count % 256)));
			}

			if (inputKeyboard->GetKeyTrigger(DIK_P) || inputKeyboard->GetKeyTrigger(DIK_TAB))
			{
				CallPause();
			}
		}
		else
		{
			CCharacter::UpdateAll();
			CScene::UpdateAll();
			CParticle::UpdateAll();
			CBillBoard::UpdateAll();

			if (m_TargetDied)
			{
				m_CountResult++;

				if (GameEnd_SE == NULL)
				{
					GameEnd_SE = CSound::Create(SOUND_LABEL_SE_GAMECLEAR);
					GameEnd_SE->Play();
				}

				if (m_CountResult > 255)
				{
					if (m_CountResult > 300)
					{
						CFade::FadeOut(new CModeResult(m_NumKill, m_NumSneak, true));
					}
				}
				else
				{
					GameClear->SetColor(D3DCOLOR_RGBA(255, 255, 255, m_CountResult));
				}
			}
			else if (m_PlayerDied)
			{
				if (GameEnd_SE == NULL)
				{
					GameEnd_SE = CSound::Create(SOUND_LABEL_SE_GAMEOVER);
					GameEnd_SE->Play();
					GameOver->SetVisible(true);
				}

				m_CountResult++;
				if (m_CountResult > 255)
				{
					if (m_CountResult > 300)
					{
						CFade::FadeOut(new CModeResult(m_NumKill, m_NumSneak, false));
					}
				}
				else
				{
					GameClear->SetColor(D3DCOLOR_RGBA(255, 255, 255, m_CountResult));
				}
			}

			if (inputKeyboard->GetKeyTrigger(DIK_P) || inputKeyboard->GetKeyTrigger(DIK_TAB))
			{
				CallPause();
			}
		}
	}
}

void CModeGame::Draw()
{
	CScene::DrawAll();
	CBillBoard::DrawAll(player->GetCamera());

	CImGui::BeginDraw();

	D3DXVECTOR3 pos = player->GetPos();
	ImGui::Begin("Debug Window", 0);
	ImGui::Text("X = %.2f Y = %.2f Z = %.2f", pos.x, pos.y, pos.z);
	//ImGui::Text("test = %.2f", g_test);
	ImGui::End();

	CImGui::EndDraw();
}

void CModeGame::PlayerDied()
{
	m_PlayerDied = true;
}

void CModeGame::TargetKilled()
{
	m_TargetDied = true;
	GameClear->SetVisible(true);
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

void CModeGame::CallPause()
{
	if (m_Pause)
	{
		m_Pause = false;
		Black->SetVisible(false);
		Pause->SetVisible(false);
		Tutorial->SetVisible(false);
	}
	else
	{
		m_Pause = true;
		Black->SetVisible(true);
		Pause->SetVisible(true);
		Tutorial->SetVisible(true);
	}
}
