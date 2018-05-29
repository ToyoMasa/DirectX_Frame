//======================================================================
//	�Q�[���Ǘ��w�b�_[manager]
//
//======================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

class CInputKeyboard;
class CInputMouse;
class CCamera;
class CLight;

class CManager
{
public:
	CManager() {}
	~CManager() {}

	static bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void Uninit();
	static void Update();
	static void Draw();

	static CInputKeyboard *GetInputKeyboard(void) { return m_InputKeyboard; }
	static CInputMouse *GetInputMouse(void) { return m_InputMouse; }

private:
	static CInputKeyboard *m_InputKeyboard;	// �L�[�{�[�h�ւ̃|�C���^
	static CInputMouse *m_InputMouse;			// �}�E�X�ւ̃|�C���^
	static CCamera		*m_Camera;
	static CLight		*m_Light;
};

#endif // !_MANAGER_H_
