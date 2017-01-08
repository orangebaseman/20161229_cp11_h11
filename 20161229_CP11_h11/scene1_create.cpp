// --------------------
// キャラクター作成シーン
// --------------------
#include	"conioex.h"
#include	"public.h"

// --------------------
// 疑似private関数宣言
// --------------------
int		DisplayMasterMessage_CreateScene(const int*, int*, int, int);					// キャラクター作成シーン_シーン実行
int		DisplayAndCreatePartyMember_CreateScene(tCharacter*, const tJob*, int, int);	// キャラクター作成シーン_表示（マスタメッセージ）
int		DisplayCantAddMessage_CreateScene(int, int);									// キャラクター作成シーン_


// --------------------
// 関数実装部
// --------------------
// 【関数内容】
// キャラクター作成シーン_シーン実行
// 【引数】
// pCharacterList		: 【変更対象】キャラクターリスト
// pBuiltInCharaList	: 【参照用　】組み込みキャラクターリスト
// pJobList				: 【参照用　】職業一覧
// pNum					: 【変更対象】キャラクター人数
// nNumBuiltIn			: 【参照用　】組み込みキャラクター人数
// 【戻り値】
// なし
void	Execute_CreateScene(tCharacter* pCharacterList, const tCharacter* pBuiltInCharaList, const tJob* pJobList, int* pNumMember, int nNumBuiltIn)
{
	// --------------------
	// ローカル変数宣言、初期化
	// --------------------
	int x, y = 2, tempY;				// 描画XY座標
	tPoint2D	ptCur_Draw = { 1, 1 };	// 描画現在位置
	tString*	pCur_Str;				// StringListの現在位置
	bool		isLast;
	int i;								// ループカウンタ
	int nAdd = 1;						// 作成（追加）人数
	tCharacter* pCh = pCharacterList;	// キャラクター構造体ポインタ
	// -------
	// マスタメッセージ部　変数
	// ------
	tPoint2D	ptStart_MessageMaster = { 1, 1 };			// 原点（左上）
	int			nLen_MessageMaster = MAX_WIDTH_OF_WINDOW;	// 長さ
	int			nLines_MessageMaster = 9;					// 行数
	tArea		AreaW_MessageMaster;						// Area(Window全体）
	tArea		AreaT_MessageMaster;						// Area(Text部分）
	tString*	pTextList_Master_MessageMaster;				// メッセージリスト(全体）
	tString*	pTextList_Display_MessageMaster;			// メッセージリスト（表示部分）
	pTextList_Display_MessageMaster = StringList_New_Blank();
	// -------
	// キャラクター作成部　変数
	// ------
	tPoint2D	ptStart_CharacterCreate_Head= { 1, 11 };						// 原点（左上）
	tPoint2D	ptStart_CharacterCreate_Chara[MAX_NUMBER_OF_CHARACTERS - 1];	// 原点（左上）
	for (i = 0; i < MAX_NUMBER_OF_CHARACTERS - 1; i++)
	{
		ptStart_CharacterCreate_Chara[i].x = ptStart_CharacterCreate_Head.x
			+ MAX_CHARACTERS_OF_HERO_NAME + SIZE_OF_BORDER
			+ i * (MAX_CHARACTERS_OF_HERO_NAME + SIZE_OF_BORDER);
		ptStart_CharacterCreate_Chara[i].y = ptStart_CharacterCreate_Head.y;
	}
	// -------
	// キャラクター作成補助部　変数
	// ------
	tPoint2D	ptStart_CharacterCreate_Sub;	//
	int			nLen_CharacterCreate_Sub;		//
	int			nLines_CharacterCreate_Sub;		// 行数
	tArea		AreaW_CharacterCreate_Sub;		// Area(Window全体）
	tArea		AreaT_CharacterCreate_Sub;		// Area(Text部分）

	// -------
	// 画面クリア
	// ------
	clrscr();
	// ※人数チェック:　上限人数ならばエラー表示をしてシーン終了
	if ((*pNumMember) >= MAX_NUMBER_OF_CHARACTERS)
	{
		DisplayCantAddMessage_CreateScene(2, 2);
		getchar();
		return;
	}
	// --------------------
	// マスタメッセージ　表示
	// --------------------
	// --------
	// 枠線の表示
	// --------
	// 描画現在位置を原点へ
	ptCur_Draw = ptStart_MessageMaster;	
	// 罫線ウインドウの表示
	AreaW_MessageMaster = DrawBorderWindow(&ptCur_Draw, true, nLen_MessageMaster, nLines_MessageMaster);
	// 文字描画範囲取得
	AreaT_MessageMaster = Area_Inside_BorderWindow(&AreaW_MessageMaster);
	// --------
	// メッセージの作成
	// --------
	pCur_Str = StringList_New("なかまを　およびに　なるのですね");					// 新規作成
	pCur_Str = StringList_Add(pCur_Str, "なんにん　およびに　なりますか？", true);	// 追加
	pTextList_Master_MessageMaster = StringList_First(pCur_Str);				// メッセージリスト（マスタ）に代入
	// メッセージリスト(表示用）に、メッセージサイズにリサイズして代入
	pTextList_Display_MessageMaster = 
		ResizeStringList_By_tArea(pTextList_Display_MessageMaster, pTextList_Master_MessageMaster, AreaT_MessageMaster, START_FROM_LAST, 1);
	// --------
	// メッセージの表示
	// --------
	DrawTextList_Plain(AreaT_MessageMaster, pTextList_Display_MessageMaster, &ptCur_Draw);

	// --------------------
	// キャラクター作成人数　入力
	// --------------------
	// キャラクター人数をキーボードから取得
	nAdd = InputInteger_pt(0, MAX_NUMBER_OF_CHARACTERS - (*pNumMember), &ptCur_Draw, true);

	msleep(500);
	// ※追加しないならシーン終了
	if (nAdd <= 0) 
	{
		// 後処理
		StringList_DeleteAll(pTextList_Display_MessageMaster);
		StringList_DeleteAll(pTextList_Master_MessageMaster);
		return;
	}

	// ----------
	// マスターメッセージ　表示内容更新
	// ---------
	// 現在位置をマスタメッセージリストへ
	pCur_Str = pTextList_Master_MessageMaster;
	// 空行追加
	pCur_Str = StringList_Add(pCur_Str, "", true);
	// メッセージ追加
	pCur_Str = StringList_Add_Blank(pCur_Str, true);
	sprintf(pCur_Str->szText, "%2d　めい　およびに　なるのですね", nAdd);
	// メッセージリスト(表示用）に、メッセージサイズにリサイズして代入
	pTextList_Display_MessageMaster = 
		ResizeStringList_By_tArea(pTextList_Display_MessageMaster, pTextList_Master_MessageMaster, AreaT_MessageMaster, START_FROM_LAST, 1);
	// メッセージ表示エリアをクリア
	ClearArea(&AreaT_MessageMaster);
	// メッセージ表示
	DrawTextList_Plain(AreaT_MessageMaster, pTextList_Display_MessageMaster, &ptCur_Draw);
	// --------------------
	// キャラクター作成部　描画
	// --------------------
	ptCur_Draw = ptStart_CharacterCreate_Head;
	DisplayStatusHeader_PT(&ptCur_Draw);
	for (i = 0; i < nAdd; i++)
	{
		ptCur_Draw = ptStart_CharacterCreate_Chara[i];
		isLast = (i == nAdd - 1) ? true : false;
		DisplayStatusBlank_pt(&ptCur_Draw, isLast);
	}
	// --------------------
	// キャラクター作成補助部　描画
	// --------------------
	// 変数初期化
	// 原点　X座標（キャラクター作成部　最後の一つのX座標　＋　罫線（左）　＋　表示文字数　＋　罫線（右）　＋　全角スペース）
	ptStart_CharacterCreate_Sub.x = ptStart_CharacterCreate_Chara[nAdd - 1].x + SIZE_OF_BORDER + MAX_CHARACTERS_OF_HERO_NAME + SIZE_OF_BORDER + SIZE_OF_ZENAKU_CHARACTER;
	// 原点　X座標（キャラクター作成部のY座標）
	ptStart_CharacterCreate_Sub.y = ptStart_CharacterCreate_Head.y;
	// 幅（キャラクター作成部右側全て：ウインドウ幅　+ ヌル文字 - X座標開始位置）
	nLen_CharacterCreate_Sub = MAX_WIDTH_OF_WINDOW + SIZE_OF_NULL - ptStart_CharacterCreate_Sub.x;
	// 高さ
	nLines_CharacterCreate_Sub = 15;
	// 描画
	ptCur_Draw = ptStart_CharacterCreate_Sub;
	AreaW_CharacterCreate_Sub = DrawBorderWindow(&ptCur_Draw, false, nLen_CharacterCreate_Sub, nLines_CharacterCreate_Sub);
	// 文字描画範囲取得
	AreaT_CharacterCreate_Sub = Area_Inside_BorderWindow(&AreaW_CharacterCreate_Sub);

	for (i = 0; i < nAdd; i++)
	{
		// ----------
		// マスターメッセージ　表示内容更新
		// ---------
		// 現在位置をマスタメッセージリストへ
		pCur_Str = pTextList_Master_MessageMaster;
		// 空行追加
		pCur_Str = StringList_Add(pCur_Str, "", true);
		// メッセージ追加
		pCur_Str = StringList_Add_Blank(pCur_Str, true);
		sprintf(pCur_Str->szText, "%2d　ばんめの　おなかまは　どなたに　なさいますか", i + 1);
		// メッセージリスト(表示用）に、メッセージサイズにリサイズして代入
		pTextList_Display_MessageMaster =
			ResizeStringList_By_tArea(pTextList_Display_MessageMaster, pTextList_Master_MessageMaster, AreaT_MessageMaster, START_FROM_LAST, 1);
		// メッセージ表示エリアをクリア
		ClearArea(&AreaT_MessageMaster);
		// メッセージ表示
		DrawTextList_Plain(AreaT_MessageMaster, pTextList_Display_MessageMaster, &ptCur_Draw);

		// 

		getchar();
	}
	

	
	// --------------------
	// 後処理
	// --------------------
	StringList_DeleteAll(pTextList_Display_MessageMaster);
	StringList_DeleteAll(pTextList_Master_MessageMaster);

	getchar();
}
// 【関数内容】
// キャラクター作成シーン_表示（マスタメッセージ）
// 【引数】
// pNum		:【変更対象】現在のパーティ人数
// pAdd		:【変更対象】追加人数（作成人数）
// x_start	:【参照用　】開始X座標
// y_start	:【参照用　】開始Y座標
// 【戻り値】
// 次のY座標
int		DisplayMasterMessage_CreateScene(const int* pNum, int* pAdd, int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("なかまを　およびに　なるのですね");	y++;
	gotoxy(x, y); printf("なんにん　およびに　なりますか？");	y++;
	gotoxy(x, y); InputInteger(pAdd, 0, MAX_NUMBER_OF_CHARACTERS - (*pNum), x, y, true);
	gotoxy(x, y);											y++;
	return y;
}
// 【関数内容】
// キャラクター作成シーン_表示（作成部）＋キャラクター作成
// 【引数】
// pCh			:【変更対象】作成するキャラクター構造体
// pJobList		:【参照用　】職業一覧
// x_start		:【参照用　】開始X座標
// y_start		:【参照用　】開始Y座標
// 【戻り値】
// 次のY座標
int		DisplayAndCreatePartyMember_CreateScene(tCharacter* pCh, const tJob* pJobList, int x_start, int y_start)
{
	// --------------------
	// ローカル変数宣言, 初期化
	// --------------------
	int x = x_start, y = y_start;	// 描画位置
	int tempY;						// 
	int x_end, y_end;				// 描画終了位置（）

	gotoxy(x, y); printf(""); y++;
	tempY = y;
	// --------------------
	//　カスタムキャラクター　ステータス入力
	// --------------------
	
	

	//// なまえ　入力
	//gotoxy(x, y);
	//printf("[なまえ　]");
	//InputString(pCh->szName, MAX_CHARACTERS_OF_HERO_NAME - 1, x + 10, y);
	//y++;

	//gotoxy(x, y); printf("[職　　業]");
	//DisplayJobList(pJobList, x + 10 + 14, y, &x_end, &y_end);
	//InputJob(pCh, pJobList, x + 10, y);
	//ClearJobList(x + 10 + 14, y, x_end, y_end);
	//y++;
	//gotoxy(x, y); printf("[Ｈ　　Ｐ]"); InputInteger(&(pCh->nHP_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[Ｓ　　Ｐ]"); InputInteger(&(pCh->nSP_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[こうげき]"); InputInteger(&(pCh->nAtk_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[ぼうぎょ]"); InputInteger(&(pCh->nDef_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[まほこう]"); InputInteger(&(pCh->nMAtk_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[まほぼう]"); InputInteger(&(pCh->nMDef_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[すばやさ]"); InputInteger(&(pCh->nSpd_Base), 1, 9, x + 10, y, true); y++;
	//CalculateCharacterStatus(pCh);
	return y;
}
// 【関数内容】
// キャラクター作成シーン_表示（追加不可時）
// 【引数】
// pCharacterList	: 【変更対象】キャラクターリスト
// pJobList			: 【閲覧用】　職業一覧
// pNum				: 【変更対象】キャラクター人数
// 【戻り値】
// なし
int		DisplayCantAddMessage_CreateScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("それいじょう　なかまを　つれていけませんよ。");	y++;
	gotoxy(x, y); printf("また　おこしください。");						y++;
	gotoxy(x, y);													y++;
	return y;
}
