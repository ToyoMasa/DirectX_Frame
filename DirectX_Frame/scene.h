#ifndef _SCENE_H_

class CScene
{
protected:
	D3DXVECTOR3 m_Pos;
public:
	virtual ~CScene() {}
	virtual void Init() {}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void Set(D3DXVECTOR3& pos);
	void Release();
private:

};

#endif // !_SCENE_H_
