// --------------------
// キャラクター更新シーン
// --------------------
#include	"conioex.h"
#include	"public.h"

// --------------------
// 疑似private関数宣言
// --------------------
int		DisplayMasterMessage_UpdateMemberScene(int, int);
int		DisplayAndUpdatePartyMember_UpdateMemberScene(tCharacter*, const tJob*, int, int, int);
int		DisplayBaseStatus_UpdateMemberScene(const tCharacter*, int, int);
int		DisplayCantUpdateMessage_UpdateMemberScene(int, int);

// --------------------
// 関数実装部
// --------------------

void	Execute_UpdateMemberScene(tCharacter* pCharacterList, const tJob* pJobList, int num)
{
	int x = 2, y = 2;
	clrscr();
	if (num <= 1)
	{
		DisplayCantUpdateMessage_UpdateMemberScene(x, y);
		getchar();
		return;
	}

	y = DisplayMasterMessage_UpdateMemberScene(x, y);
	y = DisplayAndUpdatePartyMember_UpdateMemberScene(pCharacterList, pJobList, num, x, y);

	getchar();
}
int		DisplayMasterMessage_UpdateMemberScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("ヒャハハハ てめえらの　ちからに");	y++;
	gotoxy(x, y); printf("ふまんは　ねーか？");					y++;
	gotoxy(x, y); printf("");					y++;
	gotoxy(x, y); printf("オレさまが　かいぞうを　してやるよ");	y++;
	gotoxy(x, y); printf("その　どきょうが　あるならな");		y++;
	gotoxy(x, y);												y++;
	gotoxy(x, y); printf("だれを　かいぞうして　ほしいんだ？");	y++;
	return y;
}
int		DisplayAndUpdatePartyMember_UpdateMemberScene(tCharacter* pCharacterList, const tJob* pJobList, int num, int x_start, int y_start)
{
	tCharacter* pCh = pCharacterList;
	tArea area;
	int input;
	int x = x_start, y = y_start;
	int x_end, y_end;
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
	InputInteger(&input, 0, num - 1, x, y, true); y++;
	y++;
	if (input == 0)
	{
		gotoxy(x, y); printf("チッ　ならば　おれの　まえから　うせろ"); y++;
		return y;
	}

	for (i = 0, pCh = pCharacterList; i < input; i++)
	{
		pCh = pCh->next;
	}
	clrscr(); y = 2;
	gotoxy(x, y); printf("%sの　どこを　かいぞう　したいんだ？", pCh->szName); y++;
	gotoxy(x, y); printf("┏━━━┳━━━━┓"); y++;
	gotoxy(x, y); printf("┃コード┃能　　力┃"); y++;
	gotoxy(x, y); printf("┣━━━╋━━━━┫"); y++;
	gotoxy(x, y); printf("┃     1┃なまえ　┃"); y++;
	gotoxy(x, y); printf("┃     2┃職　　業┃"); y++;
	gotoxy(x, y); printf("┃     3┃Ｈ　　Ｐ┃"); y++;
	gotoxy(x, y); printf("┃     4┃Ｓ　　Ｐ┃"); y++;
	gotoxy(x, y); printf("┃     5┃こうげき┃"); y++;
	gotoxy(x, y); printf("┃     6┃ぼうぎょ┃"); y++;
	gotoxy(x, y); printf("┃     7┃まほこう┃"); y++;
	gotoxy(x, y); printf("┃     8┃まほぼう┃"); y++;
	gotoxy(x, y); printf("┃     9┃すばやさ┃"); y++;
	gotoxy(x, y); printf("┃     0┃やめます┃"); y++;
	gotoxy(x, y); printf("┗━━━┻━━━━┛"); y++;
	gotoxy(x, y); printf(""); y++;
	DisplayStatusHeader(31, 3);
	DisplayBaseStatus_UpdateMemberScene(pCh, 43, 3);
	gotoxy(x, y);
	y = InputInteger(&input, 0, 9, x, y, true); y++;
	switch (input)
	{
	case 0:
		gotoxy(x, y); printf("チッ　ならば　おれの　まえから　うせろ"); y++;
		return y;
	case 1:
		gotoxy(x, y); printf("[なまえ　]"); InputString(pCh->szName, MAX_CHARACTERS_OF_HERO_NAME, x + 10, y); y++;
		break;
	case 2:
		gotoxy(x, y); printf("[職　　業]");
		DisplayJobList(pJobList, x + 10 + 14, y, &x_end, &y_end);
		InputJob(pCh, pJobList, x + 10, y);
		//ClearJobList(x + 10 + 14, y, x_end, y_end);
		area = { { x + 10 + 14 , y}, {x_end, y_end} };
		ClearArea(&area);
		y++;
		break;
	case 3:
		gotoxy(x, y); printf("[Ｈ　　Ｐ]"); InputInteger(&(pCh->nHP_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 4:
		gotoxy(x, y); printf("[Ｓ　　Ｐ]"); InputInteger(&(pCh->nSP_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 5:
		gotoxy(x, y); printf("[こうげき]"); InputInteger(&(pCh->nAtk_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 6:
		gotoxy(x, y); printf("[ぼうぎょ]"); InputInteger(&(pCh->nDef_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 7:
		gotoxy(x, y); printf("[まほこう]"); InputInteger(&(pCh->nMAtk_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 8:
		gotoxy(x, y); printf("[まほぼう]"); InputInteger(&(pCh->nMDef_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 9:
		gotoxy(x, y); printf("[すばやさ]"); InputInteger(&(pCh->nSpd_Base), 1, 9, x + 10, y, true); y++;
		break;
	default:
		return y;
	}
	CalculateCharacterStatus(pCh);
	DisplayBaseStatus_UpdateMemberScene(pCh, 43, 3);
	gotoxy(x, y); printf("ヒャハハハ　…　どうだ　みちがえただろう"); y++;
	gotoxy(x, y); printf("また　こいよ"); y++;
	return y;
}
int		DisplayBaseStatus_UpdateMemberScene(const tCharacter* pCh, int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("━┳"); y++;
	gotoxy(x, y); printf(" -┃"); y++;
	gotoxy(x, y); printf("%2d┃", pCh->job.nCode); y++;
	gotoxy(x, y); printf("─╂"); y++;
	gotoxy(x, y); printf("%2d┃", pCh->nHP_Base); y++;
	gotoxy(x, y); printf("%2d┃", pCh->nSP_Base); y++;
	gotoxy(x, y); printf("─╂"); y++;
	gotoxy(x, y); printf("%2d┃", pCh->nAtk_Base); y++;
	gotoxy(x, y); printf("%2d┃", pCh->nDef_Base); y++;
	gotoxy(x, y); printf("─╂"); y++;
	gotoxy(x, y); printf("%2d┃", pCh->nMAtk_Base); y++;
	gotoxy(x, y); printf("%2d┃", pCh->nMDef_Base); y++;
	gotoxy(x, y); printf("─╂"); y++;
	gotoxy(x, y); printf("%2d┃", pCh->nSpd_Base); y++;
	gotoxy(x, y); printf("━┻"); y++;

	x = x_start + 4;
	y = y_start;
	gotoxy(x, y); printf("━━━━┓"); y++;
	gotoxy(x, y); printf("%s┃", pCh->szName); y++;
	gotoxy(x, y); printf("%s┃", pCh->job.szName); y++;
	gotoxy(x, y); printf("────┨"); y++;
	gotoxy(x, y); printf("%8d┃", pCh->nHP); y++;
	gotoxy(x, y); printf("%8d┃", pCh->nSP); y++;
	gotoxy(x, y); printf("────┨"); y++;
	gotoxy(x, y); printf("%8d┃", pCh->nAtk); y++;
	gotoxy(x, y); printf("%8d┃", pCh->nDef); y++;
	gotoxy(x, y); printf("────┨"); y++;
	gotoxy(x, y); printf("%8d┃", pCh->nMAtk); y++;
	gotoxy(x, y); printf("%8d┃", pCh->nMDef); y++;
	gotoxy(x, y); printf("────┨"); y++;
	gotoxy(x, y); printf("%8d┃", pCh->nSpd); y++;
	gotoxy(x, y); printf("━━━━┛"); y++;
	return y;
}
int		DisplayCantUpdateMessage_UpdateMemberScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("んだよ　てめえ　ひとりしか　いないじゃねーか");	y++;
	gotoxy(x, y); printf("でなおして　きな");								y++;
	gotoxy(x, y);															y++;
	return y;
}
