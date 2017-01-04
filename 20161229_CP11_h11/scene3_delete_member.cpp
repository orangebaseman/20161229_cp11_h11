// --------------------
// �L�����N�^�[�폜�V�[��
// --------------------
#include	"conioex.h"
#include	"public.h"

// --------------------
// �^��private�֐��錾
// --------------------
void	DisplayCantDeleteMessage_DeleteMemberScene(int, int);
int		DisplayMasterMessage_DeleteMemberScene(int, int);
int		DisplayAndDeletePartyMember(tCharacter*, int*, int, int);

// --------------------
// �֐�������
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
	gotoxy(x, y); printf("�����́@�ЂƂ���́@�ɂ́@�ނ���́@�΂��傾��"); y++;
	gotoxy(x, y); printf("�����A���������A���������I"); y++;
	gotoxy(x, y); printf(""); y++;
}
int		DisplayMasterMessage_DeleteMemberScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("�悤�@�Ђ����Ԃ肾��"); y++;
	gotoxy(x, y); printf("�킩���Ă���@�Ȃɂ��@������"); y++;
	gotoxy(x, y); printf(""); y++;
	gotoxy(x, y); printf("�����Ɂ@�����Ɓ@�������Ƃ�"); y++;
	gotoxy(x, y); printf("�킩����@�������@�����Ă��@����̂��낤"); y++;
	gotoxy(x, y); printf(""); y++;
	gotoxy(x, y); printf("�����Ă݂�@�ǂ��Ɓ@�킩�ꂽ���񂾁H"); y++;
	gotoxy(x, y); printf(""); y++;
	return y;
}
int		DisplayAndDeletePartyMember(tCharacter* pCharacterList, int* pNum, int x_start, int y_start)
{
	tCharacter* pCh = pCharacterList;
	int input;
	int x = x_start, y = y_start;
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
	InputInteger(&input, 0, (*pNum) - 1, x, y, true); y++;
	y++;
	if (input == 0)
	{
		gotoxy(x, y); printf("�������B�ł́@�܂���"); y++;
		return y;
	}
	for (i = 0, pCh = pCharacterList; i < input; i++)
	{
		pCh = pCh->next;
	}
	gotoxy(x, y); printf("�킩�����B %s�ɂ́@���ꂩ��@���܂��킩����@�����Ă�����", pCh->szName); y++;
	gotoxy(x, y); printf("�܂���"); y++;
	CharacterList_Delete(pCh);
	(*pNum)--;
	return y;
}
