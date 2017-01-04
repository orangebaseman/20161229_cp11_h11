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
	// ローカル変数宣言
	// --------------------
	int x, y, tempY;					// 描画XY座標
	tPoint2D	ptCur;
	int i;								// ループカウンタ
	int nAdd;							// 作成（追加）人数
	tCharacter* pCh = pCharacterList;	// キャラクター構造体ポインタ

	tPoint2D	ptStart_MessageMaster = { 1, 1 };
	int			nLen_MessageMaster = MAX_WIDTH_OF_WINDOW;
	int			nLines_MessageMaster = 9;
	tArea		MesMaster_AreaW;
	tArea		MesMaster_AreaT;
	tString*	MesMaster_pTextList;

	// --------------------
	// 初期化
	// --------------------
	clrscr();
	// ※人数チェック:　上限人数ならばエラー表示をしてシーン終了
	if ((*pNumMember) >= MAX_NUMBER_OF_CHARACTERS)
	{
		DisplayCantAddMessage_CreateScene(2, 2);
		getchar();
		return;
	}
	y = 2;
	nAdd = 1;

	ptCur = ptStart_MessageMaster;
	MesMaster_AreaW = DrawBorderWindow(&ptCur, true, nLen_MessageMaster, nLines_MessageMaster);

	ptCur.x = MesMaster_AreaW.start.x + 2;
	ptCur.y = MesMaster_AreaW.start.y + 1;

	MesMaster_pTextList = StringList_New();
	strcpy(MesMaster_pTextList->szText, "なかまを　およびに　なるのですね");
	MesMaster_pTextList = StringList_Add(MesMaster_pTextList, true);
	strcpy(MesMaster_pTextList->szText, "なんにん　およびに　なりますか？");
	
	MesMaster_pTextList = StringList_First(MesMaster_pTextList);
	while (MesMaster_pTextList != NULL)
	{
		gotoxy(ptCur.x , ptCur.y);
		printf(MesMaster_pTextList->szText);
		if (ptCur.y <= MesMaster_AreaW.end.y && MesMaster_pTextList->next != NULL)
		{
			ptCur.y += 1;
			MesMaster_pTextList = MesMaster_pTextList->next;
		}
		else
		{
			break;
		}
	}

	getchar();
	StringList_DeleteAll(MesMaster_pTextList);

	// --------------------
	// キャラクター作成人数　入力
	// --------------------
	//y = DisplayMasterMessage_CreateScene(pNumMember, &nAdd, 2, 2);
	Clear_Inside_BorderWindow(&MesMaster_AreaW);

	// ※追加しないならシーン終了
	if (nAdd <= 0) return;
	// --------------------
	// キャラクター作成部
	// --------------------
	DisplayStatusHeader(2, y);
	for (i = 0; i < nAdd; i++)
	{
		DisplayStatusBlank(2 + (i + 1) * 10, y, i == nAdd - 1);
	}


		// キャラクター構造体　新規作成
		//pCh = CharacterList_Add(pCh, pNumMember, true);
		// 描画X座標
		//x = 2 + i * 23;
		// 
		// 
		// カスタムキャラクター
		//tempY = DisplayAndCreatePartyMember_CreateScene(pCh, pJobList, x, y);
	
	//y = tempY;

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
	//　組み込みキャラクター選択
	// --------------------
	//gotoxy(x, y); printf("┏━━━┳━━━━┓"); y++;
	//gotoxy(x, y); printf("┃コード┃なまえ　┃"); y++;
	//gotoxy(x, y); printf("┣━━━╋━━━━┫"); y++;

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
