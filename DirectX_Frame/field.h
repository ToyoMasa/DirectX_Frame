#ifndef _FIELD_H_
#define _FIELD_H_

class CField : public CScene
{
public:
	CField::CField(int priority) : CScene(priority)
	{
		m_Vertex = NULL;
		m_Index = NULL;
		m_MeshSize = 1.0f;
		m_SizeX = 1;
		m_SizeY = 1;
		m_TextureID = 0;
		m_NumPrimitive = 0;
		m_NumVertex = 0;
		m_NumIndex = 0;
	}
	~CField(){}

	void Init(int texId, float meshSize, int sizeX, int sizeY);
	void Uninit();
	void Update();
	void Draw();
	static CField* Create(int texId, float meshSize, int sizeX, int sizeY);

private:
	VERTEX_3D *m_Vertex;
	WORD *m_Index;
	float m_MeshSize;
	int m_SizeX;
	int m_SizeY;
	int m_TextureID;
	int m_NumPrimitive;
	int m_NumVertex;
	int m_NumIndex;
};

#endif // !_FIELD_H_
