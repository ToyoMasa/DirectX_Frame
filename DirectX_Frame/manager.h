//======================================================================
//	�Q�[���Ǘ��w�b�_[manager]
//
//======================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

class CManager
{
public:
	CManager() {}
	~CManager() {}

	static bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void Uninit();
	static void Update();
	static void Draw();

private:
	static CCamera		*m_Camera;
	static CLight		*m_Light;
};

#endif // !_MANAGER_H_
