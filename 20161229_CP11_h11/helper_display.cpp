// --------------------
// 表示補助
// --------------------
#include	"public.h"
#include	"conioex.h"

#ifndef PREVIOUS_LINE
#define	PREVIOUS_LINE	(1)	//1行前
#endif
#ifndef NEXT_LINE
#define	NEXT_LINE		(1)	//1行次
#endif

// --------------------
// 疑似private関数宣言
// --------------------
tArea	DrawLine_Blank_(tPoint2D*, bool, const char*, const char*, const size_t);
tArea	DrawLine_Border(tPoint2D*, bool, const char*, const char*, const size_t, const char*);

// 【関数内容】
// gotoxy(conioex.h)のオーバーロード
// 【引数】
// point	: 【参照用　】移動先座標
// 【戻り値】
// なし
void	gotoxy_pt(tPoint2D point)
{
	gotoxy(point.x, point.y);
}

// 【関数内容】
// 描画範囲をクリア
// 【引数】
// area	: 【閲覧用　】描画範囲
// 【戻り値】
// なし
void	ClearArea(const tArea* area)
{
	int x;
	tPoint2D ptCur = area->start;
	// --------------------
	// 範囲内を半角スペースで上書き
	// --------------------
	for (ptCur.y = area->start.y; ptCur.y <= area->end.y; ptCur.y++)
	{
		gotoxy_pt(ptCur);
		for (x = area->start.x; x <= area->end.x; x++)
		{
			printf(" ");
		}
	}
}

// 【関数内容】
// 罫線ウインドウ　内側の描画範囲を取得
// 【引数】
// area	: 【閲覧用　】罫線ウインドウの描画範囲範囲
// 【戻り値】
//  罫線ウインドウ　内側の描画範囲
tArea Area_Inside_BorderWindow(const tArea* area)
{
	tArea area_inside = (*area);
	area_inside.start.x += SIZE_OF_BORDER;
	area_inside.start.y += NEXT_LINE;
	area_inside.end.x -= SIZE_OF_BORDER;
	area_inside.end.y -= PREVIOUS_LINE;
	return area_inside;
}

