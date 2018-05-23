//=============================================================================
// ���͏��� [input.h]
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include<windows.h>
#define DIRECTINPUT_VERSION (0x0800)		//dinput.h���O�ɏ���
#include <dinput.h>

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);									//update�̍ŏ��ɌĂ�

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);							//�������u��
bool GetKeyboardRepeat(int nKey);							//�������u�ԂƂ��̌㉟�����ςȂ�擾����
bool GetKeyboardRelease(int nKey);							//�������u��

#endif