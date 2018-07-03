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

};

#endif // !_TITLE_H_
