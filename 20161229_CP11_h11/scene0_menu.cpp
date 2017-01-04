// --------------------
// メニューシーン
// --------------------
#include	"conioex.h"
#include	"public.h"

// --------------------
// 疑似private関数宣言
// --------------------
int		DisplayMasterMessage_MenuScene(int, int);	// メニューシーン_主人のセリフ表示
int		DisplayOptions_MenuScene(int, int);			// メニューシーン_選択部分表示

// --------------------
// 関数実装部
// --------------------
void	Execute_MenuScene(int* pMenu)
{
	int y;
	clrscr();
	y = DisplayMasterMessage_MenuScene(2, 2);
	y = DisplayOptions_MenuScene(5, y);
	y = InputInteger(pMenu, 0, 4, 5, y, false);
}
int		DisplayMasterMessage_MenuScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("ルイーダ　の　さかば　へ　ようこそ");		y++;
	gotoxy(x, y); printf("どんな　ごようじですか");					y++;
	gotoxy(x, y);													y++;
	return y;

}
int		DisplayOptions_MenuScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("[1] なかま　を　よぶ");					y++;
	gotoxy(x, y); printf("[2] なかま　を　まかいぞう");				y++;
	gotoxy(x, y); printf("[3] なかま　と　わかれる");				y++;
	gotoxy(x, y); printf("[4] みんなの　ちからを　かくにん");		y++;
	gotoxy(x, y);													y++;
	gotoxy(x, y); printf("[0] さようなら");							y++;
	gotoxy(x, y);													y++;

	return y;
}
