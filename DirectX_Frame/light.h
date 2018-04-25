//======================================================================
//	ライティング処理[Light.h]
//
//======================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

void LightInit(void);
void LightUninit(void);
void LightUpdate(void);
void LightSet(void);

class CLight
{
public:
	CLight();
	~CLight();

	void Init(int id);
	void Uninit();
	void SetLight();

private:
	D3DLIGHT9 m_Light;
	int	m_LightID;
};

#endif // !_LIGHT_H_