// 【関数内容】
// 罫線ウインドウ　空白行の描画
// 【引数】
// pPtStart		: 【変更対象】描画原点（左上）
// isUpdateCur	: 【参照用　】描画位置を更新するか否か
// borderLeft	: 【参照用　】罫線文字（左側）
// borderRight	: 【参照用　】罫線文字（右側）
// size_cell	: 【参照用　】空白文字数
// 【戻り値】
// 描画領域
tArea	DrawLine_Blank_(tPoint2D* pPtStart, bool isUpdateCur, const char* borderLeft, const char* borderRight, const size_t size_cell)
{
	// --------------------
	// ローカル変数宣言、初期化
	// --------------------
	// 描画座標
	tPoint2D	ptCur = (*pPtStart);
	// 描画領域
	tArea		area = { ptCur, ptCur };
	// 罫線文字変数　メモリ確保
	char*		borderL = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	char*		borderR = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	// 罫線文字コピー（文字数オーバーならトリミング）
	Trim_And_Copy_String(borderL, borderLeft, SIZE_OF_BORDER);
	Trim_And_Copy_String(borderR, borderRight, SIZE_OF_BORDER);
	// --------------------
	// 描画
	// --------------------
	// 罫線（左）
	gotoxy_pt(ptCur);									// 移動実行
	printf(borderL);									// 描画
	// 罫線（右）
	ptCur.x = pPtStart->x + SIZE_OF_BORDER + size_cell;	// X移動位置（表示文字数分スキップ）
	gotoxy_pt(ptCur);									// 移動実行
	printf(borderR);									// 描画
	// 改行
	ptCur.x = pPtStart->x;								// X移動位置（初期位置）
	ptCur.y += 1;										// Y移動位置（改行）
	// --------------------
	// メモリ解放
	// --------------------
	free(borderL);
	free(borderR);
	// --------------------
	// 描画領域更新 （＝終端位置を更新）
	// --------------------
	// X: 開始座標 + 罫線（左）　＋　表示文字数 + 罫線（右）　- １文字前
	area.end.x = pPtStart->x + SIZE_OF_BORDER + size_cell *  + SIZE_OF_BORDER - SIZE_OF_HANKAKU_CHARACTER;
	// Y: 現在座標 - 1行前
	area.end.y = ptCur.y - PREVIOUS_LINE;
	// --------------------
	// 次の描画位置を更新
	// --------------------
	if (isUpdateCur)
	{
		(*pPtStart) = ptCur;
	}
	// --------------------
	// 描画領域を返却
	// --------------------
	return area;
}
// 【関数内容】
// 罫線ウインドウ　罫線行の描画
// 【引数】
// pPtStart		: 【変更対象】描画原点（左上）
// isUpdateCur	: 【参照用　】描画位置を更新するか否か
// borderLeft	: 【参照用　】罫線文字（左側）
// borderRight	: 【参照用　】罫線文字（中央）
// size_cell	: 【参照用　】描画文字数
// borderRight	: 【参照用　】罫線文字（右側）
// 【戻り値】
// 描画領域
tArea	DrawLine_Border(tPoint2D* pPtStart, bool isUpdateCur, const char* borderLeft, const char* borderCenter, const size_t size_cell, const char* borderRight)
{
	// --------------------
	// ローカル変数宣言、初期化	
	// --------------------
	// ループカウンタ
	int			i;
	// 描画座標
	tPoint2D	ptCur = (*pPtStart);
	// 描画領域
	tArea		area = { ptCur, ptCur };
	// 罫線文字変数　メモリ確保
	char*		borderL = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	char*		borderC = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	char*		borderR = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	// 罫線文字コピー（文字数オーバーならトリミング）
	Trim_And_Copy_String(borderL, borderLeft, SIZE_OF_BORDER);
	Trim_And_Copy_String(borderC, borderCenter, SIZE_OF_BORDER);
	Trim_And_Copy_String(borderR, borderRight, SIZE_OF_BORDER);
	// --------------------
	// 描画
	// --------------------
	// 罫線（左）
	gotoxy_pt(ptCur);				// 移動実行
	printf(borderL);				// 描画
	// 罫線（中央）（表示文字数分描画）
	for (int i = 0; i < size_cell; i += SIZE_OF_ZENAKU_CHARACTER)
	{
		printf(borderC);			// 描画
	}
	// 罫線（右）
	printf(borderR);				// 描画
	// 改行
	ptCur.x = pPtStart->x;			// X移動位置（初期位置）
	ptCur.y += 1;					// Y移動位置（改行）
	// --------------------
	// メモリ解放
	// --------------------
	free(borderL);
	free(borderC);
	free(borderR);
	// --------------------
	// 描画領域更新 （＝終端位置を更新）
	// --------------------
	// X: 開始座標 + 罫線（左）　＋　表示文字数(罫線（中央）) + 罫線（右）　- １文字前
	area.end.x = pPtStart->x + SIZE_OF_BORDER + size_cell + SIZE_OF_BORDER - SIZE_OF_HANKAKU_CHARACTER;
	// Y: 現在座標 - 1行前
	area.end.y = ptCur.y - PREVIOUS_LINE;
	// --------------------
	// 次の描画位置を更新
	// --------------------
	if (isUpdateCur)
	{
		(*pPtStart) = ptCur;
	}
	// --------------------
	// 描画領域を返却
	// --------------------
	return area;
}

