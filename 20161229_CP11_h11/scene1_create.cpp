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
	tPoint2D	ptCur_Draw_Sub = { 1, 1 };
	tString*	pCur_Str;				// StringList�̌��݈ʒu
	const tCharacter*	pCur_Chr_S;		// CharacterList�̌��݈ʒu
	tCharacter*	pCur_Chr_D;				// 
	bool		isLast;					// �Ōォ�ǂ���
	int			i, j;						// ���[�v�J�E���^
	int			nCharacter_Selected;	// �I���L����
	int			nAdd = 1;				// �쐬�i�ǉ��j�l��
	tCharacter* pCh = pCharacterList;	// �L�����N�^�[�\���̃|�C���^
	// -------
	// �}�X�^���b�Z�[�W���@�ϐ�
	// ------
	tPoint2D	ptStart_MessageMaster = { 1, 1 };				// ���_�i����j
	int			nLen_MessageMaster = MAX_WIDTH_OF_WINDOW;		// ����
	int			nLines_MessageMaster = 9;						// �s��
	tArea		AreaW_MessageMaster;							// Area(Window�S�́j
	tArea		AreaT_MessageMaster;							// Area(Text�����j
	tString*	pTextList_Master_MessageMaster = NULL;			// ���b�Z�[�W���X�g(�S�́j
	tString*	pTextList_Display_MessageMaster = NULL;			// ���b�Z�[�W���X�g�i�\�������j
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
	tPoint2D	ptStart_CharacterCreate_Sub;						//
	tPoint2D	ptStart_JobList;									// JobList�@�\���ʒu
	int			nLen_CharacterCreate_Sub;							//
	int			nLines_CharacterCreate_Sub;							// �s��
	tArea		AreaW_CharacterCreate_Sub;							// Area(Window�S�́j
	tArea		AreaT_CharacterCreate_Sub;							// Area(Text�����j						
	tString*	pTextList_Master_CharacterCreate_Sub = NULL;		// ���b�Z�[�W���X�g(�S�́j
	tString*	pTextList_Display_CharacterCreate_Sub = NULL;		// ���b�Z�[�W���X�g�i�\�������j
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
		StringList_DeleteAll(pTextList_Display_CharacterCreate_Sub);
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
		// �J�X�^������/�g�ݍ��݃L�����N�^�[�@�I��
		// �⏕�E�C���h�E�ɑI�����\��
		// ---------
		ptCur_Draw = ptStart_CharacterCreate_Sub;

		StringList_DeleteAll(pTextList_Master_CharacterCreate_Sub);

		pCur_Str = StringList_New_Blank();
		sprintf(pCur_Str->szText, "%2d�@�΂�߂̂��Ȃ��܂́H", i + 1);
		pCur_Str = StringList_Add(pCur_Str, "��������������������", true);;
		pCur_Str = StringList_Add(pCur_Str, "���R�[�h���Ȃ܂��@��", true);
		pCur_Str = StringList_Add(pCur_Str, "��������������������", true);
		
		j = 1;
		pCur_Chr_S = pBuiltInCharaList;
		while (1)
		{
			pCur_Str = StringList_Add_Blank(pCur_Str, true);
			sprintf(pCur_Str->szText, "���@�@%2d��%s��", j, pCur_Chr_S->szName);
			if (pCur_Chr_S->next != NULL)
			{
				pCur_Chr_S = pCur_Chr_S->next;
				j++;
			}
			else
			{
				break;
			}
		}
		pCur_Str = StringList_Add(pCur_Str, "���@�@ 0�����Ԃ�ń�", true);
		pCur_Str = StringList_Add(pCur_Str, "��������������������", true);

		pTextList_Master_CharacterCreate_Sub = StringList_First(pCur_Str);

		// ���b�Z�[�W���X�g(�\���p�j�ɁA���b�Z�[�W�T�C�Y�Ƀ��T�C�Y���đ��
		pTextList_Display_CharacterCreate_Sub =
			ResizeStringList_By_tArea(pTextList_Display_CharacterCreate_Sub, pTextList_Master_CharacterCreate_Sub, AreaT_CharacterCreate_Sub, START_FROM_LAST, 1);
		// ���b�Z�[�W�\���G���A���N���A
		ClearArea(&AreaT_CharacterCreate_Sub);
		// ���b�Z�[�W�\��
		DrawTextList_Plain(AreaT_CharacterCreate_Sub, pTextList_Display_CharacterCreate_Sub, &ptCur_Draw);

		gotoxy_pt(ptCur_Draw);
		nCharacter_Selected = InputInteger_pt(0, j, &ptCur_Draw, true);

		msleep(500);

		// --------------------
		// �L�����N�^�[���̓���
		// --------------------
		if (nCharacter_Selected > 0)
		{
			// --------------------
			// �g�ݍ��݃L�����N�^�[
			// --------------------
			// --------------------
			// �p�[�e�B�����o�[�̒ǉ�
			// --------------------
			// �g�ݍ��݃L�����N�^�[���X�g����A�ǂݍ��݁i�I��ԍ�-1��@���ւɂ܂킹�ΊY���L�����N�^�[�I���j
			pCur_Chr_S = pBuiltInCharaList;
			for (j = 1; j < nCharacter_Selected; j++)
			{
				pCur_Chr_S = pCur_Chr_S->next;
			}
			// �p�[�e�B�����o�[�ɒǉ��i�p�[�e�B�񃁃��o�[�l�������킹�čX�V
			pCur_Chr_D = CharacterList_Add(pCharacterList, pCur_Chr_S, pNumMember, true);
			// --------------------
			// �`��
			// --------------------
			// �`����W
			ptCur_Draw.x = ptStart_CharacterCreate_Chara[i].x + SIZE_OF_BORDER; // �`��J�n�ʒu�@�{�@�r���i���j
			ptCur_Draw.y = ptStart_CharacterCreate_Chara[i].y + NEXT_LINE;		// �`��J�n�ʒu�@�́@���̍s
			// �Ȃ܂�
			gotoxy_pt(ptCur_Draw);				// �ړ�
			printf(pCur_Chr_D->szName);			// �`��
			// �E��
			ptCur_Draw.y += NEXT_LINE;			// ���s
			gotoxy_pt(ptCur_Draw);				// �ړ�
			printf(pCur_Chr_D->job.szName);		// �`��
			// ���s
			ptCur_Draw.y += NEXT_LINE;			// ���s
			// HP
			ptCur_Draw.y += NEXT_LINE;			// ���s
			gotoxy_pt(ptCur_Draw);				// �ړ�
			printf("%8d", pCur_Chr_D->nHP);
			// SP
			ptCur_Draw.y += NEXT_LINE;			// ���s
			gotoxy_pt(ptCur_Draw);				// �ړ�
			printf("%8d", pCur_Chr_D->nSP);		// �`��
			// ���s
			ptCur_Draw.y += NEXT_LINE;			// ���s
			// ��������
			ptCur_Draw.y += NEXT_LINE;			// ���s
			gotoxy_pt(ptCur_Draw);				// �ړ�
			printf("%8d", pCur_Chr_D->nAtk);		// �`��
			// �ڂ�����
			ptCur_Draw.y += NEXT_LINE;			// ���s
			gotoxy_pt(ptCur_Draw);				// �ړ�
			printf("%8d", pCur_Chr_D->nDef);		// �`��
			// ���s
			ptCur_Draw.y += NEXT_LINE;			// ���s
			// �܂ق���
			ptCur_Draw.y += NEXT_LINE;			// ���s
			gotoxy_pt(ptCur_Draw);				// �ړ�
			printf("%8d", pCur_Chr_D->nMAtk);	// �`��
			// �܂قڂ�
			ptCur_Draw.y += NEXT_LINE;			// ���s
			gotoxy_pt(ptCur_Draw);				// �ړ�
			printf("%8d", pCur_Chr_D->nMDef);	// �`��
			// ���s
			ptCur_Draw.y += NEXT_LINE;			// ���s
			// ���΂₳
			ptCur_Draw.y += NEXT_LINE;			// ���s
			gotoxy_pt(ptCur_Draw);				// �ړ�
			printf("%8d", pCur_Chr_D->nSpd);		// �`��
		}
		// --------------------
		// �J�X�^���L�����N�^�[
		// --------------------
		else
		{
			msleep(500);

			pCur_Chr_D = CharacterList_Add_Blank(pCharacterList, pNumMember, true);

			// �T�u���b�Z�[�W�\���G���A���N���A
			ClearArea(&AreaT_CharacterCreate_Sub);
			ptCur_Draw_Sub = AreaT_CharacterCreate_Sub.start;
			gotoxy_pt(ptCur_Draw_Sub);
			printf("%2d�@�΂�߂̂��Ȃ��܂́H", i + 1);
			// �`����W
			ptCur_Draw.x = ptStart_CharacterCreate_Chara[i].x + SIZE_OF_BORDER; // �`��J�n�ʒu�@�{�@�r���i���j
			ptCur_Draw.y = ptStart_CharacterCreate_Chara[i].y + NEXT_LINE;		// �`��J�n�ʒu�@�́@���̍s

			ptStart_JobList.x = AreaT_CharacterCreate_Sub.end.x - (SIZE_OF_BORDER + 3 * SIZE_OF_ZENAKU_CHARACTER + SIZE_OF_BORDER + MAX_CHARACTERS_OF_JOB_NAME + SIZE_OF_BORDER);
			ptStart_JobList.y = AreaT_CharacterCreate_Sub.start.y + NEXT_LINE + NEXT_LINE;

			//-----------
			// �Ȃ܂�
			//-----------
			// ����
			ptCur_Draw_Sub.y += NEXT_LINE;
			gotoxy_pt(ptCur_Draw_Sub);
			printf("���Ȃ܂��@�́H");
			ptCur_Draw_Sub.y += NEXT_LINE;
			gotoxy_pt(ptCur_Draw_Sub);
			InputString_pt(pCur_Chr_D->szName, MAX_CHARACTERS_OF_HERO_NAME, &ptCur_Draw_Sub);
			// �`��
			gotoxy_pt(ptCur_Draw);										
			printf(pCur_Chr_D->szName);	
			//-----------
			// �E��
			//-----------
			// ����
			ptCur_Draw_Sub.y++;
			gotoxy_pt(ptCur_Draw_Sub);
			printf("�E�@�@�Ɓ@�́H");
			ptCur_Draw_Sub.y++;
			gotoxy_pt(ptCur_Draw_Sub);
			InputJob_pt(pCur_Chr_D, pJobList, &ptCur_Draw_Sub, &ptStart_JobList);
			
			ptCur_Draw.y += NEXT_LINE;											// ���s
			gotoxy_pt(ptCur_Draw);												// �ړ�
			printf(pCur_Chr_D->job.szName);										// �`��
			// ���s
			ptCur_Draw.y += NEXT_LINE;											// ���s
			// HP
			ptCur_Draw.y += NEXT_LINE;											// ���s
			gotoxy_pt(ptCur_Draw);												// �ړ�
			printf("%8d", pCur_Chr_D->nHP);
			// SP
			ptCur_Draw.y += NEXT_LINE;											// ���s
			gotoxy_pt(ptCur_Draw);												// �ړ�
			printf("%8d", pCur_Chr_D->nSP);										// �`��
			// ���s
			ptCur_Draw.y += NEXT_LINE;											// ���s
			// ��������
			ptCur_Draw.y += NEXT_LINE;											// ���s
			gotoxy_pt(ptCur_Draw);												// �ړ�
			printf("%8d", pCur_Chr_D->nAtk);										// �`��
			// �ڂ�����
			ptCur_Draw.y += NEXT_LINE;											// ���s
			gotoxy_pt(ptCur_Draw);												// �ړ�
			printf("%8d", pCur_Chr_D->nDef);										// �`��
			// ���s
			ptCur_Draw.y += NEXT_LINE;											// ���s
			// �܂ق���
			ptCur_Draw.y += NEXT_LINE;											// ���s
			gotoxy_pt(ptCur_Draw);												// �ړ�
			printf("%8d", pCur_Chr_D->nMAtk);									// �`��
			// �܂قڂ�
			ptCur_Draw.y += NEXT_LINE;											// ���s
			gotoxy_pt(ptCur_Draw);												// �ړ�
			printf("%8d", pCur_Chr_D->nMDef);									// �`��
			// ���s
			ptCur_Draw.y += NEXT_LINE;											// ���s
			// ���΂₳
			ptCur_Draw.y += NEXT_LINE;											// ���s
			gotoxy_pt(ptCur_Draw);												// �ړ�
			printf("%8d", pCur_Chr_D->nSpd);										// �`��
		}
	}
	

	
	// --------------------
	// �㏈��
	// --------------------
	StringList_DeleteAll(pTextList_Display_MessageMaster);
	StringList_DeleteAll(pTextList_Master_MessageMaster);

	getchar();
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
