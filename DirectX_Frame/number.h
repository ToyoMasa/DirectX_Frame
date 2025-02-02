//======================================================================
//	数字描画処理ヘッダ[number.h]
//
//======================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#define NUMBER_WIDTH (90)
#define NUMBER_HEIGHT (140)
#define NUMBER2_WIDTH (128)
#define NUMBER2_HEIGHT (137)

class CNumber
{
public:
	CNumber() {}
	~CNumber() {}

	static void Init();
	static void Uninit();
	static void Draw(int n, float x, float y);

private:
	static CScene2D *m_Scene2D;
};

// 1桁の数字描画
void DrawNumber(int n, float x, float y, float width, float height, D3DCOLOR color);
// 2桁以上の数字描画	(xは描画する時の中心座標)
void DrawNumbers(int n, float x, float y, float width, float height, D3DCOLOR color);

void DrawScore(int score, int fig, float x, float y, float width, float height, D3DCOLOR color);

// フォント違い
void DrawNumber2(int n, float x, float y, float width, float height, D3DCOLOR color);
void DrawNumbers2(int n, float x, float y, float width, float height, D3DCOLOR color);
void DrawScore2(int score, int fig, float x, float y, float width, float height, D3DCOLOR color);

#endif // !_NUMBER_H_
