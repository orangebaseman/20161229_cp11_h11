// --------------------
// キャラクター削除シーン
// --------------------
#include	"conioex.h"
#include	"public.h"

// --------------------
// 疑似private関数宣言
// --------------------
void	DisplayCantDeleteMessage_DeleteMemberScene(int, int);
int		DisplayMasterMessage_DeleteMemberScene(int, int);
int		DisplayAndDeletePartyMember(tCharacter*, int*, int, int);

// --------------------
// 関数実装部
// --------------------

void	Execute_DeleteMemberScene(tCharacter* pCharacterList, int* pNum)
{
	int y = 2;
	clrscr();
	if ((*pNum) <= 1)
	{
		DisplayCantDeleteMessage_DeleteMemberScene(2, y);
		getchar();
		return;
	}
	y = DisplayMasterMessage_DeleteMemberScene(2, y);
	y = DisplayAndDeletePartyMember(pCharacterList, pNum, 2, y);
	getchar();
}
void	DisplayCantDeleteMessage_DeleteMemberScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("ここは　ひとりもの　には　むえんの　ばしょだよ"); y++;
	gotoxy(x, y); printf("さあ、かえった、かえった！"); y++;
	gotoxy(x, y); printf(""); y++;
}
int		DisplayMasterMessage_DeleteMemberScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("よう　ひさしぶりだな"); y++;
	gotoxy(x, y); printf("わかっている　なにも　いうな"); y++;
	gotoxy(x, y); printf(""); y++;
	gotoxy(x, y); printf("ここに　きたと　いうことは"); y++;
	gotoxy(x, y); printf("わかれを　つげたい　あいてが　いるのだろう"); y++;
	gotoxy(x, y); printf(""); y++;
	gotoxy(x, y); printf("いってみろ　どいつと　わかれたいんだ？"); y++;
	gotoxy(x, y); printf(""); y++;
	return y;
}
int		DisplayAndDeletePartyMember(tCharacter* pCharacterList, int* pNum, int x_start, int y_start)
{
	tCharacter* pCh = pCharacterList;
	int input;
	int x = x_start, y = y_start;
	int i;
	gotoxy(x, y); printf("┏━━━┳━━━━┓"); y++;
	gotoxy(x, y); printf("┃コード┃なまえ　┃"); y++;
	gotoxy(x, y); printf("┣━━━╋━━━━┫"); y++;
	pCh = pCh->next;
	i = 1;
	while (pCh != NULL)
	{
		gotoxy(x, y); printf("┃%6d┃%s┃", i, pCh->szName); y++;
		pCh = pCh->next;
		i++;
	}
	gotoxy(x, y); printf("┃　　 0┃やめます┃"); y++;
	gotoxy(x, y); printf("┗━━━┻━━━━┛"); y++;
	InputInteger(&input, 0, (*pNum) - 1, x, y, true); y++;
	y++;
	if (input == 0)
	{
		gotoxy(x, y); printf("そうか。では　またな"); y++;
		return y;
	}
	for (i = 0, pCh = pCharacterList; i < input; i++)
	{
		pCh = pCh->next;
	}
	gotoxy(x, y); printf("わかった。 %sには　おれから　うまくわかれを　つたえておこう", pCh->szName); y++;
	gotoxy(x, y); printf("またな"); y++;
	CharacterList_Delete(pCh);
	(*pNum)--;
	return y;
}
