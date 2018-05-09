#include "common.h"

void CScene::Set(D3DXVECTOR3& pos)
{
	m_Pos = pos;
}

void CScene::Release()
{
	Uninit();
	delete this;
}
