/**
* @file	conioex.h
* @brief	Win32 コンソール I/O 拡張ヘッダ for Visual C++/Borland C++
*
* @author	HAL名古屋 教務部　浜谷浩彦
* @date	2009/10/08 (木)
* @date	2009/10/15 (木) msleep 関数を追加。
* @date	2010/01/13 (水) playsound 関数で、常に先頭へシーク。
* @version	1.02
*
* @author	HAL名古屋 GP51A176-02 No.65028 花井遊矢
* @date	2016/12/29 (木)  conioex.hとconioex.cppに分割。インクルードガードでは重複定義してしまう変数/関数実装部を分割。
* @date	2016/12/29 (木)  __inline キーワードをstatic inlineキーワードに変更。 動作確認：Visual C++ 2013のみ。
* @date	2016/12/29 (木) 【リファクタリング】 次のインクルードガードを削除：COLORS, CONIOEX_INST, CONIOEX
* @version	1.02_01		(branched from version 1.02)
*/
#ifndef __CONIOEX_H
#define __CONIOEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#pragma comment(lib, "winmm.lib")


#ifdef __BORLANDC__
#define NOCURSOR		_NOCURSOR
#define SOLIDCURSOR		_SOLIDCURSOR
#define NORMALCURSOR	_NORMALCURSOR
__inline void setcursortype(int cur_t) {_setcursortype(cur_t);}
__inline int _kbhit(void) {return kbhit();}
#else /* !__BORLANDC__ */

#pragma warning(disable:4996)

#define NOCURSOR		0
#define SOLIDCURSOR		1
#define NORMALCURSOR	2

#define _NOCURSOR		NOCURSOR
#define _SOLIDCURSOR	SOLIDCURSOR
#define _NORMALCURSOR	NORMALCURSOR

enum COLORS {
	BLACK,			/* 黒		*/
	BLUE,			/* 濃い青	*/
	GREEN,			/* 緑		*/
	CYAN,			/* 青緑		*/
	RED,			/* 濃い赤	*/
	MAGENTA,		/* 紫		*/
	BROWN,			/* 濃い黄	*/
	LIGHTGRAY,		/* 25%灰色	*/
	DARKGRAY,		/* 50%灰色	*/
	LIGHTBLUE,		/* 青		*/
	LIGHTGREEN,		/* 明るい緑	*/
	LIGHTCYAN,		/* 水色		*/
	LIGHTRED,		/* 赤		*/
	LIGHTMAGENTA,	/* ピンク	*/
	YELLOW,			/* 黄		*/
	WHITE			/* 白		*/
};

/**
 * @brief	水平方向のカーソル位置を取得
 *
 * @return	現在のカーソル位置のX座標(1～)
 */
int wherex(void);
/**
 * @brief	垂直方向のカーソル位置を取得
 *
 * @return	現在のカーソル位置のY座標(1～)
 */
int wherey(void);
/**
 * @brief	カーソル位置の移動
 *
 * @param	x [入力] X座標(1～)
 * @param	y [入力] Y座標(1～)
 */
void gotoxy(int x, int y);
/**
 * @brief	行末まで消去
 */
void clreol(void);
/**
 * @brief	画面消去
 */
void clrscr(void);
/**
 * @brief	文字色高輝度化
 */
void highvideo(void);
/**
 * @brief	文字色低輝度化
 */
void lowvideo(void);

/**
 * @brief	既定文字色設定
 */
void normvideo(void);

void textbackground(int newcolor);
void textcolor(int newcolor);
void textattr(int newattr);

void setcursortype(int cur_t);
static inline void _setcursortype(int cur_t) {setcursortype(cur_t);}
/**
 * @brief	現在行に挿入
 */
void insline(void);
/**
 * @brief	現在行の削除
 */
void delline(void);

#endif /* __BORLANDC__ */

static inline void setcaption(char *title) { SetConsoleTitleA(title); }
static inline int getcaption(char *title, int len) { return GetConsoleTitleA(title, len); }
static inline void msleep(unsigned long msecs) { Sleep(msecs); }

/**
* @brief	キー情報　定数マクロ
*/
#define PK_ENTER				VK_RETURN
#define PK_ESC					VK_ESCAPE
#define PK_F1					VK_F1
#define PK_F2					VK_F2
#define PK_F3					VK_F3
#define PK_F4					VK_F4
#define PK_F5					VK_F5
#define PK_F6					VK_F6
#define PK_F7					VK_F7
#define PK_F8					VK_F8
#define PK_F9					VK_F9
#define PK_F10					VK_F10
#define PK_F11					VK_F11
#define PK_F12					VK_F12
#define PK_SP					VK_SPACE
#define PK_UP					VK_UP
#define PK_DOWN					VK_DOWN
#define PK_RIGHT				VK_RIGHT
#define PK_LEFT					VK_LEFT
#define PK_SHIFT				VK_SHIFT
#define PK_CTRL					VK_CONTROL
#define PK_ALT					VK_MENU
#define PK_BS					VK_BACK
#define PK_PAUSE				VK_PAUSE
#define PK_INS					VK_INSERT
#define PK_DEL					VK_DELETE
#define PK_TAB					VK_TAB
#define PK_NFER					VK_KANA		/* [無変換]	*/
#define PK_XFER					VK_CONVERT	/* [変換]	*/
#define PK_0					0x30
#define PK_1					0x31
#define PK_2					0x32
#define PK_3					0x33
#define PK_4					0x34
#define PK_5					0x35
#define PK_6					0x36
#define PK_7					0x37
#define PK_8					0x38
#define PK_9					0x39
#define PK_NUMPAD0				VK_NUMPAD0	/* テンキーの[0]	*/
#define PK_NUMPAD1				VK_NUMPAD1	/* テンキーの[1]	*/
#define PK_NUMPAD2				VK_NUMPAD2	/* テンキーの[2]	*/
#define PK_NUMPAD3				VK_NUMPAD3	/* テンキーの[3]	*/
#define PK_NUMPAD4				VK_NUMPAD4	/* テンキーの[4]	*/
#define PK_NUMPAD5				VK_NUMPAD5	/* テンキーの[5]	*/
#define PK_NUMPAD6				VK_NUMPAD6	/* テンキーの[6]	*/
#define PK_NUMPAD7				VK_NUMPAD7	/* テンキーの[7]	*/
#define PK_NUMPAD8				VK_NUMPAD8	/* テンキーの[8]	*/
#define PK_NUMPAD9				VK_NUMPAD9	/* テンキーの[9]	*/
#define PK_A					0x41
#define PK_B					0x42
#define PK_C					0x43
#define PK_D					0x44
#define PK_E					0x45
#define PK_F					0x46
#define PK_G					0x47
#define PK_H					0x48
#define PK_I					0x49
#define PK_J					0x4A
#define PK_K					0x4B
#define PK_L					0x4C
#define PK_M					0x4D
#define PK_N					0x4E
#define PK_O					0x4F
#define PK_P					0x50
#define PK_Q					0x51
#define PK_R					0x52
#define PK_S					0x53
#define PK_T					0x54
#define PK_U					0x55
#define PK_V					0x56
#define PK_W					0x57
#define PK_X					0x58
#define PK_Y					0x59
#define PK_Z					0x5A

