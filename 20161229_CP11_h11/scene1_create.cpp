// --------------------
// �L�����N�^�[�쐬�V�[��
// --------------------
#include	"conioex.h"
#include	"public.h"

// --------------------
// �^��private�֐��錾
// --------------------
int		DisplayMasterMessage_CreateScene(const int*, int*, int, int);					// �L�����N�^�[�쐬�V�[��_�V�[�����s
int		DisplayAndCreatePartyMember_CreateScene(tCharacter*, const tJob*, int, int);	// �L�����N�^�[�쐬�V�[��_�\���i�}�X�^���b�Z�[�W�j
int		DisplayCantAddMessage_CreateScene(int, int);									// �L�����N�^�[�쐬�V�[��_

// --------------------
// �֐�������
// --------------------
// �y�֐����e�z
// �L�����N�^�[�쐬�V�[��_�V�[�����s
// �y�����z
// pCharacterList		: �y�ύX�Ώہz�L�����N�^�[���X�g
// pBuiltInCharaList	: �y�Q�Ɨp�@�z�g�ݍ��݃L�����N�^�[���X�g
// pJobList				: �y�Q�Ɨp�@�z�E�ƈꗗ
// pNum					: �y�ύX�Ώہz�L�����N�^�[�l��
// nNumBuiltIn			: �y�Q�Ɨp�@�z�g�ݍ��݃L�����N�^�[�l��
// �y�߂�l�z
// �Ȃ�
void	Execute_CreateScene(tCharacter* pCharacterList, const tCharacter* pBuiltInCharaList, const tJob* pJobList, int* pNumMember, int nNumBuiltIn)
{
	// --------------------
	// ���[�J���ϐ��錾�A������
	// --------------------
	int x, y = 2, tempY;				// �`��XY���W
	tPoint2D	ptCur_Draw = { 1, 1 };	// �`�挻�݈ʒu
	tString*	pCur_Str;				// StringList�̌��݈ʒu
	int i;								// ���[�v�J�E���^
	int nAdd = 1;						// �쐬�i�ǉ��j�l��
	tCharacter* pCh = pCharacterList;	// �L�����N�^�[�\���̃|�C���^
	// -------
	// �}�X�^���b�Z�[�W���@�ϐ�
	// ------
	tPoint2D	ptStart_MessageMaster = { 1, 1 };			// ���_�i����j
	int			nLen_MessageMaster = MAX_WIDTH_OF_WINDOW;	// ����
	int			nLines_MessageMaster = 9;					// �s��
	tArea		AreaW_MessageMaster;						// Area(Window�S�́j
	tArea		AreaT_MessageMaster;						// Area(Text�����j
	tString*	pTextList_MessageMaster;					// �e�L�X�g���X�g
	// -------
	// ��ʃN���A
	// ------
	clrscr();
	// ���l���`�F�b�N:�@����l���Ȃ�΃G���[�\�������ăV�[���I��
	if ((*pNumMember) >= MAX_NUMBER_OF_CHARACTERS)
	{
		DisplayCantAddMessage_CreateScene(2, 2);
		getchar();
		return;
	}
	// --------------------
	// �}�X�^���b�Z�[�W�@�\��
	// --------------------
	// �g���̕\��
	ptCur_Draw = ptStart_MessageMaster;
	AreaW_MessageMaster = DrawBorderWindow(&ptCur_Draw, true, nLen_MessageMaster, nLines_MessageMaster);
	AreaT_MessageMaster = Area_Inside_BorderWindow(&AreaW_MessageMaster);

	// �}�X�^���b�Z�[�W�̍쐬
	// ���P�s�ŕ�����̑���ƒǉ���x�ɍs���֐��̎���
	pTextList_MessageMaster = StringList_New();
	pCur_Str = pTextList_MessageMaster;
	strcpy(pCur_Str->szText, "�Ȃ��܂��@����тɁ@�Ȃ�̂ł���");
	pCur_Str = StringList_Add(pCur_Str, "�Ȃ�ɂ�@����тɁ@�Ȃ�܂����H", true);
	pTextList_MessageMaster = StringList_First(pCur_Str);

	// �}�X�^���b�Z�[�W�̕`��
	// �����Œ���while���񂷂��A���S�ɕ\�����������͊֐����g�����B
	ptCur_Draw = AreaT_MessageMaster.start;
	pCur_Str = pTextList_MessageMaster;

	while (pCur_Str != NULL)
	{
		gotoxy_pt(ptCur_Draw);
		printf(pCur_Str->szText);
		if (ptCur_Draw.y <= AreaT_MessageMaster.end.y && pTextList_MessageMaster->next != NULL)
		{
			ptCur_Draw.y += 1;
			pCur_Str = pCur_Str->next;
		}
		else
		{
			break;
		}
	}
	// �㏈��
	StringList_DeleteAll(pTextList_MessageMaster);

	// --------------------
	// �L�����N�^�[�쐬�l���@����
	// --------------------
	//y = DisplayMasterMessage_CreateScene(pNumMember, &nAdd, 2, 2);
	ClearArea(&AreaT_MessageMaster);

	// ���ǉ����Ȃ��Ȃ�V�[���I��
	if (nAdd <= 2) return;
	// --------------------
	// �L�����N�^�[�쐬��
	// --------------------
	DisplayStatusHeader(2, y);
	for (i = 0; i < nAdd; i++)
	{
		DisplayStatusBlank(2 + (i + 1) * 10, y, i == nAdd - 1);
	}


		// �L�����N�^�[�\���́@�V�K�쐬
		//pCh = CharacterList_Add(pCh, pNumMember, true);
		// �`��X���W
		//x = 2 + i * 23;
		// 
		// 
		// �J�X�^���L�����N�^�[
		//tempY = DisplayAndCreatePartyMember_CreateScene(pCh, pJobList, x, y);
	
	//y = tempY;

	getchar();
}
// �y�֐����e�z
// �L�����N�^�[�쐬�V�[��_�\���i�}�X�^���b�Z�[�W�j
// �y�����z
// pNum		:�y�ύX�Ώہz���݂̃p�[�e�B�l��
// pAdd		:�y�ύX�Ώہz�ǉ��l���i�쐬�l���j
// x_start	:�y�Q�Ɨp�@�z�J�nX���W
// y_start	:�y�Q�Ɨp�@�z�J�nY���W
// �y�߂�l�z
// ����Y���W
int		DisplayMasterMessage_CreateScene(const int* pNum, int* pAdd, int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("�Ȃ��܂��@����тɁ@�Ȃ�̂ł���");	y++;
	gotoxy(x, y); printf("�Ȃ�ɂ�@����тɁ@�Ȃ�܂����H");	y++;
	gotoxy(x, y); InputInteger(pAdd, 0, MAX_NUMBER_OF_CHARACTERS - (*pNum), x, y, true);
	gotoxy(x, y);											y++;
	return y;
}
// �y�֐����e�z
// �L�����N�^�[�쐬�V�[��_�\���i�쐬���j�{�L�����N�^�[�쐬
// �y�����z
// pCh			:�y�ύX�Ώہz�쐬����L�����N�^�[�\����
// pJobList		:�y�Q�Ɨp�@�z�E�ƈꗗ
// x_start		:�y�Q�Ɨp�@�z�J�nX���W
// y_start		:�y�Q�Ɨp�@�z�J�nY���W
// �y�߂�l�z
// ����Y���W
int		DisplayAndCreatePartyMember_CreateScene(tCharacter* pCh, const tJob* pJobList, int x_start, int y_start)
{
	// --------------------
	// ���[�J���ϐ��錾, ������
	// --------------------
	int x = x_start, y = y_start;	// �`��ʒu
	int tempY;						// 
	int x_end, y_end;				// �`��I���ʒu�i�j

	gotoxy(x, y); printf(""); y++;
	tempY = y;

	// --------------------
	//�@�g�ݍ��݃L�����N�^�[�I��
	// --------------------
	//gotoxy(x, y); printf("��������������������"); y++;
	//gotoxy(x, y); printf("���R�[�h���Ȃ܂��@��"); y++;
	//gotoxy(x, y); printf("��������������������"); y++;

	// --------------------
	//�@�J�X�^���L�����N�^�[�@�X�e�[�^�X����
	// --------------------
	
	

	//// �Ȃ܂��@����
	//gotoxy(x, y);
	//printf("[�Ȃ܂��@]");
	//InputString(pCh->szName, MAX_CHARACTERS_OF_HERO_NAME - 1, x + 10, y);
	//y++;

	//gotoxy(x, y); printf("[�E�@�@��]");
	//DisplayJobList(pJobList, x + 10 + 14, y, &x_end, &y_end);
	//InputJob(pCh, pJobList, x + 10, y);
	//ClearJobList(x + 10 + 14, y, x_end, y_end);
	//y++;
	//gotoxy(x, y); printf("[�g�@�@�o]"); InputInteger(&(pCh->nHP_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[�r�@�@�o]"); InputInteger(&(pCh->nSP_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[��������]"); InputInteger(&(pCh->nAtk_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[�ڂ�����]"); InputInteger(&(pCh->nDef_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[�܂ق���]"); InputInteger(&(pCh->nMAtk_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[�܂قڂ�]"); InputInteger(&(pCh->nMDef_Base), 1, 9, x + 10, y, true); y++;
	//gotoxy(x, y); printf("[���΂₳]"); InputInteger(&(pCh->nSpd_Base), 1, 9, x + 10, y, true); y++;
	//CalculateCharacterStatus(pCh);
	return y;
}
// �y�֐����e�z
// �L�����N�^�[�쐬�V�[��_�\���i�ǉ��s���j
// �y�����z
// pCharacterList	: �y�ύX�Ώہz�L�����N�^�[���X�g
// pJobList			: �y�{���p�z�@�E�ƈꗗ
// pNum				: �y�ύX�Ώہz�L�����N�^�[�l��
// �y�߂�l�z
// �Ȃ�
int		DisplayCantAddMessage_CreateScene(int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y); printf("���ꂢ���傤�@�Ȃ��܂��@��Ă����܂����B");	y++;
	gotoxy(x, y); printf("�܂��@���������������B");						y++;
	gotoxy(x, y);													y++;
	return y;
}
