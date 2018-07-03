//======================================================================
//	‰æ–Ê‘JˆÚ‚ÌŠî’êƒNƒ‰ƒX[mode.h]
//
//======================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "mode.h"

class CModeGame : public CMode
{
public:
	CModeGame() {}
	~CModeGame() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:

};

#endif // !_GAME_H_