tArea	DrawBorderWindow(tPoint2D* pPtStart, bool isUpdateCur, const size_t width, const size_t height)
{
	// --------------------
	// ローカル変数宣言、初期化	
	// --------------------
	// ループカウンタ
	int i;
	// 描画座標
	tPoint2D	ptCur = (*pPtStart);
	// 全角描画終了座標 
	tPoint2D	ptZenkakuEnd = { pPtStart->x + width - SIZE_OF_ZENAKU_CHARACTER,
								pPtStart->y + height - PREVIOUS_LINE };
	// 描画領域
	tArea		area = { ptCur, ptCur };
	// --------------------
	// エラーチェック：　エラーなら描画せずに終了
	// --------------------
	// 幅は全角サイズか
	if (width % SIZE_OF_ZENAKU_CHARACTER != 0)
	{
		gotoxy_pt(ptCur);
		printf("DrawBorderWindow ERROR:全角文字のサイズ（偶数）を入力してください");
		return area;
	}
	if (width < 2 * SIZE_OF_ZENAKU_CHARACTER || height < 2)
	{
		gotoxy_pt(ptCur);
		printf("DrawBorderWindow ERROR:ウインドウが成立するサイズを入力してください");
		return area;
	}
	if (ptZenkakuEnd.x > MAX_WIDTH_OF_WINDOW - SIZE_OF_HANKAKU_CHARACTER ||
		ptZenkakuEnd.y > MAX_HEIGHT_OF_WINDOW)
	{
		gotoxy_pt(ptCur);
		printf("DrawBorderWindow ERROR:ウインドウの表示枠を超えて入力しようとしています。サイズを確認してください。");
		return area;
	}
	// --------------------
	// 描画
	// --------------------
	// --------
	// 四隅描画
	// --------
	// 左上隅
	gotoxy_pt(ptCur);			// 移動実行
	printf("┏");				// 描画
	// 右上隅
	ptCur.x = ptZenkakuEnd.x;	// X移動位置（全角終了座標）
	ptCur.y = pPtStart->y;		// Y移動位置（原点）
	gotoxy_pt(ptCur);			// 移動実行
	printf("┓");				// 描画
	// 左下隅
	ptCur.x = pPtStart->x;		// X移動位置（原点）
	ptCur.y = ptZenkakuEnd.y;	// Y移動位置（全角終了座標）
	gotoxy_pt(ptCur);			// 移動実行
	printf("┗");				// 描画
	// 右下隅
	ptCur.x = ptZenkakuEnd.x;	// X移動位置（全角終了座標）
	ptCur.y = ptZenkakuEnd.y;	// Y移動位置（全角終了座標）
	gotoxy_pt(ptCur);			// 移動実行
	printf("┛");				// 描画
	// --------
	// 直線描画
	// --------
	// 横描画 (両端は描画せず）
	for (i = 0 + SIZE_OF_BORDER; i <= ptZenkakuEnd.x - SIZE_OF_BORDER; i += SIZE_OF_ZENAKU_CHARACTER)
	{
		ptCur.x = pPtStart->x + i;	// X座標位置
		// 上側
		ptCur.y = pPtStart->y;		// Y座標位置（原点）
		gotoxy_pt(ptCur);			// 移動実行
		printf("━");				// 描画
		// 下側
		ptCur.y = ptZenkakuEnd.y;	// Y移動位置（全角終了座標）
		gotoxy_pt(ptCur);			// 移動実行
		printf("━");				// 描画
	}
	// 縦描画 (両端は描画せず）
	for (i = 0 + NEXT_LINE; i < ptZenkakuEnd.y - PREVIOUS_LINE; i++)
	{
		ptCur.y = pPtStart->y + i;	// Y座標位置
		// 上側
		ptCur.x = pPtStart->x;		// X移動位置（原点）
		gotoxy_pt(ptCur);			// 移動実行
		printf("┃");				// 描画
		// 下側
		ptCur.x = ptZenkakuEnd.x;	// X移動位置（全角終了座標）
		gotoxy_pt(ptCur);			// 移動実行
		printf("┃");				// 描画
	}
	// --------------------
	// 描画領域更新 （＝終端位置を更新）
	// --------------------
	// X: 開始座標 + haba - 1文字前
	area.end.x = pPtStart->x + width - SIZE_OF_HANKAKU_CHARACTER;
	// Y: 開始座標 + 高さ - 1行前
	area.end.y = pPtStart->y + height - PREVIOUS_LINE;
	// --------------------
	// 次の描画位置を更新
	// --------------------
	if (isUpdateCur)
	{
		ptCur.x = pPtStart->x;
		ptCur.y = area.end.y + 1;
		(*pPtStart) = ptCur;
	}
	// --------------------
	// 描画領域を返却
	// --------------------
	return area;
}

