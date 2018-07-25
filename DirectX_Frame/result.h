//======================================================================
//	‰æ–Ê‘JˆÚ‚ÌŠî’êƒNƒ‰ƒX[mode.h]
//
//======================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "mode.h"

class CModeResult : public CMode
{
public:
	CModeResult() : CMode() {}
	~CModeResult() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	static CScene2D* m_ResultText;
};

#endif // !_RESULT_H_
