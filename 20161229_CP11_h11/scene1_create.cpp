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
	bool		isLast;
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
	tString*	pTextList_Master_MessageMaster;				// ���b�Z�[�W���X�g(�S�́j
	tString*	pTextList_Display_MessageMaster;			// ���b�Z�[�W���X�g�i�\�������j
	pTextList_Display_MessageMaster = StringList_New_Blank();
	// -------
	// �L�����N�^�[�쐬���@�ϐ�
	// ------
	tPoint2D	ptStart_CharacterCreate_Head= { 1, 11 };						// ���_�i����j
	tPoint2D	ptStart_CharacterCreate_Chara[MAX_NUMBER_OF_CHARACTERS - 1];	// ���_�i����j
	for (i = 0; i < MAX_NUMBER_OF_CHARACTERS - 1; i++)
	{
		ptStart_CharacterCreate_Chara[i].x = ptStart_CharacterCreate_Head.x
			+ MAX_CHARACTERS_OF_HERO_NAME + SIZE_OF_BORDER
			+ i * (MAX_CHARACTERS_OF_HERO_NAME + SIZE_OF_BORDER);
		ptStart_CharacterCreate_Chara[i].y = ptStart_CharacterCreate_Head.y;
	}
	// -------
	// �L�����N�^�[�쐬�⏕���@�ϐ�
	// ------
	tPoint2D	ptStart_CharacterCreate_Sub;	//
	int			nLen_CharacterCreate_Sub;		//
	int			nLines_CharacterCreate_Sub;		// �s��
	tArea		AreaW_CharacterCreate_Sub;		// Area(Window�S�́j
	tArea		AreaT_CharacterCreate_Sub;		// Area(Text�����j

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
	// --------
	// �g���̕\��
	// --------
	// �`�挻�݈ʒu�����_��
	ptCur_Draw = ptStart_MessageMaster;	
	// �r���E�C���h�E�̕\��
	AreaW_MessageMaster = DrawBorderWindow(&ptCur_Draw, true, nLen_MessageMaster, nLines_MessageMaster);
	// �����`��͈͎擾
	AreaT_MessageMaster = Area_Inside_BorderWindow(&AreaW_MessageMaster);
	// --------
	// ���b�Z�[�W�̍쐬
	// --------
	pCur_Str = StringList_New("�Ȃ��܂��@����тɁ@�Ȃ�̂ł���");					// �V�K�쐬
	pCur_Str = StringList_Add(pCur_Str, "�Ȃ�ɂ�@����тɁ@�Ȃ�܂����H", true);	// �ǉ�
	pTextList_Master_MessageMaster = StringList_First(pCur_Str);				// ���b�Z�[�W���X�g�i�}�X�^�j�ɑ��
	// ���b�Z�[�W���X�g(�\���p�j�ɁA���b�Z�[�W�T�C�Y�Ƀ��T�C�Y���đ��
	pTextList_Display_MessageMaster = 
		ResizeStringList_By_tArea(pTextList_Display_MessageMaster, pTextList_Master_MessageMaster, AreaT_MessageMaster, START_FROM_LAST, 1);
	// --------
	// ���b�Z�[�W�̕\��
	// --------
	DrawTextList_Plain(AreaT_MessageMaster, pTextList_Display_MessageMaster, &ptCur_Draw);

	// --------------------
	// �L�����N�^�[�쐬�l���@����
	// --------------------
	// �L�����N�^�[�l�����L�[�{�[�h����擾
	nAdd = InputInteger_pt(0, MAX_NUMBER_OF_CHARACTERS - (*pNumMember), &ptCur_Draw, true);

	msleep(500);
	// ���ǉ����Ȃ��Ȃ�V�[���I��
	if (nAdd <= 0) 
	{
		// �㏈��
		StringList_DeleteAll(pTextList_Display_MessageMaster);
		StringList_DeleteAll(pTextList_Master_MessageMaster);
		return;
	}

	// ----------
	// �}�X�^�[���b�Z�[�W�@�\�����e�X�V
	// ---------
	// ���݈ʒu���}�X�^���b�Z�[�W���X�g��
	pCur_Str = pTextList_Master_MessageMaster;
	// ��s�ǉ�
	pCur_Str = StringList_Add(pCur_Str, "", true);
	// ���b�Z�[�W�ǉ�
	pCur_Str = StringList_Add_Blank(pCur_Str, true);
	sprintf(pCur_Str->szText, "%2d�@�߂��@����тɁ@�Ȃ�̂ł���", nAdd);
	// ���b�Z�[�W���X�g(�\���p�j�ɁA���b�Z�[�W�T�C�Y�Ƀ��T�C�Y���đ��
	pTextList_Display_MessageMaster = 
		ResizeStringList_By_tArea(pTextList_Display_MessageMaster, pTextList_Master_MessageMaster, AreaT_MessageMaster, START_FROM_LAST, 1);
	// ���b�Z�[�W�\���G���A���N���A
	ClearArea(&AreaT_MessageMaster);
	// ���b�Z�[�W�\��
	DrawTextList_Plain(AreaT_MessageMaster, pTextList_Display_MessageMaster, &ptCur_Draw);
	// --------------------
	// �L�����N�^�[�쐬���@�`��
	// --------------------
	ptCur_Draw = ptStart_CharacterCreate_Head;
	DisplayStatusHeader_PT(&ptCur_Draw);
	for (i = 0; i < nAdd; i++)
	{
		ptCur_Draw = ptStart_CharacterCreate_Chara[i];
		isLast = (i == nAdd - 1) ? true : false;
		DisplayStatusBlank_pt(&ptCur_Draw, isLast);
	}
	// --------------------
	// �L�����N�^�[�쐬�⏕���@�`��
	// --------------------
	// �ϐ�������
	// ���_�@X���W�i�L�����N�^�[�쐬���@�Ō�̈��X���W�@�{�@�r���i���j�@�{�@�\���������@�{�@�r���i�E�j�@�{�@�S�p�X�y�[�X�j
	ptStart_CharacterCreate_Sub.x = ptStart_CharacterCreate_Chara[nAdd - 1].x + SIZE_OF_BORDER + MAX_CHARACTERS_OF_HERO_NAME + SIZE_OF_BORDER + SIZE_OF_ZENAKU_CHARACTER;
	// ���_�@X���W�i�L�����N�^�[�쐬����Y���W�j
	ptStart_CharacterCreate_Sub.y = ptStart_CharacterCreate_Head.y;
	// ���i�L�����N�^�[�쐬���E���S�āF�E�C���h�E���@+ �k������ - X���W�J�n�ʒu�j
	nLen_CharacterCreate_Sub = MAX_WIDTH_OF_WINDOW + SIZE_OF_NULL - ptStart_CharacterCreate_Sub.x;
	// ����
	nLines_CharacterCreate_Sub = 15;
	// �`��
	ptCur_Draw = ptStart_CharacterCreate_Sub;
	AreaW_CharacterCreate_Sub = DrawBorderWindow(&ptCur_Draw, false, nLen_CharacterCreate_Sub, nLines_CharacterCreate_Sub);
	// �����`��͈͎擾
	AreaT_CharacterCreate_Sub = Area_Inside_BorderWindow(&AreaW_CharacterCreate_Sub);

	for (i = 0; i < nAdd; i++)
	{
		// ----------
		// �}�X�^�[���b�Z�[�W�@�\�����e�X�V
		// ---------
		// ���݈ʒu���}�X�^���b�Z�[�W���X�g��
		pCur_Str = pTextList_Master_MessageMaster;
		// ��s�ǉ�
		pCur_Str = StringList_Add(pCur_Str, "", true);
		// ���b�Z�[�W�ǉ�
		pCur_Str = StringList_Add_Blank(pCur_Str, true);
		sprintf(pCur_Str->szText, "%2d�@�΂�߂́@���Ȃ��܂́@�ǂȂ��Ɂ@�Ȃ����܂���", i + 1);
		// ���b�Z�[�W���X�g(�\���p�j�ɁA���b�Z�[�W�T�C�Y�Ƀ��T�C�Y���đ��
		pTextList_Display_MessageMaster =
			ResizeStringList_By_tArea(pTextList_Display_MessageMaster, pTextList_Master_MessageMaster, AreaT_MessageMaster, START_FROM_LAST, 1);
		// ���b�Z�[�W�\���G���A���N���A
		ClearArea(&AreaT_MessageMaster);
		// ���b�Z�[�W�\��
		DrawTextList_Plain(AreaT_MessageMaster, pTextList_Display_MessageMaster, &ptCur_Draw);

		// 

		getchar();
	}
	

	
	// --------------------
	// �㏈��
	// --------------------
	StringList_DeleteAll(pTextList_Display_MessageMaster);
	StringList_DeleteAll(pTextList_Master_MessageMaster);

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
