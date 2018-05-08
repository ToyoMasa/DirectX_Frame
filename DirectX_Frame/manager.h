//======================================================================
//	ÉQÅ[ÉÄä«óùÉwÉbÉ_[manager]
//
//======================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "scene2D.h"
#include "scene3D.h"
#include "sceneModel.h"
#include "camera.h"
#include "light.h"

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
	static CScene2D *m_Scene2D;
	static CScene3D *m_Scene3D;
	static CSceneModel *m_Model;
	static CCamera *m_Camera;
	static CLight *m_Light;
};

#endif // !_MANAGER_H_
