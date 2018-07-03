//======================================================================
//	ゲーム管理ヘッダ[manager]
//
//======================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

class CInputKeyboard;
class CInputMouse;
class CCamera;
class CLight;
class CMode;

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
	static void SetMode(CMode* mode);

private:
	static CInputKeyboard *m_InputKeyboard;	// キーボードへのポインタ
	static CInputMouse *m_InputMouse;		// マウスへのポインタ
	static CLight		*m_Light;
	static CMode *m_Mode;
};

#endif // !_MANAGER_H_
