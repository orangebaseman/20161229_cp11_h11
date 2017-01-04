// --------------------
// 入力補助
// -------------------
#include	"conioex.h"
#include	"public.h"
#include	<stdlib.h>

#ifndef MAX_CHARACTERS_OF_STR_FUNCTION
#define MAX_CHARACTERS_OF_STR_FUNCTION	(50)	// 文字列操作関数　最大文字数
#endif // MAX_CHARACTERS_OF_STR_FUNCTION

// 【関数内容】
// ステータスヘッダの表示
// 【引数】
// x_start	: 【参照用　】描画原点（左上）
// y_start	: 【参照用　】描画原点（左上）
// 【戻り値】
// 次の描画位置（Y座標)
int		InputInteger(int* pInput, unsigned int min, unsigned int max, int x_start, int y_start, bool isMinMaxShowed)
{
	int x = x_start, y = y_start;
	int i;							// ループ変数
	int len;						// 桁数
	if (max == 0)
	{
		len = 1;
	}
	else
	{
		len = (int)log10((double)max) + 1;
	}
	while (1)
	{
		gotoxy(x, y);
		printf("[");
		for (i = 0; i < len; i++)
		{
			printf(" ");
		}
		printf("]");
		if (isMinMaxShowed)
		{
			printf("[%2d - %2d ]", min, max);
		}

		gotoxy(x + 1, y);
		rewind(stdin);
		scanf("%d", pInput);
		if ((*pInput) >= min && (*pInput) <= max)
		{
			return y++;
		}
		else
		{
			gotoxy(x + len + 2, y);
			printf("[※再入力]");
		}
	}
}
void	InputString(char pInput[], int nMaxLen, int x_start, int y_start)
{
	int i;
	int x = x_start, y = y_start;
	int nLen;
	char cYN;
	char strStyle[6];
	sprintf(strStyle, "%%%ds", nMaxLen);

	while (1)
	{
		gotoxy(x, y);
		printf("[");
		for (i = 0; i < nMaxLen; i++)
		{
			printf(" ");
		}
		printf("]");

		gotoxy(x + 1, y);
		rewind(stdin);
		scanf(strStyle, pInput);
		nLen = strlen(pInput);
		for (i = nLen; i < nMaxLen; i++)
		{
			strcat(pInput, " ");
		}

		gotoxy(x + nMaxLen + 1, y);
		printf("]OK?(Y/N)");
		for (i = x + nMaxLen + 12; i <= MAX_WIDTH_OF_WINDOW; i++)
		{
			printf(" ");
		}
		gotoxy(x + nMaxLen + 12, y);
		rewind(stdin);
		scanf("%c", &cYN);
		gotoxy(x + nMaxLen + 2, y);
		for (i = x + nMaxLen + 2; i <= MAX_WIDTH_OF_WINDOW; i++)
		{
			printf(" ");
		}
		if (cYN == 'Y' || cYN == 'y')
		{
			return;
		}
	}
}
void	InputJob(tCharacter* pCh, const tJob* pJobList, int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y);
	InputInteger(&(pCh->job.nCode), 1, 6, x, y, false);
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);
	gotoxy(x + 3, y);
	printf("[%s]", pCh->job.szName);
}

// 【関数内容】
// 文字列をトリミングしてコピー（最初からnLen文字分）
// 【引数】
// pDest	: 【変更対象】コピー先文字列
// pSource	: 【参照用　】コピー元文字列
// nLen		: 【参照用　】○文字分
// 【戻り値】
// なし
void	Trim_And_Copy_String(char* pDest,const char* pSource, int nLen)
{
	strncpy(pDest, pSource, nLen);	// nLen文字コピー
	*(pDest + nLen) = '\0';			// コピー先の終端にヌル文字代入
}

// 【関数内容】
// 文字列をコピー（nStart番目からnLen文字分）
// 【引数】
// pDest	: 【変更対象】コピー先文字列
// pSource	: 【参照用　】コピー元文字列
// nStart	: 【参照用　】○番目から
// nLen		: 【参照用　】○文字分
// 【戻り値】
// なし
void Copy_String_From_Certain(char* pDest, const char* pSource, int nStart, int nLen)
{
	// --------------------
	// ローカル変数宣言
	// --------------------
	int cnt;													// ループカウンタ
	// --------------------
	// コピー
	// --------------------
	for (cnt = 0; cnt < nLen; cnt++)							// nLen文字コピーしたら終了
	{
		(*(pDest + cnt)) = (*(pSource + (nStart - 1) + cnt));	// コピー
		if (*(pDest + cnt) == '\0') return;						// コピー元にヌル文字があったら終了
	}
	(*(pDest + nLen)) = '\0';									// コピー先の最後にヌル文字代入
}