// 【関数内容】
// テキストリストを指定位置に描画（単純描画）
// 【引数】
// AreaDisp		: 【参照用　】文字表示の領域
// pTextList	: 【参照用　】表示するテキストリスト
// ptCur_Draw	: 【変更対象】描画現在位置（関数終了後も継続）
// 【戻り値】
// なし
void DrawTextList_Plain(tArea AreaDisp, tString* pTextList, tPoint2D* ptCur_Draw)
{
	// 現在位置の更新
	(*ptCur_Draw) = AreaDisp.start;
	tString* pCur_Str = StringList_First(pTextList);
	// 描画実行（１行目で条件を満たしていなければ、描画しない）
	while (ptCur_Draw->y <= AreaDisp.end.y && pCur_Str != NULL)
	{
		// 移動、描画
		gotoxy_pt(*ptCur_Draw);
		printf(pCur_Str->szText);
		// 描画を続けるか（次の行が描画範囲内かどうか、次のメッセージの有無で判定）
		if (ptCur_Draw->y + 1 <= AreaDisp.end.y && pCur_Str->next != NULL)
		{
			// 次の行あり（情報を更新）
			ptCur_Draw->y += 1;			// 描画位置を次の行へ
			pCur_Str = pCur_Str->next;	// 表示メッセージを次へ
		}
		else
		{
			// 次の行なし（描画終了）
			ptCur_Draw->y += 1;			// 描画位置を次の行へ
			gotoxy_pt(*ptCur_Draw);		// 移動
			break;
		}
	}
}


// 【関数内容】
// ステータスヘッダの表示
// 【引数】
// x_start	: 【参照用　】描画原点（左上）
// y_start	: 【参照用　】描画原点（左上）
// 【戻り値】
// 次の描画位置（Y座標)
int		DisplayStatusHeader(int x_start, int y_start)
{
	// --------------------
	// ローカル変数宣言、初期化
	// --------------------
	int x = x_start, y = y_start;	//	描画座標
	// --------------------
	// 描画
	// --------------------
	gotoxy(x, y); printf("┏━━━━┳"); y++;
	gotoxy(x, y); printf("┃なまえ　┃"); y++;
	gotoxy(x, y); printf("┃職　　業┃"); y++;
	gotoxy(x, y); printf("┠────╂"); y++;
	gotoxy(x, y); printf("┃Ｈ　　Ｐ┃"); y++;
	gotoxy(x, y); printf("┃Ｓ　　Ｐ┃"); y++;
	gotoxy(x, y); printf("┠────╂"); y++;
	gotoxy(x, y); printf("┃こうげき┃"); y++;
	gotoxy(x, y); printf("┃ぼうぎょ┃"); y++;
	gotoxy(x, y); printf("┠────╂"); y++;
	gotoxy(x, y); printf("┃まほこう┃"); y++;
	gotoxy(x, y); printf("┃まほぼう┃"); y++;
	gotoxy(x, y); printf("┠────╂"); y++;
	gotoxy(x, y); printf("┃すばやさ┃"); y++;
	gotoxy(x, y); printf("┗━━━━┻"); y++;
	// --------------------
	// 次の描画位置（Y）を返却
	// --------------------
	return y;
}

tPoint2D*	DisplayStatusHeader_PT(tPoint2D* ptStart)
{
	ptStart->y = DisplayStatusHeader(ptStart->x, ptStart->y);
	return ptStart;
}

