//======================================================================
//	DirectX�e���v���imain�j
//
//======================================================================
#include <Windows.h>
#include "common.h"
#include "main.h"
#include "renderer.h"
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
	if (!CRenderer::Init(hWnd, bWindow))
	{
		return false;
	}

	// imgui�̏������Ɛݒ�
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Init(hWnd, CRenderer::GetDevice());
#endif

	ImGui::StyleColorsClassic();

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

	// imgui�̏I������
#if defined(_DEBUG) || defined(DEBUG)
	CImGui::Uninit();
#endif
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
	HRESULT hr;

	hr = CRenderer::DrawBegin();

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(hr))
	{
		//�`��
		scene2D->Draw();

		scene3D->Draw();

		model->Draw();

// �f�o�b�O�pimgui�E�B���h�E�̕`��
#if defined(_DEBUG) || defined(DEBUG)
		CImGui::BeginDraw();
		CImGui::EndDraw();
#endif

		CRenderer::DrawEnd();
	}
}
