// --------------------
// ���j���[�V�[��
// --------------------
#include	"conioex.h"
#include	"public.h"

// --------------------
// �^��private�֐��錾
// --------------------
int		DisplayMasterMessage_MenuScene(int, int);	// ���j���[�V�[��_��l�̃Z���t�\��
int		DisplayOptions_MenuScene(int, int);			// ���j���[�V�[��_�I�𕔕��\��

// --------------------
// �֐�������
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
	gotoxy(x, y); printf("���C�[�_�@�́@�����΁@�ց@�悤����");		y++;
	gotoxy(x, y); printf("�ǂ�ȁ@���悤���ł���");					y++;
	gotoxy(x, y);													y++;
	return y;

}
int		DisplayOptions_MenuScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("[1] �Ȃ��܁@���@���");					y++;
	gotoxy(x, y); printf("[2] �Ȃ��܁@���@�܂�������");				y++;
	gotoxy(x, y); printf("[3] �Ȃ��܁@�Ɓ@�킩���");				y++;
	gotoxy(x, y); printf("[4] �݂�Ȃ́@��������@�����ɂ�");		y++;
	gotoxy(x, y);													y++;
	gotoxy(x, y); printf("[0] ���悤�Ȃ�");							y++;
	gotoxy(x, y);													y++;

	return y;
}
