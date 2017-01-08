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
	tPoint2D	ptCur_Draw_Sub = { 1, 1 };
	tString*	pCur_Str;				// StringListの現在位置
	const tCharacter*	pCur_Chr_S;		// CharacterListの現在位置
	tCharacter*	pCur_Chr_D;				// 
	bool		isLast;					// 最後かどうか
	int			i, j;						// ループカウンタ
	int			nCharacter_Selected;	// 選択キャラ
	int			nAdd = 1;				// 作成（追加）人数
	tCharacter* pCh = pCharacterList;	// キャラクター構造体ポインタ
	// -------
	// マスタメッセージ部　変数
	// ------
	tPoint2D	ptStart_MessageMaster = { 1, 1 };				// 原点（左上）
	int			nLen_MessageMaster = MAX_WIDTH_OF_WINDOW;		// 長さ
	int			nLines_MessageMaster = 9;						// 行数
	tArea		AreaW_MessageMaster;							// Area(Window全体）
	tArea		AreaT_MessageMaster;							// Area(Text部分）
	tString*	pTextList_Master_MessageMaster = NULL;			// メッセージリスト(全体）
	tString*	pTextList_Display_MessageMaster = NULL;			// メッセージリスト（表示部分）
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
	tPoint2D	ptStart_CharacterCreate_Sub;						//
	tPoint2D	ptStart_JobList;									// JobList　表示位置
	int			nLen_CharacterCreate_Sub;							//
	int			nLines_CharacterCreate_Sub;							// 行数
	tArea		AreaW_CharacterCreate_Sub;							// Area(Window全体）
	tArea		AreaT_CharacterCreate_Sub;							// Area(Text部分）						
	tString*	pTextList_Master_CharacterCreate_Sub = NULL;		// メッセージリスト(全体）
	tString*	pTextList_Display_CharacterCreate_Sub = NULL;		// メッセージリスト（表示部分）
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
		StringList_DeleteAll(pTextList_Display_CharacterCreate_Sub);
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
		// カスタム入力/組み込みキャラクター　選択
		// 補助ウインドウに選択肢表示
		// ---------
		ptCur_Draw = ptStart_CharacterCreate_Sub;

		StringList_DeleteAll(pTextList_Master_CharacterCreate_Sub);

		pCur_Str = StringList_New_Blank();
		sprintf(pCur_Str->szText, "%2d　ばんめのおなかまは？", i + 1);
		pCur_Str = StringList_Add(pCur_Str, "┏━━━┳━━━━┓", true);;
		pCur_Str = StringList_Add(pCur_Str, "┃コード┃なまえ　┃", true);
		pCur_Str = StringList_Add(pCur_Str, "┣━━━╋━━━━┫", true);
		
		j = 1;
		pCur_Chr_S = pBuiltInCharaList;
		while (1)
		{
			pCur_Str = StringList_Add_Blank(pCur_Str, true);
			sprintf(pCur_Str->szText, "┃　　%2d┃%s┃", j, pCur_Chr_S->szName);
			if (pCur_Chr_S->next != NULL)
			{
				pCur_Chr_S = pCur_Chr_S->next;
				j++;
			}
			else
			{
				break;
			}
		}
		pCur_Str = StringList_Add(pCur_Str, "┃　　 0┃じぶんで┃", true);
		pCur_Str = StringList_Add(pCur_Str, "┗━━━┻━━━━┛", true);

		pTextList_Master_CharacterCreate_Sub = StringList_First(pCur_Str);

		// メッセージリスト(表示用）に、メッセージサイズにリサイズして代入
		pTextList_Display_CharacterCreate_Sub =
			ResizeStringList_By_tArea(pTextList_Display_CharacterCreate_Sub, pTextList_Master_CharacterCreate_Sub, AreaT_CharacterCreate_Sub, START_FROM_LAST, 1);
		// メッセージ表示エリアをクリア
		ClearArea(&AreaT_CharacterCreate_Sub);
		// メッセージ表示
		DrawTextList_Plain(AreaT_CharacterCreate_Sub, pTextList_Display_CharacterCreate_Sub, &ptCur_Draw);

		gotoxy_pt(ptCur_Draw);
		nCharacter_Selected = InputInteger_pt(0, j, &ptCur_Draw, true);

		msleep(500);

		// --------------------
		// キャラクター情報の入力
		// --------------------
		if (nCharacter_Selected > 0)
		{
			// --------------------
			// 組み込みキャラクター
			// --------------------
			// --------------------
			// パーティメンバーの追加
			// --------------------
			// 組み込みキャラクターリストから、読み込み（選択番号-1回　次へにまわせば該当キャラクター選択）
			pCur_Chr_S = pBuiltInCharaList;
			for (j = 1; j < nCharacter_Selected; j++)
			{
				pCur_Chr_S = pCur_Chr_S->next;
			}
			// パーティメンバーに追加（パーティんメンバー人数も合わせて更新
			pCur_Chr_D = CharacterList_Add(pCharacterList, pCur_Chr_S, pNumMember, true);
			// --------------------
			// 描画
			// --------------------
			// 描画座標
			ptCur_Draw.x = ptStart_CharacterCreate_Chara[i].x + SIZE_OF_BORDER; // 描画開始位置　＋　罫線（左）
			ptCur_Draw.y = ptStart_CharacterCreate_Chara[i].y + NEXT_LINE;		// 描画開始位置　の　次の行
			// なまえ
			gotoxy_pt(ptCur_Draw);				// 移動
			printf(pCur_Chr_D->szName);			// 描画
			// 職業
			ptCur_Draw.y += NEXT_LINE;			// 改行
			gotoxy_pt(ptCur_Draw);				// 移動
			printf(pCur_Chr_D->job.szName);		// 描画
			// 改行
			ptCur_Draw.y += NEXT_LINE;			// 改行
			// HP
			ptCur_Draw.y += NEXT_LINE;			// 改行
			gotoxy_pt(ptCur_Draw);				// 移動
			printf("%8d", pCur_Chr_D->nHP);
			// SP
			ptCur_Draw.y += NEXT_LINE;			// 改行
			gotoxy_pt(ptCur_Draw);				// 移動
			printf("%8d", pCur_Chr_D->nSP);		// 描画
			// 改行
			ptCur_Draw.y += NEXT_LINE;			// 改行
			// こうげき
			ptCur_Draw.y += NEXT_LINE;			// 改行
			gotoxy_pt(ptCur_Draw);				// 移動
			printf("%8d", pCur_Chr_D->nAtk);		// 描画
			// ぼうぎょ
			ptCur_Draw.y += NEXT_LINE;			// 改行
			gotoxy_pt(ptCur_Draw);				// 移動
			printf("%8d", pCur_Chr_D->nDef);		// 描画
			// 改行
			ptCur_Draw.y += NEXT_LINE;			// 改行
			// まほこう
			ptCur_Draw.y += NEXT_LINE;			// 改行
			gotoxy_pt(ptCur_Draw);				// 移動
			printf("%8d", pCur_Chr_D->nMAtk);	// 描画
			// まほぼう
			ptCur_Draw.y += NEXT_LINE;			// 改行
			gotoxy_pt(ptCur_Draw);				// 移動
			printf("%8d", pCur_Chr_D->nMDef);	// 描画
			// 改行
			ptCur_Draw.y += NEXT_LINE;			// 改行
			// すばやさ
			ptCur_Draw.y += NEXT_LINE;			// 改行
			gotoxy_pt(ptCur_Draw);				// 移動
			printf("%8d", pCur_Chr_D->nSpd);		// 描画
		}
		// --------------------
		// カスタムキャラクター
		// --------------------
		else
		{
			msleep(500);

			pCur_Chr_D = CharacterList_Add_Blank(pCharacterList, pNumMember, true);

			// サブメッセージ表示エリアをクリア
			ClearArea(&AreaT_CharacterCreate_Sub);
			ptCur_Draw_Sub = AreaT_CharacterCreate_Sub.start;
			gotoxy_pt(ptCur_Draw_Sub);
			printf("%2d　ばんめのおなかまは？", i + 1);
			// 描画座標
			ptCur_Draw.x = ptStart_CharacterCreate_Chara[i].x + SIZE_OF_BORDER; // 描画開始位置　＋　罫線（左）
			ptCur_Draw.y = ptStart_CharacterCreate_Chara[i].y + NEXT_LINE;		// 描画開始位置　の　次の行

			ptStart_JobList.x = AreaT_CharacterCreate_Sub.end.x - (SIZE_OF_BORDER + 3 * SIZE_OF_ZENAKU_CHARACTER + SIZE_OF_BORDER + MAX_CHARACTERS_OF_JOB_NAME + SIZE_OF_BORDER);
			ptStart_JobList.y = AreaT_CharacterCreate_Sub.start.y + NEXT_LINE + NEXT_LINE;

			//-----------
			// なまえ
			//-----------
			// 入力
			ptCur_Draw_Sub.y += NEXT_LINE;
			gotoxy_pt(ptCur_Draw_Sub);
			printf("おなまえ　は？");
			ptCur_Draw_Sub.y += NEXT_LINE;
			gotoxy_pt(ptCur_Draw_Sub);
			InputString_pt(pCur_Chr_D->szName, MAX_CHARACTERS_OF_HERO_NAME, &ptCur_Draw_Sub);
			// 描画
			gotoxy_pt(ptCur_Draw);										
			printf(pCur_Chr_D->szName);	
			//-----------
			// 職業
			//-----------
			// 入力
			ptCur_Draw_Sub.y++;
			gotoxy_pt(ptCur_Draw_Sub);
			printf("職　　業　は？");
			ptCur_Draw_Sub.y++;
			gotoxy_pt(ptCur_Draw_Sub);
			InputJob_pt(pCur_Chr_D, pJobList, &ptCur_Draw_Sub, &ptStart_JobList);
			
			ptCur_Draw.y += NEXT_LINE;											// 改行
			gotoxy_pt(ptCur_Draw);												// 移動
			printf(pCur_Chr_D->job.szName);										// 描画
			// 改行
			ptCur_Draw.y += NEXT_LINE;											// 改行
			// HP
			ptCur_Draw.y += NEXT_LINE;											// 改行
			gotoxy_pt(ptCur_Draw);												// 移動
			printf("%8d", pCur_Chr_D->nHP);
			// SP
			ptCur_Draw.y += NEXT_LINE;											// 改行
			gotoxy_pt(ptCur_Draw);												// 移動
			printf("%8d", pCur_Chr_D->nSP);										// 描画
			// 改行
			ptCur_Draw.y += NEXT_LINE;											// 改行
			// こうげき
			ptCur_Draw.y += NEXT_LINE;											// 改行
			gotoxy_pt(ptCur_Draw);												// 移動
			printf("%8d", pCur_Chr_D->nAtk);										// 描画
			// ぼうぎょ
			ptCur_Draw.y += NEXT_LINE;											// 改行
			gotoxy_pt(ptCur_Draw);												// 移動
			printf("%8d", pCur_Chr_D->nDef);										// 描画
			// 改行
			ptCur_Draw.y += NEXT_LINE;											// 改行
			// まほこう
			ptCur_Draw.y += NEXT_LINE;											// 改行
			gotoxy_pt(ptCur_Draw);												// 移動
			printf("%8d", pCur_Chr_D->nMAtk);									// 描画
			// まほぼう
			ptCur_Draw.y += NEXT_LINE;											// 改行
			gotoxy_pt(ptCur_Draw);												// 移動
			printf("%8d", pCur_Chr_D->nMDef);									// 描画
			// 改行
			ptCur_Draw.y += NEXT_LINE;											// 改行
			// すばやさ
			ptCur_Draw.y += NEXT_LINE;											// 改行
			gotoxy_pt(ptCur_Draw);												// 移動
			printf("%8d", pCur_Chr_D->nSpd);										// 描画
		}
	}
	

	
	// --------------------
	// 後処理
	// --------------------
	StringList_DeleteAll(pTextList_Display_MessageMaster);
	StringList_DeleteAll(pTextList_Master_MessageMaster);

	getchar();
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
