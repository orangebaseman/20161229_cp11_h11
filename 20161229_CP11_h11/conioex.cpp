/**
* @file	conioex.h
* @brief	Win32 �R���\�[�� I/O �g���w�b�_ for Visual C++/Borland C++
*
* @author	HAL���É� �������@�l�J�_�F
* @date	2009/10/08 (��)
* @date	2009/10/15 (��) msleep �֐���ǉ��B
* @date	2010/01/13 (��) playsound �֐��ŁA��ɐ擪�փV�[�N�B
* @version	1.02
*
* @author	HAL���É� GP51A176-02 No.65028 �Ԉ�V��
* @date	2016/12/29 (��)  conioex.h��conioex.cpp�ɕ����B�C���N���[�h�K�[�h�ł͏d����`���Ă��܂��ϐ�/�֐��������𕪊��B
* @date	2016/12/29 (��)  __inline �L�[���[�h��static inline�L�[���[�h�ɕύX�B ����m�F�FVisual C++ 2013�̂݁B
* @date	2016/12/29 (��) �y���t�@�N�^�����O�z ���̃C���N���[�h�K�[�h���폜�FCOLORS, CONIOEX_INST, CONIOEX
* @version	1.02_01		(branched from version 1.02)
*/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __BORLANDC__
	static inline void setcursortype(int cur_t) { _setcursortype(cur_t); }
	static inline int _kbhit(void) { return kbhit(); }
#else /* !__BORLANDC__ */
#endif

#include	"conioex.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <process.h>
#include <tchar.h>
#include <mmsystem.h>
#include <digitalv.h>

WORD	__conioex_h_wAttribute = LIGHTGRAY;	/* ���E�F */
/**
* @brief	���������̃J�[�\���ʒu���擾
*
* @return	���݂̃J�[�\���ʒu��X���W(1�`)
*/
int wherex(void)

{
	CONSOLE_SCREEN_BUFFER_INFO	csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X - csbi.srWindow.Left + 1;
}
/**
* @brief	���������̃J�[�\���ʒu���擾
*
* @return	���݂̃J�[�\���ʒu��Y���W(1�`)
*/
int wherey(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y - csbi.srWindow.Top + 1;
}
/**
* @brief	�J�[�\���ʒu�̈ړ�
*
* @param	x [����] X���W(1�`)
* @param	y [����] Y���W(1�`)
*/
void gotoxy(int x, int y)
{
	COORD c;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	c.X = x - 1;
	c.Y = y - 1;
	if (GetConsoleScreenBufferInfo(h, &csbi))
		c.Y += csbi.srWindow.Top;
	SetConsoleCursorPosition(h, c);
}
/**
* @brief	�s���܂ŏ���
*/
void clreol(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	COORD	c;
	HANDLE	h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi)) {
		DWORD num;

		c = csbi.dwCursorPosition;
		FillConsoleOutputAttribute(h, csbi.wAttributes,
			csbi.srWindow.Right - csbi.dwCursorPosition.X + 1, c, &num);
		FillConsoleOutputCharacter(h, ' ',
			csbi.srWindow.Right - csbi.dwCursorPosition.X + 1, c, &num);
	}
}
/**
* @brief	��ʏ���
*/
void clrscr(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD num;
	COORD c = { 0, 0 };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi)) {
		__conioex_h_wAttribute = csbi.wAttributes;
		FillConsoleOutputAttribute(h, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, c, &num);
		FillConsoleOutputCharacter(h, TEXT(' '), csbi.dwSize.X * csbi.dwSize.Y, c, &num);
		gotoxy(csbi.srWindow.Left + 1, csbi.srWindow.Top + 1);
	}
}
/**
* @brief	�����F���P�x��
*/
void highvideo(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi))
		SetConsoleTextAttribute(h, csbi.wAttributes | FOREGROUND_INTENSITY);
}
/**
* @brief	�����F��P�x��
*/
void lowvideo(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi))
		SetConsoleTextAttribute(h, csbi.wAttributes & ~FOREGROUND_INTENSITY);
}
/**
* @brief	���蕶���F�ݒ�
*/
void normvideo(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGRAY);
}
void textbackground(int newcolor)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(h, &csbi))
		SetConsoleTextAttribute(h, (csbi.wAttributes & ~0x00f0) | ((newcolor & 0x07) << 4));
}
void textcolor(int newcolor)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(h, &csbi))
		SetConsoleTextAttribute(h, (csbi.wAttributes & ~0x0f) | (newcolor & 0x0f));
}
void textattr(int newattr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), newattr);
}
void setcursortype(int cur_t)
{
	CONSOLE_CURSOR_INFO	cci;
	static	int nSize = -1;

	if (nSize < 0) {
		if (GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci))
			nSize = (int)cci.dwSize;
		else
			nSize = 25;
	}
	cci.dwSize = (cur_t < NORMALCURSOR) ? 100 : nSize;
	cci.bVisible = (cur_t != NOCURSOR);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
