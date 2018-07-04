//======================================================================
//	タイトル画面管理
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
#include "title.h"
#include "game.h"

CScene2D* CModeTitle::m_TitleLogo = NULL;

void CModeTitle::Init()
{
	// テクスチャの初期化
	CTexture::Init();

	m_TitleLogo = CScene2D::Create(TEX_ID_TITLE, 256.0f, 64.0f);
	m_TitleLogo->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
}

void CModeTitle::Uninit()
{
	// 全てのテクスチャの解放
	CTexture::ReleaseAll();

	CScene::ReleaseAll();
}

void CModeTitle::Update()
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

	CScene::UpdateAll();

	if (inputMouse->GetLeftTrigger() || inputKeyboard->GetKeyTrigger(DIK_SPACE)) 
	{
		CManager::SetMode(new CModeGame());
	}

}

void CModeTitle::Draw()
{
	CScene::DrawAll();
}
