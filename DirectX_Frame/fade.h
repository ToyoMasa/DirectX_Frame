//======================================================================
//	�t�F�[�h���[fade.h]
//
//======================================================================
#ifndef _FADE_H_
#define _FADE_H_

class CFade
{
public:
	CFade() {}
	~CFade() {}

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static bool GetFade() { return m_FadeIn | m_FadeOut; }

	static void FadeIn();
	static void FadeOut();

private:
	static D3DXVECTOR2 m_TexSize;
	static int m_Alpha;
	static int m_TexId;
	static bool m_FadeIn;
	static bool m_FadeOut;
};

#endif // !_FADE_H_

