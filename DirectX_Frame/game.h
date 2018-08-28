//======================================================================
//	ƒQ[ƒ€‰æ–Ê[game.h]
//
//======================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "mode.h"

static const int ENEMY_NUM = 8;

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
	static void IncrementNumKill() { m_NumKill++; }
	static void IncrenentNumSneak() { m_NumSneak++; }

	static void test(float test);

private:
	static CBillBoard* tree1;
	static CBillBoard* tree2;
	static CPlayer* player;
	static CEnemy* enemy[ENEMY_NUM];
	static CEnemy* Target;
	static CLight *m_Light;
	static bool m_PlayerDied;
	static bool m_TargetDied;
	static CScene2D* Load;
	static CScene2D* LoadFrame;
	static CScene2D* LoadGage;
	static int m_NumKill;
	static int m_NumSneak;
};

#endif // !_GAME_H_
