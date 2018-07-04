//======================================================================
//	ÉQÅ[ÉÄâÊñ [game.h]
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
	static CBillBoard* tree1;
	static CBillBoard* tree2;
	static CPlayer* player;
	static CEnemy* enemy;
	static CLight *m_Light;

};

#endif // !_GAME_H_
