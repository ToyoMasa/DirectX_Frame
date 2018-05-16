#ifndef _SCENE_H_

class CScene
{
protected:
	D3DXVECTOR3 m_Pos;
public:
	CScene();
	virtual ~CScene() {}
	virtual void Init() {}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void Set(D3DXVECTOR3& pos);
	void Release();
	static void UpdateAll();
	static void DrawAll();
	static void ReleaseAll();
	static CScene *m_Scene[10];
private:
};

#endif // !_SCENE_H_
