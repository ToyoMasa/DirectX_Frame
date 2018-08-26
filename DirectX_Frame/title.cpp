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
#include "title.h"
#include "game.h"
#include "fade.h"
#include "PlayerAnim.h"
#include "sound.h"

CScene2D* CModeTitle::m_TitleLogo = NULL;

CScene2D* pressSpace;
CSceneSkinMesh* mesh;
CCamera* camera;
CSound* bgm;
int count;

void CModeTitle::Init()
{
	// テクスチャの初期化
	CTexture::Init();

	m_TitleLogo = CScene2D::Create(TEX_ID_TITLE, 1153.0f, 323.0f);
	m_TitleLogo->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150.0f, 0.0f));

	pressSpace = CScene2D::Create(TEX_ID_PRESS_SPACE, 501.0f, 105.0f);
	pressSpace->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f));

	camera = CCamera::Create();
	camera->SetPos(D3DXVECTOR3(-0.2f, 1.7f, -1.0f));
	camera->SetAt(D3DXVECTOR3(0.0f, 1.5f, 0.0f));

	mesh = CSceneSkinMesh::Create(SKINMESH_SOURCE[SM_ID_PLAYER]);
	mesh->ChangeAnim(PLAYER_IDLE, 0.0f);

	// フェードイン
	CFade::FadeIn();

	bgm = CSound::Create(SOUND_LABEL_BGM_TITLE);
	bgm->Play();

	count = 0;
}

void CModeTitle::Uninit()
{
	// 全てのテクスチャの解放
	CTexture::ReleaseAll();

	CScene::ReleaseAll();

	camera->Release();

	bgm->Release();
}

void CModeTitle::Update()
{
	CInputKeyboard *inputKeyboard;
	CInputMouse *inputMouse;
	float mouseX, mouseY, mouseZ;

	camera->Update();

	// キーボード取得
	inputKeyboard = CManager::GetInputKeyboard();

	// マウス取得
	inputMouse = CManager::GetInputMouse();
	mouseX = (float)inputMouse->GetAxisX();
	mouseY = (float)inputMouse->GetAxisY();
	mouseZ = (float)inputMouse->GetAxisZ();

	count++;

	if (count / 256 % 2 == 0.0f)
	{
		pressSpace->SetColor(D3DCOLOR_RGBA(255, 255, 255, count % 256));
	}
	else
	{
		pressSpace->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255 - (count % 256)));
	}

	CScene::UpdateAll();

	if (inputMouse->GetLeftTrigger() || inputKeyboard->GetKeyTrigger(DIK_SPACE)) 
	{
		CFade::FadeOut(new CModeGame());
	}

}

void CModeTitle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	if (pDevice == NULL)
	{
		return;
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CScene::DrawAll();

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
