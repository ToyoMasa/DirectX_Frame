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

CBillBoard *CModeGame::tree1 = NULL;
CBillBoard *CModeGame::tree2 = NULL;
CPlayer *CModeGame::player = NULL;
CEnemy *CModeGame::enemy = NULL;
CLight *CModeGame::m_Light;
CParticleEmitter emitter;

void CModeGame::Init()
{
	// テクスチャの初期化
	CTexture::Init();

	// フィールド
	CField* field = CField::Create(TEX_ID_FIELD001, 2.0f, 20, 20, true);

	// プレイヤー
	player = CPlayer::Create(MODEL_ID_PLAYER, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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
}

void CModeGame::Uninit()
{
	CCharacter::ReleaseAll();

	//CNumber::Uninit();

	CScene::ReleaseAll();

	CParticle::ReleaseAll();

	m_Light->Release();

	CBillBoard::Uninit();

	// 全てのテクスチャの解放
	CTexture::ReleaseAll();
}

void CModeGame::Update()
{
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
	if (isCollisionCapsule(player->GetCapsule(), enemy->GetCapsule()))
	{
		ImGui::Text("Hit");
	}
	ImGui::End();

	CImGui::EndDraw();
#endif
}
