//=============================================================================
// 入力処理 [input.h]
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include<windows.h>
#define DIRECTINPUT_VERSION (0x0800)		//dinput.hより前に書く
#include <dinput.h>

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);									//updateの最初に呼ぶ

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);							//押した瞬間
bool GetKeyboardRepeat(int nKey);							//押した瞬間とその後押しっぱなら取得する
bool GetKeyboardRelease(int nKey);							//離した瞬間

#endif