// --------------------
// �L�����N�^�[�\���V�[��
// --------------------
#include	"conioex.h"
#include	"public.h"

// --------------------
// �^��private�֐��錾
// --------------------
int		DisplayMasterMessage_ShowMemberScene(int, int);
int		DisplayPartyMembers_ShowMemberScene(const tCharacter*, int, int);
int		DisplayMember_ShowMemberScene(const tCharacter*, int, int);

// --------------------
// �֐�������
// --------------------

void	Execute_ShowMemberScene(const tCharacter* pCharacterList)
{
	int y;
	clrscr();
	y = DisplayMasterMessage_ShowMemberScene(2, 2);
	y = DisplayPartyMembers_ShowMemberScene(pCharacterList, 4, y);
	getchar();
}
int		DisplayMasterMessage_ShowMemberScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("�₠�@�݂�Ȃ̂�������@�����ɂ񂷂�񂾂�");	y++;
	gotoxy(x, y); printf("�ǂ�@�݂��ā@�����Ȃ���");					y++;
	gotoxy(x, y);														y++;
	return y;
}
int		DisplayPartyMembers_ShowMemberScene(const tCharacter* pCharacterList, int x_start, int y_start)
{
	int x = x_start, y = y_start;
	const tCharacter* pCh = pCharacterList;

	DisplayStatusHeader(x, y);
	x += 2;

	while (pCh != NULL)
	{
		x += 10;
		DisplayMember_ShowMemberScene(pCh, x, y);
		pCh = pCh->next;
	}
	return y;
}
int		DisplayMember_ShowMemberScene(const tCharacter* pCh, int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("��������"); (pCh->next != NULL) ? printf("��") : printf("��"); y++;
	gotoxy(x, y); printf("%s��", pCh->szName); y++;
	gotoxy(x, y); printf("%s��", pCh->job.szName); y++;
	gotoxy(x, y); printf("��������"); (pCh->next != NULL) ? printf("��") : printf("��"); y++;
	gotoxy(x, y); printf("%8d��", pCh->nHP); y++;
	gotoxy(x, y); printf("%8d��", pCh->nSP); y++;
	gotoxy(x, y); printf("��������"); (pCh->next != NULL) ? printf("��") : printf("��"); y++;
	gotoxy(x, y); printf("%8d��", pCh->nAtk); y++;
	gotoxy(x, y); printf("%8d��", pCh->nDef); y++;
	gotoxy(x, y); printf("��������"); (pCh->next != NULL) ? printf("��") : printf("��"); y++;
	gotoxy(x, y); printf("%8d��", pCh->nMAtk); y++;
	gotoxy(x, y); printf("%8d��", pCh->nMDef); y++;
	gotoxy(x, y); printf("��������"); (pCh->next != NULL) ? printf("��") : printf("��"); y++;
	gotoxy(x, y); printf("%8d��", pCh->nSpd); y++;
	gotoxy(x, y); printf("��������"); (pCh->next != NULL) ? printf("��") : printf("��"); y++;
	return y;
}