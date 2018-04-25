//======================================================================
//	DirectXテンプレ（main）
//
//======================================================================
#include <Windows.h>
#include "common.h"
#include "main.h"
#include "camera.h"
#include "light.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneModel.h"

//======================================================================
//	定義
//======================================================================
#define CLASS_NAME "sample"						//クラスの名前
#define WINDOW_NAME "ウィンドウの表示"			//タイトルの名前

//======================================================================
//	グローバル変数
//======================================================================
LPDIRECT3D9			g_pD3D = NULL;				//Direct3Dインターフェース
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;		//Direct3Dデバイス
CScene2D *scene2D;
CScene3D *scene3D;
CSceneModel *model;
CCamera *camera;
CLight *light;

//======================================================================
//	プロトタイプ宣言
//======================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	//ウィンドウプロシージャ

bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UnInit(void);
void Update(void);
void Draw(void);

//======================================================================
//	main関数
//======================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),						//自分の構造体のサイズを記入する
		CS_VREDRAW | CS_HREDRAW,				//詳細はwebで
		WndProc,								//ウィンドウプロシージャ関数ポインタ（関数名だけでポインタになる）
		0,
		0,
		hInstance,								//WinMainの引数に宣言されている
		NULL,									//指定したいアイコンがあれば指定できる
		LoadCursor(NULL, IDC_ARROW),			//カーソルのアイコンを指定
		(HBRUSH)(COLOR_WINDOW + 1),				//Windowのクラウド領域の色を指定
		NULL,									//メニューネーム
		CLASS_NAME,								//クラスネーム（WindowのパーツをOSに伝えるための名前）
		NULL
	};

	RegisterClassEx(&wcex);						//Windowクラス登録

	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	DWORD Style = ((WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) ^ WS_MAXIMIZEBOX) & WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&wr, Style, false);

	int WinWidth = SCREEN_WIDTH + 16;
	int WinHeight = SCREEN_HEIGHT + 39;

	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	int WinX = 1536 < WinWidth ? 0 : (1536 - WinWidth) / 2;
	int WinY = 864 < WinHeight ? 0 : (864 - WinHeight) / 2;

	HWND hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		Style,
		WinX,									//Windowの左上X座標、左上Y座標、幅（フレーム含む）
		WinY,
		(WinWidth),
		(WinHeight),
		NULL,									//親Windowへのハンドル
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);					//表示

	UpdateWindow(hWnd);							//更新


	if (!Init(hInstance, hWnd, TRUE))
	{
		MessageBox(hWnd, "初期化に失敗しました。", "エラー", MB_OK);
	}

	MSG msg;									//宣言

	//======================================================================
	//	ゲームループ
	//======================================================================
	DWORD dwExecLastTime = 0;					//前フレームの時間
	DWORD dwCurrentTime = 0;					//現在の時間

	timeBeginPeriod(1);							//分解能を設定

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//60fpsでループするようにする。
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000)
			{
				//ゲーム処理
				Update();

				Draw();

				dwExecLastTime = dwCurrentTime;
			}
		}
	} while (msg.message != WM_QUIT);

	UnInit();

	timeEndPeriod(1);							//分解能を戻す

	return (int)msg.wParam;						//決まり
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:							//×を押されるなどでウィンドウが閉じられたら
		PostQuitMessage(0);						//WM_QUITメッセージの送信（このメッセージが呼ばれたら強制終了する）
		break;

	case WM_KEYDOWN:							//キーボードからの入力取得
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;

		default:
			break;
		}

		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//これをしないと正常に終了しないかもしれない。逆に基本的な動きをさせたくない時には呼ばない
}

bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;

	//Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return false;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}

	//デバイスのプレゼンテーションパラメータの設定
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//[デバイス作成制御]<描画>と<頂点処理>をハードウェアで行う
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,						//ディスプレイアダプタ
		D3DDEVTYPE_HAL,							//デバイスタイプ
		hWnd,									//フォーカスするウィンドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	//デバイス作成制御の組み合わせ
		&d3dpp,									//デバイスのプレゼンテーションへのポインタ
		&g_pD3DDevice)))						//デバイスインタフェースへのポインタ　※最重要
	{
		//上記の設定が失敗したら
		MessageBox(hWnd, "Direct3Dデバイスの作成に失敗しました", "エラー", MB_OK);
		return false;
	}

	//レンダ―ステートパラメータの設定
	//SRC…今から描くもの。つまりポリゴンにテクスチャを貼ったもの。
	//DEST…すでに描画されている画面のこと。
	//SRC_RGB * SRC_α + DEST_RGB * (1 - SRC_α)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	// 照明
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//ポリゴンとテクスチャの色の乗算
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);			//左辺値
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);			//右辺値

	//テクスチャのピクセルに関する設定
	//テクスチャアドレス外を参照した時にどうするか
	//WRAP = 反復（繰り返し）
	//CLAMP = 一番最後のピクセルを引き延ばす
	//MIRROR = 反転（U方向のみ、V方向のみもできる）
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//D3DTEXF_POINT　＝　周りの点を無理やり持ってくる→ドット絵を強調する時に使う
	//D3DTEXF_LINEAR　＝　アンチエイリアシングのようになめらかにする(基本こっち)
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);			//実際のテクスチャサイズより小さい時のフィルタリング
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);			//実際のテクスチャサイズより大きい時のフィルタリング
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);			//ミップマップ（元の画像の÷２の単位で自動で作られる画像）間を補正する

	scene2D = new CScene2D();
	scene2D->Init(128, 128);

	scene3D = new CScene3D();
	scene3D->Init("data/textures/field001.jpg");

	model = new CSceneModel();
	model->Init("data/models/player_ufo.x");

	model->Move(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	camera = new CCamera();
	camera->Init(D3DXVECTOR3(0.0f, 3.0f, -3.0f), D3DXVECTOR3(0, 0, 0));

	light = new CLight();
	light->Init(0);

	return true;
}

void UnInit(void)
{
	scene2D->Uninit();
	delete scene2D;

	scene3D->Uninit();
	delete scene3D;

	model->Uninit();
	delete model;

	camera->Uninit();
	delete camera;

	light->Uninit();
	delete light;

	if (g_pD3DDevice != NULL)
	{//デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{//Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

void Update(void)
{
	scene2D->Set(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	scene3D->Update();

	model->Update();

	camera->Update();
}

void Draw(void)
{
	//クリア処理
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(64, 96, 255, 255), 1.0f, 0);

	//Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//描画
		scene2D->Draw();

		scene3D->Draw();

		model->Draw();

		//Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);	//第三引数はhWndでも可
}

LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}
