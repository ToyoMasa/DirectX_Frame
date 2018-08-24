//======================================================================
//	ƒQ[ƒ€‰æ–Ê[game.h]
//
//======================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "mode.h"

class CModeGame : public CMode
{
public:
	CModeGame() : CMode() {}
	~CModeGame() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	static CPlayer* GetPlayer() { return player; }
	static void PlayerDied() { m_PlayerDied = true; }
	static void TargetKilled();
	static CCamera* GetCamera() { return player->GetCamera(); }
	static void MakeMap();

	static void test(float test);

private:
	static CBillBoard* tree1;
	static CBillBoard* tree2;
	static CPlayer* player;
	static CEnemy* enemy[2];
	static CEnemy* Target;
	static CLight *m_Light;
	static bool m_PlayerDied;
	static bool m_TargetDied;
	static CScene2D* Load;
	static CScene2D* LoadFrame;
	static CScene2D* LoadGage;

};

#endif // !_GAME_H_