// 【関数内容】
// ステータス　空白版の表示
// 【引数】
// x_start	: 【参照用　】描画原点（左上）
// y_start	: 【参照用　】描画原点（左上）
// isLast	: 【参照用　】最後の１つか否か
// 【戻り値】
// 次の描画位置（Y座標)
//　　　　　　　　(isLAST)
//┳━━━━┳  ┳━━━━┓
//┃　　　　┃  ┃　　　　┃
//┃　　　　┃  ┃　　　　┃
//╂────╂  ╂────┨
//┃　　　　┃  ┃　　　　┃
//┃　　　　┃  ┃　　　　┃
//╂────╂  ╂────┨
//┃　　　　┃  ┃　　　　┃
//┃　　　　┃  ┃　　　　┃
//╂────╂  ╂────┨
//┃　　　　┃  ┃　　　　┃
//┃　　　　┃  ┃　　　　┃
//╂────╂  ╂────┨
//┃　　　　┃  ┃　　　　┃
//┻━━━━┻  ┻━━━━┛
int			DisplayStatusBlank(int x_start, int y_start, bool isLast)
{
	// --------------------
	// ローカル変数宣言、初期化
	// --------------------
	int x = x_start, y = y_start;
	tPoint2D	ptCur = { x_start, y_start };

	// --------------------
	// 描画
	// --------------------	
	DrawLine_Border(&ptCur, true, "┳", "━", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "┳" : "┓"));
	DrawLine_Blank_(&ptCur, true, "┃", "┃", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Blank_(&ptCur, true, "┃", "┃", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "╂", "─", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "╂" : "┨"));
	DrawLine_Blank_(&ptCur, true, "┃", "┃", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Blank_(&ptCur, true, "┃", "┃", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "╂", "─", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "╂" : "┨"));
	DrawLine_Blank_(&ptCur, true, "┃", "┃", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Blank_(&ptCur, true, "┃", "┃", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "╂", "─", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "╂" : "┨"));
	DrawLine_Blank_(&ptCur, true, "┃", "┃", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Blank_(&ptCur, true, "┃", "┃", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "╂", "─", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "╂" : "┨"));
	DrawLine_Blank_(&ptCur, true, "┃", "┃", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "┻", "━", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "┻" : "┛"));

	y = ptCur.y;
	//// --------------------
	// 次の描画位置（Y）を返却
	// --------------------
	return y;
}

tPoint2D*	DisplayStatusBlank_pt(tPoint2D* ptStart, bool isLast)
{
	ptStart->y = DisplayStatusBlank(ptStart->x, ptStart->y, isLast);
	return ptStart;
}

// 【関数内容】
// 職業一覧を表示
// 【引数】
// pJobList	: 【閲覧用　】職業一覧
// x_start	: 【閲覧用　】描画原点（左上）
// y_start	: 【閲覧用　】描画原点（左上）
// x_end	: 【変更対象】描画終了位置座標（右下）
// y_end	: 【変更対象】描画終了位置座標（右下）
// 【戻り値】
// なし
void	DisplayJobList(const tJob* pJobList, int x_start, int y_start, int* x_end, int* y_end)
{	// --------------------
	// ローカル変数宣言、初期化
	// --------------------
	int x = x_start, y = y_start;	// 描画座標
	// --------------------
	// 描画
	// --------------------
	gotoxy(x, y); printf("┏━━━┳━━━━┓"); y++;
	gotoxy(x, y); printf("┃コード┃職　　業┃"); y++;
	gotoxy(x, y); printf("┣━━━╋━━━━┫"); y++;
	gotoxy(x, y); printf("┃　　 1┃けんし　┃"); y++;
	gotoxy(x, y); printf("┃　　 2┃タンク　┃"); y++;
	gotoxy(x, y); printf("┃　　 3┃かくとう┃"); y++;
	gotoxy(x, y); printf("┃　　 4┃にんじゃ┃"); y++;
	gotoxy(x, y); printf("┃　　 5┃まほう　┃"); y++;
	gotoxy(x, y); printf("┃　　 6┃み　　こ┃"); y++;
	gotoxy(x, y); printf("┗━━━┻━━━━┛"); y++;
	// --------------------
	// 描画終了位置座標
	// --------------------
	(*x_end) = x_start + 10 * SIZE_OF_ZENAKU_CHARACTER;	// 全角１０文字右
	(*y_end) = y - 1;									// 現在位置の一つ上
}

