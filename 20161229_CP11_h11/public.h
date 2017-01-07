#ifndef __PUBLIC_H
#define __PUBLIC_H
// --------------------
// 標準ライブラリ
// --------------------
#include	<stdio.h>
#include	<math.h>
#include	<stdlib.h>
#include	<string.h>
#pragma warning(disable:4996)
// --------------------
// マクロ定義
// --------------------
#define MAX_NUMBER_OF_JOBS			(6)		// 職業の数
#define MAX_NUMBER_OF_CHARACTERS	(4)		// キャラクター人数
#define MAX_CHARACTERS_OF_JOB_NAME	(4 * 2)	// 職業最大文字数(全角４文字）
#define MAX_CHARACTERS_OF_HERO_NAME	(4 * 2)	// キャラ最大文字数(全角４文字）
#define SIZE_OF_BORDER				(2)		// 罫線の大きさ
#define	SIZE_OF_NULL				(1)		// ヌル文字の大きさ
#define	SIZE_OF_HANKAKU_CHARACTER	(1)		// 半角文字の大きさ
#define	SIZE_OF_ZENAKU_CHARACTER	(2)		// 全角文字の大きさ
#define MAX_WIDTH_OF_WINDOW			(80)	// ウインドウ幅
#define MAX_HEIGHT_OF_WINDOW		(25)	// ウインドウ高さ
#define START_FROM_FIRST			(1)		// 順番（最初から）
#define START_FROM_LAST				(-1)	// 順番（最後から）
// --------------------
// 構造体定義
// --------------------
typedef struct _tPoint2D	// ２次元座標構造体
{
	int	x;					// X座標
	int	y;					// Y座標
} tPoint2D;
typedef struct _tArea		// 領域構造体
{
	tPoint2D start;			// 領域開始位置（左上）
	tPoint2D end;			// 領域終了位置（右下）
} tArea;

typedef struct _tString						// 文字列リスト
{
	// --------------------
	// 基本情報
	// --------------------
	char	szText[MAX_WIDTH_OF_WINDOW
					+ SIZE_OF_NULL];		// 文字列
	// --------------------
	// リスト構造
	// --------------------
	struct _tString*	prev;				// 前のtString
	struct _tString*	next;				// 次のtString

} tString;

typedef struct _tJob							// 職業構造体
{
	// --------------------
	// 基本情報
	// --------------------
	int		nCode;								// 職業識別コード
	char	szName[MAX_CHARACTERS_OF_JOB_NAME
					+ SIZE_OF_NULL];			// 職業名
	// --------------------
	// パラメータ補正 (1 ～ 5)
	// --------------------
	int		nHP;								// HP補正
	int		nSP;								// SP補正
	int		nAtk;								// こうげき補正
	int		nDef;								// ぼうぎょ補正
	int		nMAtk;								// まほこう補正
	int		nMDef;								// まほぼう補正
	int		nSpd;								// すばやさ補正
	// --------------------
	// リスト構造
	// --------------------
	struct _tJob* prev;							// 前のtJob
	struct _tJob* next;							// 次のtJob
} tJob;

typedef struct _tCharacter							// キャラクター構造体
{
	// --------------------
	// 基本情報
	// --------------------
	char		szName[MAX_CHARACTERS_OF_HERO_NAME
						+ SIZE_OF_NULL];			// 名前
	tJob		job;								// 職業
	// --------------------
	// ステータス基準値（パラメータふり）
	// --------------------
	int		nHP_Base;								// HP
	int		nSP_Base;								// SP
	int		nAtk_Base;								// こうげき
	int		nDef_Base;								// ぼうぎょ
	int		nMAtk_Base;								// まほこう
	int		nMDef_Base;								// まほぼう
	int		nSpd_Base;								// すばやさ
	// --------------------
	// ステータス実数値
	// --------------------
	int		nHP;									// HP
	int		nSP;									// SP
	int		nAtk;									// こうげき
	int		nDef;									// ぼうぎょ
	int		nMAtk;									// まほこう
	int		nMDef;									// まほぼう
	int		nSpd;									// すばやさ
	// --------------------
	// リスト構造
	// --------------------
	struct _tCharacter* prev;						// 前のtCharacter
	struct _tCharacter* next;						// 次のtCharacter
} tCharacter;

