//======================================================================
//	‰æ–Ê‘JˆÚ‚ÌŠî’êƒNƒ‰ƒX[mode.h]
//
//======================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "mode.h"

class CModeTitle : public CMode
{
public:
	CModeTitle() {}
	~CModeTitle() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	static CScene2D* m_TitleLogo;
};

#endif // !_TITLE_H_
