// --------------------
// �L�����N�^�[�X�V�V�[��
// --------------------
#include	"conioex.h"
#include	"public.h"

// --------------------
// �^��private�֐��錾
// --------------------
int		DisplayMasterMessage_UpdateMemberScene(int, int);
int		DisplayAndUpdatePartyMember_UpdateMemberScene(tCharacter*, const tJob*, int, int, int);
int		DisplayBaseStatus_UpdateMemberScene(const tCharacter*, int, int);
int		DisplayCantUpdateMessage_UpdateMemberScene(int, int);

// --------------------
// �֐�������
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
	gotoxy(x, y); printf("�q���n�n�n �Ă߂���́@�������");	y++;
	gotoxy(x, y); printf("�ӂ܂�́@�ˁ[���H");					y++;
	gotoxy(x, y); printf("");					y++;
	gotoxy(x, y); printf("�I�����܂��@�����������@���Ă���");	y++;
	gotoxy(x, y); printf("���́@�ǂ��傤���@����Ȃ��");		y++;
	gotoxy(x, y);												y++;
	gotoxy(x, y); printf("������@�����������ā@�ق����񂾁H");	y++;
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
	gotoxy(x, y); printf("��������������������"); y++;
	gotoxy(x, y); printf("���R�[�h���Ȃ܂��@��"); y++;
	gotoxy(x, y); printf("��������������������"); y++;
	pCh = pCh->next;
	i = 1;
	while (pCh != NULL)
	{
		gotoxy(x, y); printf("��%6d��%s��", i, pCh->szName); y++;
		pCh = pCh->next;
		i++;
	}
	gotoxy(x, y); printf("���@�@ 0����߂܂���"); y++;
	gotoxy(x, y); printf("��������������������"); y++;
	InputInteger(&input, 0, num - 1, x, y, true); y++;
	y++;
	if (input == 0)
	{
		gotoxy(x, y); printf("�`�b�@�Ȃ�΁@����́@�܂�����@������"); y++;
		return y;
	}

	for (i = 0, pCh = pCharacterList; i < input; i++)
	{
		pCh = pCh->next;
	}
	clrscr(); y = 2;
	gotoxy(x, y); printf("%s�́@�ǂ����@���������@�������񂾁H", pCh->szName); y++;
	gotoxy(x, y); printf("��������������������"); y++;
	gotoxy(x, y); printf("���R�[�h���\�@�@�̈́�"); y++;
	gotoxy(x, y); printf("��������������������"); y++;
	gotoxy(x, y); printf("��     1���Ȃ܂��@��"); y++;
	gotoxy(x, y); printf("��     2���E�@�@�Ƅ�"); y++;
	gotoxy(x, y); printf("��     3���g�@�@�o��"); y++;
	gotoxy(x, y); printf("��     4���r�@�@�o��"); y++;
	gotoxy(x, y); printf("��     5������������"); y++;
	gotoxy(x, y); printf("��     6���ڂ����儫"); y++;
	gotoxy(x, y); printf("��     7���܂ق�����"); y++;
	gotoxy(x, y); printf("��     8���܂قڂ���"); y++;
	gotoxy(x, y); printf("��     9�����΂₳��"); y++;
	gotoxy(x, y); printf("��     0����߂܂���"); y++;
	gotoxy(x, y); printf("��������������������"); y++;
	gotoxy(x, y); printf(""); y++;
	DisplayStatusHeader(31, 3);
	DisplayBaseStatus_UpdateMemberScene(pCh, 43, 3);
	gotoxy(x, y);
	y = InputInteger(&input, 0, 9, x, y, true); y++;
	switch (input)
	{
	case 0:
		gotoxy(x, y); printf("�`�b�@�Ȃ�΁@����́@�܂�����@������"); y++;
		return y;
	case 1:
		gotoxy(x, y); printf("[�Ȃ܂��@]"); InputString(pCh->szName, MAX_CHARACTERS_OF_HERO_NAME, x + 10, y); y++;
		break;
	case 2:
		gotoxy(x, y); printf("[�E�@�@��]");
		DisplayJobList(pJobList, x + 10 + 14, y, &x_end, &y_end);
		InputJob(pCh, pJobList, x + 10, y);
		//ClearJobList(x + 10 + 14, y, x_end, y_end);
		area = { { x + 10 + 14 , y}, {x_end, y_end} };
		ClearArea(&area);
		y++;
		break;
	case 3:
		gotoxy(x, y); printf("[�g�@�@�o]"); InputInteger(&(pCh->nHP_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 4:
		gotoxy(x, y); printf("[�r�@�@�o]"); InputInteger(&(pCh->nSP_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 5:
		gotoxy(x, y); printf("[��������]"); InputInteger(&(pCh->nAtk_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 6:
		gotoxy(x, y); printf("[�ڂ�����]"); InputInteger(&(pCh->nDef_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 7:
		gotoxy(x, y); printf("[�܂ق���]"); InputInteger(&(pCh->nMAtk_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 8:
		gotoxy(x, y); printf("[�܂قڂ�]"); InputInteger(&(pCh->nMDef_Base), 1, 9, x + 10, y, true); y++;
		break;
	case 9:
		gotoxy(x, y); printf("[���΂₳]"); InputInteger(&(pCh->nSpd_Base), 1, 9, x + 10, y, true); y++;
		break;
	default:
		return y;
	}
	CalculateCharacterStatus(pCh);
	DisplayBaseStatus_UpdateMemberScene(pCh, 43, 3);
	gotoxy(x, y); printf("�q���n�n�n�@�c�@�ǂ����@�݂����������낤"); y++;
	gotoxy(x, y); printf("�܂��@������"); y++;
	return y;
}
int		DisplayBaseStatus_UpdateMemberScene(const tCharacter* pCh, int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("����"); y++;
	gotoxy(x, y); printf(" -��"); y++;
	gotoxy(x, y); printf("%2d��", pCh->job.nCode); y++;
	gotoxy(x, y); printf("����"); y++;
	gotoxy(x, y); printf("%2d��", pCh->nHP_Base); y++;
	gotoxy(x, y); printf("%2d��", pCh->nSP_Base); y++;
	gotoxy(x, y); printf("����"); y++;
	gotoxy(x, y); printf("%2d��", pCh->nAtk_Base); y++;
	gotoxy(x, y); printf("%2d��", pCh->nDef_Base); y++;
	gotoxy(x, y); printf("����"); y++;
	gotoxy(x, y); printf("%2d��", pCh->nMAtk_Base); y++;
	gotoxy(x, y); printf("%2d��", pCh->nMDef_Base); y++;
	gotoxy(x, y); printf("����"); y++;
	gotoxy(x, y); printf("%2d��", pCh->nSpd_Base); y++;
	gotoxy(x, y); printf("����"); y++;

	x = x_start + 4;
	y = y_start;
	gotoxy(x, y); printf("����������"); y++;
	gotoxy(x, y); printf("%s��", pCh->szName); y++;
	gotoxy(x, y); printf("%s��", pCh->job.szName); y++;
	gotoxy(x, y); printf("����������"); y++;
	gotoxy(x, y); printf("%8d��", pCh->nHP); y++;
	gotoxy(x, y); printf("%8d��", pCh->nSP); y++;
	gotoxy(x, y); printf("����������"); y++;
	gotoxy(x, y); printf("%8d��", pCh->nAtk); y++;
	gotoxy(x, y); printf("%8d��", pCh->nDef); y++;
	gotoxy(x, y); printf("����������"); y++;
	gotoxy(x, y); printf("%8d��", pCh->nMAtk); y++;
	gotoxy(x, y); printf("%8d��", pCh->nMDef); y++;
	gotoxy(x, y); printf("����������"); y++;
	gotoxy(x, y); printf("%8d��", pCh->nSpd); y++;
	gotoxy(x, y); printf("����������"); y++;
	return y;
}
int		DisplayCantUpdateMessage_UpdateMemberScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("�񂾂�@�Ă߂��@�ЂƂ肵���@���Ȃ�����ˁ[��");	y++;
	gotoxy(x, y); printf("�łȂ����ā@����");								y++;
	gotoxy(x, y);															y++;
	return y;
}
