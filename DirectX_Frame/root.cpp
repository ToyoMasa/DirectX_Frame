#include "common.h"
#include "root.h"

D3DXVECTOR3 CRoot::m_RootPos[100];
int CRoot::m_NextRoot[100];

void CRoot::Set()
{
	m_RootPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RootPos[1] = D3DXVECTOR3(5.0f, 0.0f, 5.0f);
	m_RootPos[2] = D3DXVECTOR3(-5.0f, 0.0f, 5.0f);
	m_RootPos[3] = D3DXVECTOR3(-5.0f, 0.0f, -5.0f);
	m_RootPos[4] = D3DXVECTOR3(5.0f, 0.0f, -5.0f);

	m_NextRoot[0] = 1;
	m_NextRoot[1] = 2;
	m_NextRoot[2] = 3;
	m_NextRoot[3] = 4;
	m_NextRoot[4] = 1;
}
