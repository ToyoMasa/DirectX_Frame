//======================================================================
//	���U���g��ʊǗ�
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
#include "result.h"

CScene2D* CModeResult::m_ResultText = NULL;

void CModeResult::Init()
{
	// �e�N�X�`���̏�����
	CTexture::Init();

	m_ResultText = CScene2D::Create(TEX_ID_RESULT, 256.0f, 64.0f);
	m_ResultText->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
}

void CModeResult::Uninit()
{
	// �S�Ẵe�N�X�`���̉��
	CTexture::ReleaseAll();

	CScene::ReleaseAll();
}

void CModeResult::Update()
{
	CInputKeyboard *inputKeyboard;
	CInputMouse *inputMouse;
	float mouseX, mouseY, mouseZ;

	// �L�[�{�[�h�擾
	inputKeyboard = CManager::GetInputKeyboard();

	// �}�E�X�擾
	inputMouse = CManager::GetInputMouse();
	mouseX = (float)inputMouse->GetAxisX();
	mouseY = (float)inputMouse->GetAxisY();
	mouseZ = (float)inputMouse->GetAxisZ();

	CScene::UpdateAll();

	if (inputMouse->GetLeftTrigger() || inputKeyboard->GetKeyTrigger(DIK_SPACE))
	{
		CManager::SetMode(new CModeTitle());
	}

}

void CModeResult::Draw()
{
	CScene::DrawAll();
}