#define PK_LT					0x0BC		/* [,]	*/
#define PK_GT					0x0BE		/* [.]	*/
#define PK_SLUSH				0x0BF		/* [?]	*/
#define PK_DOT					VK_DECIMAL	/* テンキーの[.]	*/
#define PK_DIV					VK_DIVIDE	/* テンキーの[/]	*/
#define PK_BSLUSH				0x0E2		/* [_]	*/

#define PK_SEMICOLON			0x0BB		/* [;]	*/
#define PK_ADD					VK_ADD		/* テンキーの[+]	*/
#define PK_COLON				0x0BA		/* [:]	*/
#define PK_MUL					VK_MULTIPLY	/* テンキーの[*]	*/
#define PK_RBRACE				0x0DD		/* []]	*/

#define PK_ATMARK				0x0C0		/* [@]	*/
#define PK_LBRACE				0x0DB		/* [[]	*/

#define PK_MINUS				0x0BD		/* [-]	*/
#define PK_SUB					VK_SUBTRACT	/* テンキーの[-]	*/
#define PK_XOR					0x0DE		/* [^]	*/
#define PK_YEN					0x0DC		/* [\]	*/

#define PK_KANJI				0x0F3		/* [半角/全角]	*/
#define PK_CAPS					0x0F0		/* [英数][ひらがな]	*/

#define PM_LEFT					VK_LBUTTON
#define PM_MID					VK_MBUTTON
#define PM_RIGHT				VK_RBUTTON
#define PM_CURX					0x0101
#define PM_CURY					0x0102

#define PJ1_XPOS				0x0200
#define PJ1_YPOS				0x0201
#define PJ1_ZPOS				0x0202
#define PJ1_BTNS				0x0203
#define PJ2_XPOS				0x0210
#define PJ2_YPOS				0x0211
#define PJ2_ZPOS				0x0212
#define PJ2_BTNS				0x0213
#define PJ3_XPOS				0x0220
#define PJ3_YPOS				0x0221
#define PJ3_ZPOS				0x0222
#define PJ3_BTNS				0x0223
#define PJ4_XPOS				0x0230
#define PJ4_YPOS				0x0231
#define PJ4_ZPOS				0x0232
#define PJ4_BTNS				0x0233
#define PJ_XPOS					PJ1_XPOS
#define PJ_YPOS					PJ1_YPOS
#define PJ_ZPOS					PJ1_ZPOS
#define PJ_BTNS					PJ1_BTNS

/**
* @brief	キー情報リセット
*
* @return	なし
*/
void reinport(void);

/**
 * @brief	各種リアルタイム入力
 *
 * @param	port [入力] ポート番号(P*_*)
 * @return	入力値
 */
int inport(int port);


/**
 * @brief	サウンド ファイルを開く
 *
 * @param	path [入力] ファイル名
 * @retval	非0	サウンド ハンドル
 * @retval	0	エラー
 */
int opensound(char *path);
/**
 * @brief	サウンド ファイルを閉じる
 *
 * @param	hsound [入力] サウンド ハンドル
 */
void closesound(int hsound);
/**
 * @brief	サウンドを再生する
 *
 * @param	hsound [入力] サウンド ハンドル
 * @param	repeat [入力] ループ有無
 */
void playsound(int hsound, int repeat);
/**
 * @brief	サウンド再生を停止する
 *
 * @param	hsound [入力] サウンド ハンドル
 */
void stopsound(int hsound);
/**
 * @brief	サウンド再生状態の取得
 *
 * @param	hsound [入力] サウンド ハンドル
 * @return	再生中ならば 0 以外を返す。
 */
int checksound(int hsound);
/**
 * @brief	ループ再生の強制更新
 *
 * @param	hsound [入力] サウンド ハンドル
 */
void updatesound(int hsound);

/**
 * @brief	再生音量を設定する
 *
 * @param	hsound [入力] サウンド ハンドル
 * @param	percent [入力] 音量 (0 ～ 100)
 */
void setvolume(int hsound, int percent);

#ifdef __cplusplus
}
#endif

#endif /* __CONIOEX_H */
