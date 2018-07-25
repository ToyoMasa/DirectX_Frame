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

CBillBoard *CModeGame::tree1 = NULL;
CBillBoard *CModeGame::tree2 = NULL;
CPlayer *CModeGame::player = NULL;
CEnemy *CModeGame::enemy[2] = { NULL };
CEnemy *CModeGame::Target = NULL;
CLight *CModeGame::m_Light;
CParticleEmitter emitter;
bool CModeGame::m_PlayerDied = false;
bool CModeGame::m_TargetDied = false;

void CModeGame::Init()
{
	// ルートの設定
	CRoot::Set();

	// テクスチャの初期化
	CTexture::Init();

	// フェード
	CFade::Init();
	CFade::FadeIn();

	// フィールド
	CField* field = CField::Create(TEX_ID_FIELD001, 2.0f, 20, 20, true);

	// プレイヤー
	player = CPlayer::Create(MODEL_ID_PLAYER, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	player->SetField(field);

	// 敵
	enemy[0] = CEnemy::Create(MODEL_ID_ENEMY01, D3DXVECTOR3(7.0f, 0.0f, 5.0f), 1, field);
	enemy[1] = CEnemy::Create(MODEL_ID_ENEMY01, D3DXVECTOR3(0.0f, 0.0f, -8.0f), 1, field);
	enemy[1]->SetAction(CActionMoveToRandom::Create(enemy[1], 3.0f, 3.5f, 0.02f));
	Target = CEnemy::Create(MODEL_ID_TARGET, D3DXVECTOR3(0.0f, 0.0f, 8.0f), CActionWait::Create(Target), field, ENEMY_TYPE_TARGET);

	// 空
	CSkyBox::Create(player);

	m_Light = CLight::Create(0);

	CBillBoard::Init();

	tree1 = CBillBoard::Create(TEX_ID_TREE);
	tree2 = CBillBoard::Create(TEX_ID_TREE);

	tree1->Set(TEX_ID_TREE, D3DXVECTOR3(1.0f, 0.0f, 1.0f), 2.0f, 1);
	tree2->Set(TEX_ID_TREE, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 2.0f, 1);

	// パーティクルエミッター
	emitter.Init(TEX_ID_STAR, 300, 3, 300, 0.2f, 0.0f,
		D3DXVECTOR3(0.0f, 0.0f, 3.0f),
		D3DXVECTOR3(-0.006f, 0.03f, -0.006f),
		D3DXVECTOR3(0.006f, 0.035f, 0.006f),
		D3DXVECTOR3(0.0f, -0.0002f, 0.0f),
		false);

	// 数字
	//CNumber::Init();

	m_PlayerDied = false;
	m_TargetDied = false;
}

void CModeGame::Uninit()
{
	CCharacter::ReleaseAll();
	CActionBase::ReleaseAll();

	//CNumber::Uninit();

	CScene::ReleaseAll();

	CParticle::ReleaseAll();

	m_Light->Release();

	CBillBoard::Uninit();

	CFade::Uninit();

	// 全てのテクスチャの解放
	CTexture::ReleaseAll();
}

void CModeGame::Update()
{
	CFade::Update();

	emitter.Update();

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
		CManager::SetMode(new CModeResult());
	}

	if (m_PlayerDied)
	{
		CManager::SetMode(new CModeResult());
	}
}

void CModeGame::Draw()
{
	CScene::DrawAll();

	CBillBoard::DrawAll(player->GetCamera());

	//CFade::Draw();

	// デバッグ用imguiウィンドウの描画
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::BeginDraw();

	D3DXVECTOR3 pos = player->GetPos();
	ImGui::Begin("Debug Window", 0);
	ImGui::Text("X = %.2f Y = %.2f Z = %.2f", pos.x, pos.y, pos.z);
	ImGui::End();

	CImGui::EndDraw();
#endif
}

void CModeGame::TargetKilled()
{
	m_TargetDied = true;
}