// ---------------------------
// プロトタイプ関数宣言
// ---------------------------
// 初期化：tJob
// init_tJob.cpp
void	InitJobs(tJob*);												// 職業情報を初期化
tJob	getJobByCode(int, const tJob*);									// 職業識別コードから、職業情報を取得

// 初期化:tCharacter
// init_tCharacter.cpp
void	InitMainCharacter(tCharacter*, const tJob*, int*);				// 主人公情報を初期化
void	InitBuiltInCharacters(tCharacter*, const tJob*, int*);			// 組み込みキャラを初期化
void	CalculateCharacterStatus(tCharacter*);							// ステータスを計算
int		CalculateIndivisualStatus(int, int, int);						// 各ステータスを計算

// リスト構造：tJob
// list_tJob.cpp
tJob*	JobList_New();													// JobListを新規作成
tJob*	JobList_Add(tJob*, bool);										// JobListに追加（true:最後尾に追加 false:直後に追加)
void	JobList_Delete(tJob*);											// JobList一件削除
void	JobList_DeleteAll(tJob*);										// JobList全削除

// リスト構造：tCharacter
// list_tCharacter.cpp
tCharacter*	CharacterList_New(int*);									// CharacterListを新規作成
tCharacter*	CharacterList_Add(tCharacter*, int*, bool);					// CharacterListに追加（true:最後尾に追加 false:直後に追加)
void		CharacterList_Delete(tCharacter*);							// CharacterList一件削除
void		CharacterList_DeleteAll(tCharacter*);						// CharacterList全削除

// リスト構造：tString
// list_tString.cpp
tString*	StringList_New_Blank();
tString*	StringList_New(const char* pChar);
tString*	StringList_Add_Blank(tString*, bool);
tString*	StringList_Add(tString* pStr, const char* pChar, bool isAddToLast);
void		StringList_Delete(tString*);
void		StringList_DeleteAll(tString*);
tString*	StringList_First(tString*);
tString*	StringList_Last(tString*);
tString*	StringList_Reverse(tString* pStr);


// 入力補助
// helper_input.cpp
int		InputInteger(int*, unsigned int, unsigned int, int, int, bool);	// 整数を変数に入力
int		InputInteger_pt(unsigned int min, unsigned int max, tPoint2D* ptStart, bool isMinMaxShowed);
void	InputString(char[], int, int, int);								// 文字列を変数に入力
void	InputJob(tCharacter*, const tJob*, int, int);					// 職業を選択し、変数に入力
void	Trim_And_Copy_String(char*, const char*, int);
void	Copy_String_From_Certain(char*, const char*, int, int);


// 表示補助
// helper_display.cpp
void	gotoxy_pt(tPoint2D point);
void	ClearArea(const tArea*);
tArea	DrawBorderWindow(tPoint2D*, bool, const size_t, const size_t);	//
tArea	Area_Inside_BorderWindow(const tArea*);
void DrawTextList_Plain(tArea AreaDisp, tString* pTextList, tPoint2D* ptCur_Draw);
int		DisplayStatusHeader(int, int);							
tPoint2D*	DisplayStatusHeader_PT(tPoint2D* ptStart);					//
int		DisplayStatusBlank(int, int, bool);								//
tPoint2D*	DisplayStatusBlank_pt(tPoint2D* ptStart, bool isLast);
void	DisplayJobList(const tJob*, int, int, int*, int*);				// 
int		ResizeStringLine(tString* pStrLine, int nMaxLen);
tString* ResizeStringList(tString* , tString* , int, int , int, int);
tString* ResizeStringList_By_tArea(tString* pDest, tString* pSource, tArea area, int order, int nStart);
void ShowTextinWindow(tString* pMessageList, tArea area);

// メニューシーン
// scene0_menu.cpp
void	Execute_MenuScene(int*);										// メニューシーン_シーン実行

// キャラクター作成シーン
// scene1_create.cpp
void	Execute_CreateScene(tCharacter*, const tCharacter*,
							const tJob*, int*, int);					// キャラクター作成シーン_シーン実行

// キャラクター更新シーン
// scene2_update_member.cpp
void	Execute_UpdateMemberScene(tCharacter*, const tJob*, int);

// キャラクター削除シーン
// scene3_delete_member.cpp
void	Execute_DeleteMemberScene(tCharacter*, int*);

// キャラクター表示シーン
// scene4_display_member.cpp
void	Execute_ShowMemberScene(const tCharacter*);


#endif	//__PUBLIC_H