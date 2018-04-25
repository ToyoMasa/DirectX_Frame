//======================================================================
//	DirectX�e���v���imain�j
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
//	��`
//======================================================================
#define CLASS_NAME "sample"						//�N���X�̖��O
#define WINDOW_NAME "�E�B���h�E�̕\��"			//�^�C�g���̖��O

//======================================================================
//	�O���[�o���ϐ�
//======================================================================
LPDIRECT3D9			g_pD3D = NULL;				//Direct3D�C���^�[�t�F�[�X
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;		//Direct3D�f�o�C�X
CScene2D *scene2D;
CScene3D *scene3D;
CSceneModel *model;
CCamera *camera;
CLight *light;

//======================================================================
//	�v���g�^�C�v�錾
//======================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	//�E�B���h�E�v���V�[�W��

bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UnInit(void);
void Update(void);
void Draw(void);

//======================================================================
//	main�֐�
//======================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),						//�����̍\���̂̃T�C�Y���L������
		CS_VREDRAW | CS_HREDRAW,				//�ڍׂ�web��
		WndProc,								//�E�B���h�E�v���V�[�W���֐��|�C���^�i�֐��������Ń|�C���^�ɂȂ�j
		0,
		0,
		hInstance,								//WinMain�̈����ɐ錾����Ă���
		NULL,									//�w�肵�����A�C�R��������Ύw��ł���
		LoadCursor(NULL, IDC_ARROW),			//�J�[�\���̃A�C�R�����w��
		(HBRUSH)(COLOR_WINDOW + 1),				//Window�̃N���E�h�̈�̐F���w��
		NULL,									//���j���[�l�[��
		CLASS_NAME,								//�N���X�l�[���iWindow�̃p�[�c��OS�ɓ`���邽�߂̖��O�j
		NULL
	};

	RegisterClassEx(&wcex);						//Window�N���X�o�^

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
		WinX,									//Window�̍���X���W�A����Y���W�A���i�t���[���܂ށj
		WinY,
		(WinWidth),
		(WinHeight),
		NULL,									//�eWindow�ւ̃n���h��
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);					//�\��

	UpdateWindow(hWnd);							//�X�V


	if (!Init(hInstance, hWnd, TRUE))
	{
		MessageBox(hWnd, "�������Ɏ��s���܂����B", "�G���[", MB_OK);
	}

	MSG msg;									//�錾

	//======================================================================
	//	�Q�[�����[�v
	//======================================================================
	DWORD dwExecLastTime = 0;					//�O�t���[���̎���
	DWORD dwCurrentTime = 0;					//���݂̎���

	timeBeginPeriod(1);							//����\��ݒ�

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//60fps�Ń��[�v����悤�ɂ���B
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000)
			{
				//�Q�[������
				Update();

				Draw();

				dwExecLastTime = dwCurrentTime;
			}
		}
	} while (msg.message != WM_QUIT);

	UnInit();

	timeEndPeriod(1);							//����\��߂�

	return (int)msg.wParam;						//���܂�
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:							//�~���������ȂǂŃE�B���h�E������ꂽ��
		PostQuitMessage(0);						//WM_QUIT���b�Z�[�W�̑��M�i���̃��b�Z�[�W���Ă΂ꂽ�狭���I������j
		break;

	case WM_KEYDOWN:							//�L�[�{�[�h����̓��͎擾
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
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

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//��������Ȃ��Ɛ���ɏI�����Ȃ���������Ȃ��B�t�Ɋ�{�I�ȓ��������������Ȃ����ɂ͌Ă΂Ȃ�
}

bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;

	//Direct3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return false;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
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

	//[�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs��
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,						//�f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,							//�f�o�C�X�^�C�v
		hWnd,									//�t�H�[�J�X����E�B���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	//�f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,									//�f�o�C�X�̃v���[���e�[�V�����ւ̃|�C���^
		&g_pD3DDevice)))						//�f�o�C�X�C���^�t�F�[�X�ւ̃|�C���^�@���ŏd�v
	{
		//��L�̐ݒ肪���s������
		MessageBox(hWnd, "Direct3D�f�o�C�X�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}

	//�����_�\�X�e�[�g�p�����[�^�̐ݒ�
	//SRC�c������`�����́B�܂�|���S���Ƀe�N�X�`����\�������́B
	//DEST�c���łɕ`�悳��Ă����ʂ̂��ƁB
	//SRC_RGB * SRC_�� + DEST_RGB * (1 - SRC_��)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	// �Ɩ�
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�|���S���ƃe�N�X�`���̐F�̏�Z
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);			//���Ӓl
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);			//�E�Ӓl

	//�e�N�X�`���̃s�N�Z���Ɋւ���ݒ�
	//�e�N�X�`���A�h���X�O���Q�Ƃ������ɂǂ����邩
	//WRAP = �����i�J��Ԃ��j
	//CLAMP = ��ԍŌ�̃s�N�Z�����������΂�
	//MIRROR = ���]�iU�����̂݁AV�����݂̂��ł���j
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//D3DTEXF_POINT�@���@����̓_�𖳗���莝���Ă��遨�h�b�g�G���������鎞�Ɏg��
	//D3DTEXF_LINEAR�@���@�A���`�G�C���A�V���O�̂悤�ɂȂ߂炩�ɂ���(��{������)
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);			//���ۂ̃e�N�X�`���T�C�Y��菬�������̃t�B���^�����O
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);			//���ۂ̃e�N�X�`���T�C�Y���傫�����̃t�B���^�����O
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);			//�~�b�v�}�b�v�i���̉摜�́��Q�̒P�ʂŎ����ō����摜�j�Ԃ�␳����

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
	{//�f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{//Direct3D�I�u�W�F�N�g�̊J��
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
	//�N���A����
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(64, 96, 255, 255), 1.0f, 0);

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//�`��
		scene2D->Draw();

		scene3D->Draw();

		model->Draw();

		//Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);	//��O������hWnd�ł���
}

LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}