/**
* @brief	���ݍs�ɑ}��
*/
void insline(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi)) {
		COORD	c;
		DWORD	len;
		DWORD	num;
		LPTSTR	psz;
		LPWORD	pw;

		c.X = csbi.srWindow.Left;
		len = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		psz = (LPTSTR)_alloca(len * sizeof(TCHAR));
		pw = (LPWORD)_alloca(len * sizeof(WORD));
		for (c.Y = csbi.srWindow.Bottom; c.Y > csbi.dwCursorPosition.Y; c.Y--) {
			c.Y--;
			ReadConsoleOutputAttribute(h, pw, len, c, &num);
			ReadConsoleOutputCharacter(h, psz, len, c, &num);
			c.Y++;
			WriteConsoleOutputAttribute(h, pw, len, c, &num);
			WriteConsoleOutputCharacter(h, psz, len, c, &num);
		}
		FillConsoleOutputAttribute(h, csbi.wAttributes, len, c, &num);
		FillConsoleOutputCharacter(h, TEXT(' '), len, c, &num);
	}
}
/**
* @brief	���ݍs�̍폜
*/
void delline(void){
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi)) {
		DWORD	num;
		COORD	c;
		DWORD	len;
		LPTSTR	psz;
		LPWORD	pw;

		c.X = csbi.srWindow.Left;
		len = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		psz = (LPTSTR)_alloca(len * sizeof(TCHAR));
		pw = (LPWORD)_alloca(len * sizeof(WORD));
		for (c.Y = csbi.dwCursorPosition.Y; c.Y < csbi.srWindow.Bottom; c.Y++) {
			c.Y++;
			ReadConsoleOutputAttribute(h, pw, len, c, &num);
			ReadConsoleOutputCharacter(h, psz, len, c, &num);
			c.Y--;
			WriteConsoleOutputAttribute(h, pw, len, c, &num);
			WriteConsoleOutputCharacter(h, psz, len, c, &num);
		}
		FillConsoleOutputAttribute(h, __conioex_h_wAttribute, len, c, &num);
		FillConsoleOutputCharacter(h, TEXT(' '), len, c, &num);
	}
}
/**
* @brief	�L�[�A�}�E�X���͏��z��
*/
DWORD	__conioex_h_dwKeyMap[8]	= { 0, 0, 0, 0, 0, 0, 0, 0 };
COORD	__conioex_h_crdMouse	= { 0, 0 };
/**
* @brief	�L�[��񃊃Z�b�g
*
* @return	�Ȃ�
*/
void reinport(void)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		__conioex_h_dwKeyMap[i] = 0;
	}
}
/**
* @brief	�e�탊�A���^�C������
*
* @param	port [����] �|�[�g�ԍ�(P*_*)
* @return	���͒l
*/
int inport(int port)
{
	DWORD	dwEvent;
	HANDLE	h;

	/* �Q�[���p�b�h���� */
	if ((port & 0xfe00) == 0x0200) {
		int		id = (port & 0x01f0) >> 4;
		int		func = port & 0x0f;
		JOYINFO	ji;

		switch (func) {
		case 0:	case 1:	case 2:	case 3:
			if (joyGetPos(id, &ji) != JOYERR_NOERROR)
				return -1;
			switch (func) {
			case 0:
				return ji.wXpos;
			case 1:
				return ji.wYpos;
			case 2:
				return ji.wZpos;
			case 3:
				return ji.wButtons;
			}
			break;
		default:
			break;
		}
		return 0;
	}
	/* �L�[/�}�E�X �C�x���g �`�F�b�N */
	dwEvent = 0;
	h = GetStdHandle(STD_INPUT_HANDLE);
	if (GetNumberOfConsoleInputEvents(h, &dwEvent) && dwEvent) {
		DWORD			dwRead = 0;
		PINPUT_RECORD	pInpRec = (PINPUT_RECORD)_alloca(dwEvent * sizeof(INPUT_RECORD));

		if (ReadConsoleInput(h, pInpRec, dwEvent, &dwRead) && dwRead) {
			PINPUT_RECORD	pir = pInpRec;
			DWORD			dw;
			for (dw = 0; dw < dwRead; dw++, pir++) {
				switch (pir->EventType) {
				case KEY_EVENT: {
					KEY_EVENT_RECORD*	pker = &pir->Event.KeyEvent;
					if (pker->wVirtualKeyCode > 0x0FF)
						break;
					if (pker->bKeyDown)
						__conioex_h_dwKeyMap[pker->wVirtualKeyCode >> 5] |= (0x01 << (pker->wVirtualKeyCode & 31));
					else
						__conioex_h_dwKeyMap[pker->wVirtualKeyCode >> 5] &= ~(0x01 << (pker->wVirtualKeyCode & 31));
					if (pker->dwControlKeyState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
						__conioex_h_dwKeyMap[VK_MENU >> 5] |= (0x01 << (VK_MENU & 31));
					else
						__conioex_h_dwKeyMap[VK_MENU >> 5] &= ~(0x01 << (VK_MENU & 31));
					if (pker->dwControlKeyState & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED))
						__conioex_h_dwKeyMap[VK_CONTROL >> 5] |= (0x01 << (VK_CONTROL & 31));
					else
						__conioex_h_dwKeyMap[VK_CONTROL >> 5] &= ~(0x01 << (VK_CONTROL & 31));
					if (pker->dwControlKeyState & SHIFT_PRESSED)
						__conioex_h_dwKeyMap[VK_SHIFT >> 5] |= (0x01 << (VK_SHIFT & 31));
					else
						__conioex_h_dwKeyMap[VK_SHIFT >> 5] &= ~(0x01 << (VK_SHIFT & 31));
					break;
				}
				case MOUSE_EVENT: {
					MOUSE_EVENT_RECORD	*pmer = &pir->Event.MouseEvent;
					__conioex_h_crdMouse = pmer->dwMousePosition;
					if (pmer->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						__conioex_h_dwKeyMap[VK_LBUTTON >> 5] |= (0x01 << (VK_LBUTTON & 31));
					else
						__conioex_h_dwKeyMap[VK_LBUTTON >> 5] &= ~(0x01 << (VK_LBUTTON & 31));
					if (pmer->dwButtonState & FROM_LEFT_2ND_BUTTON_PRESSED)
						__conioex_h_dwKeyMap[VK_MBUTTON >> 5] |= (0x01 << (VK_MBUTTON & 31));
					else
						__conioex_h_dwKeyMap[VK_MBUTTON >> 5] &= ~(0x01 << (VK_MBUTTON & 31));
					if (pmer->dwButtonState & RIGHTMOST_BUTTON_PRESSED)
						__conioex_h_dwKeyMap[VK_RBUTTON >> 5] |= (0x01 << (VK_RBUTTON & 31));
					else
						__conioex_h_dwKeyMap[VK_RBUTTON >> 5] &= ~(0x01 << (VK_RBUTTON & 31));
					break;
				}
				default:
					break;
				}
			}
		}
	}

	/* �}�E�X���W��Ԃ� */
	switch (port) {
	case PM_CURX:
		return __conioex_h_crdMouse.X + 1;
	case PM_CURY:
		return __conioex_h_crdMouse.Y + 1;
	default:
		break;
	}
	// �L�[��Ԃ�Ԃ�
	return (__conioex_h_dwKeyMap[(port & 0x0FF) >> 5] & (0x01 << (port & 31))) != 0;
}


/**
* @brief	�T�E���h ���\����
*/
typedef struct {
	int				nDevType;
	MCIDEVICEID		wDeviceID;
	char			szPath[MAX_PATH];
	int				nRepeat;
} __conioex_h_SoundInfo;
/**
* @brief	�T�E���h �t�@�C�����J��
*
* @param	path [����] �t�@�C����
* @retval	��0	�T�E���h �n���h��
* @retval	0	�G���[
*/
int opensound(char *path){
	const char	szMidiExt[] = ".mid|.midi|.rmi";
	const char	szWaveExt[] = ".wav|.wave";
	const char	szMP3Ext[] = ".mp3";
	char		szExt[_MAX_EXT];
	union {
		MCI_WAVE_OPEN_PARMSA	wop;
		MCI_OPEN_PARMSA			op;
	} m;
	DWORD		dwCmd;
	__conioex_h_SoundInfo	*psi;

	psi = (__conioex_h_SoundInfo *)malloc(sizeof(__conioex_h_SoundInfo));
	if (psi == NULL)
		return 0;
	ZeroMemory(psi, sizeof(*psi));

	ZeroMemory(&m, sizeof(m));
	_splitpath(path, NULL, NULL, NULL, szExt);
	strlwr(szExt);
	dwCmd = MCI_OPEN_TYPE | MCI_OPEN_ELEMENT;
	if (strstr(szMidiExt, szExt)) {
		psi->nDevType = MCI_DEVTYPE_SEQUENCER;
		lstrcpynA(psi->szPath, path, MAX_PATH);
		m.op.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_SEQUENCER;
		m.op.lpstrElementName = psi->szPath;
		dwCmd |= MCI_OPEN_TYPE_ID;
	}
	else if (strstr(szWaveExt, szExt)) {
		psi->nDevType = MCI_DEVTYPE_WAVEFORM_AUDIO;
		lstrcpynA(psi->szPath, path, MAX_PATH);
		m.wop.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
		m.wop.lpstrElementName = psi->szPath;
		dwCmd |= MCI_OPEN_TYPE_ID;
		//		m.wop.dwBufferSeconds  = 60;
		//		dwCmd |= MCI_WAVE_OPEN_BUFFER;
	}
	else if (strstr(szMP3Ext, szExt)) {
		psi->nDevType = MCI_DEVTYPE_DIGITAL_VIDEO;
		lstrcpynA(psi->szPath, path, MAX_PATH);
		m.op.lpstrDeviceType = "MPEGVideo";
		m.op.lpstrElementName = psi->szPath;
	}
	else {
		free(psi);
		return 0;
	}
	if (mciSendCommandA(0, MCI_OPEN, dwCmd, (DWORD)&m)) {
		free(psi);
		return 0;
	}
	psi->wDeviceID = m.op.wDeviceID;
	return (int)psi;
}
/**
* @brief	�T�E���h �t�@�C�������
*
* @param	hsound [����] �T�E���h �n���h��
*/
void closesound(int hsound)
{
	__conioex_h_SoundInfo	*psi;

	if (!hsound)
		return;
	psi = (__conioex_h_SoundInfo *)hsound;
	if (psi->wDeviceID) {
		mciSendCommand(psi->wDeviceID, MCI_CLOSE, 0, 0);
		psi->wDeviceID = 0;
	}
	free(psi);
}
/**
* @brief	�T�E���h���Đ�����
*
* @param	hsound [����] �T�E���h �n���h��
* @param	repeat [����] ���[�v�L��
*/
void playsound(int hsound, int repeat)
{
	__conioex_h_SoundInfo	*psi;
	DWORD					dwCmd;
	MCI_PLAY_PARMS			mpp;

	if (!hsound)
		return;
	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID)
		return;
	psi->nRepeat = repeat;
	ZeroMemory(&mpp, sizeof(mpp));
	dwCmd = 0;
	if (repeat) {
		switch (psi->nDevType) {
		case MCI_DEVTYPE_DIGITAL_VIDEO:
			dwCmd |= (MCI_FROM | MCI_DGV_PLAY_REPEAT);
			mpp.dwFrom = 0;
			break;
		case MCI_DEVTYPE_SEQUENCER:
		case MCI_DEVTYPE_WAVEFORM_AUDIO:
			break;
		default:
			break;
		}
	}
	mciSendCommand(psi->wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
	mciSendCommand(psi->wDeviceID, MCI_PLAY, dwCmd, (DWORD)&mpp);
}
/**
* @brief	�T�E���h�Đ����~����
*
* @param	hsound [����] �T�E���h �n���h��
*/
void stopsound(int hsound)
{
	__conioex_h_SoundInfo	*psi;

	if (!hsound)
		return;
	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID)
		return;
	psi->nRepeat = 0;
	mciSendCommand(psi->wDeviceID, MCI_STOP, MCI_WAIT, 0);
	mciSendCommand(psi->wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
}
/**
* @brief	�T�E���h�Đ���Ԃ̎擾
*
* @param	hsound [����] �T�E���h �n���h��
* @return	�Đ����Ȃ�� 0 �ȊO��Ԃ��B
*/
int checksound(int hsound)
{
	__conioex_h_SoundInfo	*psi;
	MCI_STATUS_PARMS		msp;

	if (!hsound)
		return 0;
	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID)
		return 0;
	ZeroMemory(&msp, sizeof(msp));
	msp.dwItem = MCI_STATUS_MODE;
	if (mciSendCommand(psi->wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&msp))
		return 0;
	return msp.dwReturn == MCI_MODE_PLAY;
}
/**
* @brief	���[�v�Đ��̋����X�V
*
* @param	hsound [����] �T�E���h �n���h��
*/
void updatesound(int hsound)
{
	__conioex_h_SoundInfo	*psi;
	MCI_STATUS_PARMS		msp;

	if (!hsound)
		return;
	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID || !psi->nRepeat)
		return;
	switch (psi->nDevType) {
	case MCI_DEVTYPE_DIGITAL_VIDEO:
		break;
	case MCI_DEVTYPE_SEQUENCER:
	case MCI_DEVTYPE_WAVEFORM_AUDIO:
		ZeroMemory(&msp, sizeof(msp));
		msp.dwItem = MCI_STATUS_MODE;
		if (!mciSendCommand(psi->wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&msp)) {
			if (msp.dwReturn != MCI_MODE_PLAY) {
				if (psi->nRepeat > 0) {
					psi->nRepeat = -1;
					mciSendCommand(psi->wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
					mciSendCommand(psi->wDeviceID, MCI_PLAY, 0, 0);
				}
			}
			else
				psi->nRepeat = 1;
		}
		break;
	default:
		break;
	}
}
/**
* @brief	�Đ����ʂ�ݒ肷��
*
* @param	hsound [����] �T�E���h �n���h��
* @param	percent [����] ���� (0 �` 100)
*/
void setvolume(int hsound, int percent)
{
	__conioex_h_SoundInfo	*psi;

	if (!hsound)
		return;
	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID)
		return;
	switch (psi->nDevType) {
	case MCI_DEVTYPE_DIGITAL_VIDEO: {
		MCI_DGV_SETAUDIO_PARMS	mdsp;

		ZeroMemory(&mdsp, sizeof(mdsp));
		mdsp.dwItem = MCI_DGV_SETAUDIO_VOLUME;
		mdsp.dwValue = percent * 10;
		mciSendCommand(psi->wDeviceID, MCI_SETAUDIO,
			MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)&mdsp);
		break;
	}
	case MCI_DEVTYPE_SEQUENCER: {
		DWORD dwVolume;

		dwVolume = 0x0ffff * percent / 100;
		midiOutSetVolume(0, (DWORD)MAKELONG(dwVolume, dwVolume));
		break;
	}
	case MCI_DEVTYPE_WAVEFORM_AUDIO: {
		DWORD dwVolume;

		dwVolume = 0x0ffff * percent / 100;
		waveOutSetVolume(0, (DWORD)MAKELONG(dwVolume, dwVolume));
		break;
	}
	default:
		break;
	}
}
#ifdef __cplusplus
}
#endif