// 【関数内容】
// 文字列を指定文字数でリサイズ
// （オーバーしたらtStringを分割し、Listに追加）
// 【引数】
// pStrLine	: 【変更対象】リサイズする文字列
// nMaxLen	: 【参照用　】１行の最大文字数
// 【戻り値】
// 増えた行数
int		ResizeStringLine(tString* pStrLine, int nMaxLen)
{
	// --------------------
	// ローカル変数宣言、初期化
	// --------------------
	tString* pNewLine;						// 追加行
	int nLen = strlen(pStrLine->szText);		// 現在の文字列の長さ
	int nAddedLines = 0;					// 追加行数
	// --------------------
	// 分割
	// --------------------
	if (nLen > nMaxLen)
	{
		// 行数インクリメント
		nAddedLines++;
		// Listに追加
		pNewLine = StringList_Add_Blank(pStrLine, false);
		// 追加行の文字列：nLenMax+1番目から残りすべて（nLen-nLenMax文字）をコピー
		Copy_String_From_Certain(pNewLine->szText, pStrLine->szText, nMaxLen + 1, nLen - nMaxLen);
		// 現在の文字列：最初からnLenMax文字分にトリミング
		Trim_And_Copy_String(pStrLine->szText, pStrLine->szText, nMaxLen);
		// 追加行の文字列をリサイズ（帰納的に呼び出し）
		nAddedLines += ResizeStringLine(pNewLine, nMaxLen);
	}
	// --------------------
	// 追加行数を返却
	// --------------------
	return nAddedLines;
}

