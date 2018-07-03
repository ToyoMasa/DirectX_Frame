////======================================================================
////	ゲーム画面管理
////
////======================================================================
//#include "common.h"
//#include "main.h"
//#include "scene.h"
//#include "scene2D.h"
//#include "scene3D.h"
//#include "sceneModel.h"
//#include "camera.h"
//#include "light.h"
//#include "manager.h"
//#include "texture.h"
//#include "billboard.h"
//#include "field.h"
//#include "player.h"
//#include "enemy.h"
//#include "input.h"
//#include "skybox.h"
//#include "number.h"
//#include "mode.h"
//#include "game.h"
//
//CBillBoard* tree1;
//CBillBoard* tree2;
//int testNumber = 0;
//bool test = false;
//CPlayer* player;
//CEnemy* enemy;
//
//void CModeGame::Init()
//{
//	// フィールド
//	CField* field = CField::Create(TEX_ID_FIELD001, 2.0f, 20, 20, true);
//
//	// プレイヤー
//	player = CPlayer::Create(MODEL_ID_XBOT, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//	player->SetField(field);
//
//	// 敵
//	enemy = CEnemy::Create(MODEL_ID_XBOT, D3DXVECTOR3(0.0f, 0.0f, 5.0f));
//	enemy->SetField(field);
//
//	// 空
//	CSkyBox::Create(player);
//
//	CScene2D* test = CScene2D::Create(TEX_ID_CURSOR, 128, 128);
//	test->Set(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
//
//	tree1 = CBillBoard::Create(TEX_ID_TREE);
//	tree2 = CBillBoard::Create(TEX_ID_TREE);
//
//	tree1->Set(TEX_ID_TREE, D3DXVECTOR3(1.0f, 0.0f, 1.0f), 2.0f, 1);
//	tree2->Set(TEX_ID_TREE, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 2.0f, 1);
//
//	// 数字
//	CNumber::Init();
//}
//
//void CModeGame::Uninit()
//{
//
//}
//
//void CModeGame::Update()
//{
//
//}
//
//void CModeGame::Draw()
//{
//
//}
