#ifndef _SCENE_H_
#define _SCENE_H_

static const int OBJECT_MAX = 100;
static const int PRIORITY_MAX = 3;

class CScene
{
protected:
	D3DXVECTOR3 m_Pos;
public:
	CScene(int priority);
	virtual ~CScene() {}
	virtual void Init() {}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SetWorld(D3DXMATRIX move) {}
	virtual void Move(D3DXVECTOR3 pos) {}
	virtual void Rotate(D3DXVECTOR3 rot) {}
	virtual void Scale(D3DXVECTOR3 scale) {}
	void Set(D3DXVECTOR3& pos);
	void Release();
	static void UpdateAll();
	static void DrawAll();
	static void ReleaseAll();
	static CScene* GetScene(int priority, int id) { return m_Scene[priority][id]; }
private:
	static CScene *m_Scene[PRIORITY_MAX][OBJECT_MAX];
};

#endif // !_SCENE_H_