// 【関数内容】
// 文字列リストを指定サイズにリサイズ（１行の文字数、行数で指定）
// 【引数】
// pDest	: 【変更対象】表示用文字列
// pSource	: 【参照用　】元データ
// order	: 【参照用　】０：最初から
// nStart	: 【参照用　】○文字目
// nMaxLen	: 【参照用　】1行あたりの表示文字数
// nMaxLines: 【参照用　】表示行数
// 【戻り値】
// リサイズした文字列リスト
tString* ResizeStringList_By_LengthAndLines(tString* pDest, tString* pSource, int order, int nStart, int nMaxLen, int nMaxLines)
{
	// --------------------
	// ローカル変数宣言
	// --------------------
	tString* pStart_S;			// 参照開始行
	tString* pCur_S;			// 現在地（参照文字列）
	tString* pCur_D;			// 現在地（表示文字列）
	int nLines = 0;				// 行数
	int i;						// ループカウンタ
	int nAddLine = 0;			// 追加行数
	// --------------------
	// 初期化
	// --------------------
	// 表示文字列初期化
	StringList_DeleteAll(pDest);
	pDest = StringList_New_Blank();
	pCur_D = pDest;
	// --------------------
	// 最初から次へ
	// --------------------
	if (order == START_FROM_FIRST)
	{
		// --------------------
		// 参照開始行を決定
		// --------------------
		nLines = 1;								// 移動行数初期化
		pStart_S = StringList_First(pSource);	// 参照開始行初期化（一番初めに移動）
		while (1)
		{
			nLines++;							// 行数更新
			// --------------------
			// 次の行　有無判定　（行数、次の参照列を確認）
			// --------------------
			if (nLines <= nStart && pStart_S->next != NULL)
			{
				// --------------------
				// 次の行あり
				// --------------------
				pStart_S = pStart_S->next;		//　参照開始行を次へ
			}
			else
			{
				// --------------------
				// 次の行なし
				// --------------------
				break;
			}
		}
		// --------------------
		// 表示文字列リストの作成
		// --------------------
		pCur_S = pStart_S;									// 現在地を参照開始行へ移動
		nLines = 0;											// 表示行数を初期化
		while (1)
		{
			// --------------------
			// 表示行のコピー
			// --------------------
			strcpy(pCur_D->szText, pCur_S->szText);			// 文字列をコピー（参照行→表示文字列）
			nLines += 1;									// 表示文字列の行数をカウント
			nAddLine = ResizeStringLine(pCur_D, nMaxLen);	// 表示文字列の長さをリサイズ
			for (i = 0; i < nAddLine; i++)					
			{
				pCur_D = pCur_D->next;						// 表示文字列の現在地を、リサイズして増えた行数分移動					
				nLines++;									// 表示文字列の行数を、リサイズして増えた行数分移動
			}
			// --------------------
			// 次の行　有無判定　（行数、次の参照列を確認）
			// --------------------
			if (nLines <= nMaxLines && pCur_S->next != NULL)
			{
				// --------------------
				// 次の行あり
				// --------------------
				pCur_D = StringList_Add_Blank(pCur_D, false);		// 新規作成
				pCur_S = pCur_S->next;						// 次へ（参照文字列）
			}
			else
			{
				// --------------------
				// 次の行なし　（行数が増えすぎていたら最後から削る）
				// --------------------
				pCur_D = StringList_Last(pCur_D);
				while (nLines > nMaxLines && pCur_D->prev != NULL)
				{
					pCur_D = pCur_D->prev;					// 一つ前に戻して
					StringList_Delete(pCur_D->next);			// 削除
					nLines--;								// 行数を減らす
				}
				break;
			}
		}
	}
	// --------------------
	// 最後から前へ
	// --------------------
	else if (order == START_FROM_LAST)
	{
		// --------------------
		// 参照開始行を決定
		// --------------------
		nLines = 1;								// 移動行数初期化
		pStart_S = StringList_Last(pSource);	// 参照開始行初期化（一番最後に移動）
		while (1)
		{
			nLines++;						// 行数更新
			// --------------------
			// 前の行　有無判定　（行数、前の参照列を確認）
			// --------------------
			if (nLines <= nStart && pStart_S->prev != NULL)
			{
				// --------------------
				// 前の行あり
				// --------------------
				pStart_S = pStart_S->prev;		//　参照開始行をひとつ前へ
			}
			else
			{
				// --------------------
				// 前の行なし
				// --------------------
				break;
			}
		}
		// --------------------
		// 表示文字列リストの作成
		// --------------------
		pCur_S = pStart_S;									// 現在地を参照開始行へ移動
		nLines = 0;											// 表示行数を初期化
		while (1)
		{
			// --------------------
			// 表示行のコピー
			// --------------------
			strcpy(pCur_D->szText, pCur_S->szText);			// 文字列をコピー（参照行→表示文字列）
			nLines += 1;									// 表示文字列の行数をカウント
			nAddLine = ResizeStringLine(pCur_D, nMaxLen);	// 表示文字列の長さをリサイズ
			for (i = 0; i < nAddLine; i++)
			{
				pCur_D = pCur_D->next;						// 表示文字列の現在地を、リサイズして増えた行数分移動					
				nLines++;									// 表示文字列の行数を、リサイズして増えた行数分移動
			}
			// --------------------
			// 次の行　有無判定　（行数、前の参照列を確認）
			// --------------------
			if (nLines <= nMaxLines && pCur_S->prev != NULL)
			{
				// --------------------
				// 次の行あり
				// --------------------
				pCur_D = StringList_Add_Blank(pCur_D, false);		// 新規作成
				pCur_S = pCur_S->prev;						// 前へ（参照文字列）
			}
			else
			{
				// --------------------
				// 次の行なし　（行数が増えすぎていたら最初から削る）
				// --------------------
				pCur_D = StringList_First(pCur_D);
				while (nLines > nMaxLines && pCur_D->next != NULL)
				{
					pCur_D = pCur_D->next;				// 一つ先に進めて
					StringList_Delete(pCur_D->prev);		// 削除
					nLines--;							// 行数を減らす
				}
				break;
			}
		}
		pCur_D = StringList_Reverse(pCur_D);
	}
	// --------------------
	// リサイズした参照文字列リストを返却
	// --------------------
	pCur_D = StringList_First(pCur_D);
	return pCur_D;
}

tString* ResizeStringList_By_tArea(tString* pDest, tString* pSource, tArea area, int order, int nStart)
{
	int nLength = area.end.x - area.start.x + 1;
	int nLines = area.end.y - area.start.y + 1;
	return ResizeStringList_By_LengthAndLines(pDest, pSource, order, nStart, nLength, nLines);
}
