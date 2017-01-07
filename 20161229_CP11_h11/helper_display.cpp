// --------------------
// �\���⏕
// --------------------
#include	"public.h"
#include	"conioex.h"

#ifndef PREVIOUS_LINE
#define	PREVIOUS_LINE	(1)	//1�s�O
#endif
#ifndef NEXT_LINE
#define	NEXT_LINE		(1)	//1�s��
#endif

// --------------------
// �^��private�֐��錾
// --------------------
tArea	DrawLine_Blank_(tPoint2D*, bool, const char*, const char*, const size_t);
tArea	DrawLine_Border(tPoint2D*, bool, const char*, const char*, const size_t, const char*);

// �y�֐����e�z
// gotoxy(conioex.h)�̃I�[�o�[���[�h
// �y�����z
// point	: �y�Q�Ɨp�@�z�ړ�����W
// �y�߂�l�z
// �Ȃ�
void	gotoxy_pt(tPoint2D point)
{
	gotoxy(point.x, point.y);
}

// �y�֐����e�z
// �`��͈͂��N���A
// �y�����z
// area	: �y�{���p�@�z�`��͈�
// �y�߂�l�z
// �Ȃ�
void	ClearArea(const tArea* area)
{
	int x;
	tPoint2D ptCur = area->start;
	// --------------------
	// �͈͓��𔼊p�X�y�[�X�ŏ㏑��
	// --------------------
	for (ptCur.y = area->start.y; ptCur.y <= area->end.y; ptCur.y++)
	{
		gotoxy_pt(ptCur);
		for (x = area->start.x; x <= area->end.x; x++)
		{
			printf(" ");
		}
	}
}

// �y�֐����e�z
// �r���E�C���h�E�@�����̕`��͈͂��擾
// �y�����z
// area	: �y�{���p�@�z�r���E�C���h�E�̕`��͈͔͈�
// �y�߂�l�z
//  �r���E�C���h�E�@�����̕`��͈�
tArea Area_Inside_BorderWindow(const tArea* area)
{
	tArea area_inside = (*area);
	area_inside.start.x += SIZE_OF_BORDER;
	area_inside.start.y += NEXT_LINE;
	area_inside.end.x -= SIZE_OF_BORDER;
	area_inside.end.y -= PREVIOUS_LINE;
	return area_inside;
}

// �y�֐����e�z
// �r���E�C���h�E�@�󔒍s�̕`��
// �y�����z
// pPtStart		: �y�ύX�Ώہz�`�挴�_�i����j
// isUpdateCur	: �y�Q�Ɨp�@�z�`��ʒu���X�V���邩�ۂ�
// borderLeft	: �y�Q�Ɨp�@�z�r�������i�����j
// borderRight	: �y�Q�Ɨp�@�z�r�������i�E���j
// size_cell	: �y�Q�Ɨp�@�z�󔒕�����
// �y�߂�l�z
// �`��̈�
tArea	DrawLine_Blank_(tPoint2D* pPtStart, bool isUpdateCur, const char* borderLeft, const char* borderRight, const size_t size_cell)
{
	// --------------------
	// ���[�J���ϐ��錾�A������
	// --------------------
	// �`����W
	tPoint2D	ptCur = (*pPtStart);
	// �`��̈�
	tArea		area = { ptCur, ptCur };
	// �r�������ϐ��@�������m��
	char*		borderL = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	char*		borderR = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	// �r�������R�s�[�i�������I�[�o�[�Ȃ�g���~���O�j
	Trim_And_Copy_String(borderL, borderLeft, SIZE_OF_BORDER);
	Trim_And_Copy_String(borderR, borderRight, SIZE_OF_BORDER);
	// --------------------
	// �`��
	// --------------------
	// �r���i���j
	gotoxy_pt(ptCur);									// �ړ����s
	printf(borderL);									// �`��
	// �r���i�E�j
	ptCur.x = pPtStart->x + SIZE_OF_BORDER + size_cell;	// X�ړ��ʒu�i�\�����������X�L�b�v�j
	gotoxy_pt(ptCur);									// �ړ����s
	printf(borderR);									// �`��
	// ���s
	ptCur.x = pPtStart->x;								// X�ړ��ʒu�i�����ʒu�j
	ptCur.y += 1;										// Y�ړ��ʒu�i���s�j
	// --------------------
	// ���������
	// --------------------
	free(borderL);
	free(borderR);
	// --------------------
	// �`��̈�X�V �i���I�[�ʒu���X�V�j
	// --------------------
	// X: �J�n���W + �r���i���j�@�{�@�\�������� + �r���i�E�j�@- �P�����O
	area.end.x = pPtStart->x + SIZE_OF_BORDER + size_cell *  + SIZE_OF_BORDER - SIZE_OF_HANKAKU_CHARACTER;
	// Y: ���ݍ��W - 1�s�O
	area.end.y = ptCur.y - PREVIOUS_LINE;
	// --------------------
	// ���̕`��ʒu���X�V
	// --------------------
	if (isUpdateCur)
	{
		(*pPtStart) = ptCur;
	}
	// --------------------
	// �`��̈��ԋp
	// --------------------
	return area;
}
// �y�֐����e�z
// �r���E�C���h�E�@�r���s�̕`��
// �y�����z
// pPtStart		: �y�ύX�Ώہz�`�挴�_�i����j
// isUpdateCur	: �y�Q�Ɨp�@�z�`��ʒu���X�V���邩�ۂ�
// borderLeft	: �y�Q�Ɨp�@�z�r�������i�����j
// borderRight	: �y�Q�Ɨp�@�z�r�������i�����j
// size_cell	: �y�Q�Ɨp�@�z�`�敶����
// borderRight	: �y�Q�Ɨp�@�z�r�������i�E���j
// �y�߂�l�z
// �`��̈�
tArea	DrawLine_Border(tPoint2D* pPtStart, bool isUpdateCur, const char* borderLeft, const char* borderCenter, const size_t size_cell, const char* borderRight)
{
	// --------------------
	// ���[�J���ϐ��錾�A������	
	// --------------------
	// ���[�v�J�E���^
	int			i;
	// �`����W
	tPoint2D	ptCur = (*pPtStart);
	// �`��̈�
	tArea		area = { ptCur, ptCur };
	// �r�������ϐ��@�������m��
	char*		borderL = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	char*		borderC = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	char*		borderR = (char *)malloc(sizeof(char) * (SIZE_OF_BORDER + SIZE_OF_NULL));
	// �r�������R�s�[�i�������I�[�o�[�Ȃ�g���~���O�j
	Trim_And_Copy_String(borderL, borderLeft, SIZE_OF_BORDER);
	Trim_And_Copy_String(borderC, borderCenter, SIZE_OF_BORDER);
	Trim_And_Copy_String(borderR, borderRight, SIZE_OF_BORDER);
	// --------------------
	// �`��
	// --------------------
	// �r���i���j
	gotoxy_pt(ptCur);				// �ړ����s
	printf(borderL);				// �`��
	// �r���i�����j�i�\�����������`��j
	for (int i = 0; i < size_cell; i += SIZE_OF_ZENAKU_CHARACTER)
	{
		printf(borderC);			// �`��
	}
	// �r���i�E�j
	printf(borderR);				// �`��
	// ���s
	ptCur.x = pPtStart->x;			// X�ړ��ʒu�i�����ʒu�j
	ptCur.y += 1;					// Y�ړ��ʒu�i���s�j
	// --------------------
	// ���������
	// --------------------
	free(borderL);
	free(borderC);
	free(borderR);
	// --------------------
	// �`��̈�X�V �i���I�[�ʒu���X�V�j
	// --------------------
	// X: �J�n���W + �r���i���j�@�{�@�\��������(�r���i�����j) + �r���i�E�j�@- �P�����O
	area.end.x = pPtStart->x + SIZE_OF_BORDER + size_cell + SIZE_OF_BORDER - SIZE_OF_HANKAKU_CHARACTER;
	// Y: ���ݍ��W - 1�s�O
	area.end.y = ptCur.y - PREVIOUS_LINE;
	// --------------------
	// ���̕`��ʒu���X�V
	// --------------------
	if (isUpdateCur)
	{
		(*pPtStart) = ptCur;
	}
	// --------------------
	// �`��̈��ԋp
	// --------------------
	return area;
}

tArea	DrawBorderWindow(tPoint2D* pPtStart, bool isUpdateCur, const size_t width, const size_t height)
{
	// --------------------
	// ���[�J���ϐ��錾�A������	
	// --------------------
	// ���[�v�J�E���^
	int i;
	// �`����W
	tPoint2D	ptCur = (*pPtStart);
	// �S�p�`��I�����W 
	tPoint2D	ptZenkakuEnd = { pPtStart->x + width - SIZE_OF_ZENAKU_CHARACTER,
								pPtStart->y + height - PREVIOUS_LINE };
	// �`��̈�
	tArea		area = { ptCur, ptCur };
	// --------------------
	// �G���[�`�F�b�N�F�@�G���[�Ȃ�`�悹���ɏI��
	// --------------------
	// ���͑S�p�T�C�Y��
	if (width % SIZE_OF_ZENAKU_CHARACTER != 0)
	{
		gotoxy_pt(ptCur);
		printf("DrawBorderWindow ERROR:�S�p�����̃T�C�Y�i�����j����͂��Ă�������");
		return area;
	}
	if (width < 2 * SIZE_OF_ZENAKU_CHARACTER || height < 2)
	{
		gotoxy_pt(ptCur);
		printf("DrawBorderWindow ERROR:�E�C���h�E����������T�C�Y����͂��Ă�������");
		return area;
	}
	if (ptZenkakuEnd.x > MAX_WIDTH_OF_WINDOW - SIZE_OF_HANKAKU_CHARACTER ||
		ptZenkakuEnd.y > MAX_HEIGHT_OF_WINDOW)
	{
		gotoxy_pt(ptCur);
		printf("DrawBorderWindow ERROR:�E�C���h�E�̕\���g�𒴂��ē��͂��悤�Ƃ��Ă��܂��B�T�C�Y���m�F���Ă��������B");
		return area;
	}
	// --------------------
	// �`��
	// --------------------
	// --------
	// �l���`��
	// --------
	// �����
	gotoxy_pt(ptCur);			// �ړ����s
	printf("��");				// �`��
	// �E���
	ptCur.x = ptZenkakuEnd.x;	// X�ړ��ʒu�i�S�p�I�����W�j
	ptCur.y = pPtStart->y;		// Y�ړ��ʒu�i���_�j
	gotoxy_pt(ptCur);			// �ړ����s
	printf("��");				// �`��
	// ������
	ptCur.x = pPtStart->x;		// X�ړ��ʒu�i���_�j
	ptCur.y = ptZenkakuEnd.y;	// Y�ړ��ʒu�i�S�p�I�����W�j
	gotoxy_pt(ptCur);			// �ړ����s
	printf("��");				// �`��
	// �E����
	ptCur.x = ptZenkakuEnd.x;	// X�ړ��ʒu�i�S�p�I�����W�j
	ptCur.y = ptZenkakuEnd.y;	// Y�ړ��ʒu�i�S�p�I�����W�j
	gotoxy_pt(ptCur);			// �ړ����s
	printf("��");				// �`��
	// --------
	// �����`��
	// --------
	// ���`�� (���[�͕`�悹���j
	for (i = 0 + SIZE_OF_BORDER; i <= ptZenkakuEnd.x - SIZE_OF_BORDER; i += SIZE_OF_ZENAKU_CHARACTER)
	{
		ptCur.x = pPtStart->x + i;	// X���W�ʒu
		// �㑤
		ptCur.y = pPtStart->y;		// Y���W�ʒu�i���_�j
		gotoxy_pt(ptCur);			// �ړ����s
		printf("��");				// �`��
		// ����
		ptCur.y = ptZenkakuEnd.y;	// Y�ړ��ʒu�i�S�p�I�����W�j
		gotoxy_pt(ptCur);			// �ړ����s
		printf("��");				// �`��
	}
	// �c�`�� (���[�͕`�悹���j
	for (i = 0 + NEXT_LINE; i < ptZenkakuEnd.y - PREVIOUS_LINE; i++)
	{
		ptCur.y = pPtStart->y + i;	// Y���W�ʒu
		// �㑤
		ptCur.x = pPtStart->x;		// X�ړ��ʒu�i���_�j
		gotoxy_pt(ptCur);			// �ړ����s
		printf("��");				// �`��
		// ����
		ptCur.x = ptZenkakuEnd.x;	// X�ړ��ʒu�i�S�p�I�����W�j
		gotoxy_pt(ptCur);			// �ړ����s
		printf("��");				// �`��
	}
	// --------------------
	// �`��̈�X�V �i���I�[�ʒu���X�V�j
	// --------------------
	// X: �J�n���W + haba - 1�����O
	area.end.x = pPtStart->x + width - SIZE_OF_HANKAKU_CHARACTER;
	// Y: �J�n���W + ���� - 1�s�O
	area.end.y = pPtStart->y + height - PREVIOUS_LINE;
	// --------------------
	// ���̕`��ʒu���X�V
	// --------------------
	if (isUpdateCur)
	{
		ptCur.x = pPtStart->x;
		ptCur.y = area.end.y + 1;
		(*pPtStart) = ptCur;
	}
	// --------------------
	// �`��̈��ԋp
	// --------------------
	return area;
}

// �y�֐����e�z
// �e�L�X�g���X�g���w��ʒu�ɕ`��i�P���`��j
// �y�����z
// AreaDisp		: �y�Q�Ɨp�@�z�����\���̗̈�
// pTextList	: �y�Q�Ɨp�@�z�\������e�L�X�g���X�g
// ptCur_Draw	: �y�ύX�Ώہz�`�挻�݈ʒu�i�֐��I������p���j
// �y�߂�l�z
// �Ȃ�
void DrawTextList_Plain(tArea AreaDisp, tString* pTextList, tPoint2D* ptCur_Draw)
{
	// ���݈ʒu�̍X�V
	(*ptCur_Draw) = AreaDisp.start;
	tString* pCur_Str = StringList_First(pTextList);
	// �`����s�i�P�s�ڂŏ����𖞂����Ă��Ȃ���΁A�`�悵�Ȃ��j
	while (ptCur_Draw->y <= AreaDisp.end.y && pCur_Str != NULL)
	{
		// �ړ��A�`��
		gotoxy_pt(*ptCur_Draw);
		printf(pCur_Str->szText);
		// �`��𑱂��邩�i���̍s���`��͈͓����ǂ����A���̃��b�Z�[�W�̗L���Ŕ���j
		if (ptCur_Draw->y + 1 <= AreaDisp.end.y && pCur_Str->next != NULL)
		{
			// ���̍s����i�����X�V�j
			ptCur_Draw->y += 1;			// �`��ʒu�����̍s��
			pCur_Str = pCur_Str->next;	// �\�����b�Z�[�W������
		}
		else
		{
			// ���̍s�Ȃ��i�`��I���j
			ptCur_Draw->y += 1;			// �`��ʒu�����̍s��
			gotoxy_pt(*ptCur_Draw);		// �ړ�
			break;
		}
	}
}


// �y�֐����e�z
// �X�e�[�^�X�w�b�_�̕\��
// �y�����z
// x_start	: �y�Q�Ɨp�@�z�`�挴�_�i����j
// y_start	: �y�Q�Ɨp�@�z�`�挴�_�i����j
// �y�߂�l�z
// ���̕`��ʒu�iY���W)
int		DisplayStatusHeader(int x_start, int y_start)
{
	// --------------------
	// ���[�J���ϐ��錾�A������
	// --------------------
	int x = x_start, y = y_start;	//	�`����W
	// --------------------
	// �`��
	// --------------------
	gotoxy(x, y); printf("������������"); y++;
	gotoxy(x, y); printf("���Ȃ܂��@��"); y++;
	gotoxy(x, y); printf("���E�@�@�Ƅ�"); y++;
	gotoxy(x, y); printf("������������"); y++;
	gotoxy(x, y); printf("���g�@�@�o��"); y++;
	gotoxy(x, y); printf("���r�@�@�o��"); y++;
	gotoxy(x, y); printf("������������"); y++;
	gotoxy(x, y); printf("������������"); y++;
	gotoxy(x, y); printf("���ڂ����儫"); y++;
	gotoxy(x, y); printf("������������"); y++;
	gotoxy(x, y); printf("���܂ق�����"); y++;
	gotoxy(x, y); printf("���܂قڂ���"); y++;
	gotoxy(x, y); printf("������������"); y++;
	gotoxy(x, y); printf("�����΂₳��"); y++;
	gotoxy(x, y); printf("������������"); y++;
	// --------------------
	// ���̕`��ʒu�iY�j��ԋp
	// --------------------
	return y;
}

tPoint2D*	DisplayStatusHeader_PT(tPoint2D* ptStart)
{
	ptStart->y = DisplayStatusHeader(ptStart->x, ptStart->y);
	return ptStart;
}

// �y�֐����e�z
// �X�e�[�^�X�@�󔒔ł̕\��
// �y�����z
// x_start	: �y�Q�Ɨp�@�z�`�挴�_�i����j
// y_start	: �y�Q�Ɨp�@�z�`�挴�_�i����j
// isLast	: �y�Q�Ɨp�@�z�Ō�̂P���ۂ�
// �y�߂�l�z
// ���̕`��ʒu�iY���W)
//�@�@�@�@�@�@�@�@(isLAST)
//������������  ������������
//���@�@�@�@��  ���@�@�@�@��
//���@�@�@�@��  ���@�@�@�@��
//������������  ������������
//���@�@�@�@��  ���@�@�@�@��
//���@�@�@�@��  ���@�@�@�@��
//������������  ������������
//���@�@�@�@��  ���@�@�@�@��
//���@�@�@�@��  ���@�@�@�@��
//������������  ������������
//���@�@�@�@��  ���@�@�@�@��
//���@�@�@�@��  ���@�@�@�@��
//������������  ������������
//���@�@�@�@��  ���@�@�@�@��
//������������  ������������
int			DisplayStatusBlank(int x_start, int y_start, bool isLast)
{
	// --------------------
	// ���[�J���ϐ��錾�A������
	// --------------------
	int x = x_start, y = y_start;
	tPoint2D	ptCur = { x_start, y_start };

	// --------------------
	// �`��
	// --------------------	
	DrawLine_Border(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "��" : "��"));
	DrawLine_Blank_(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Blank_(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "��" : "��"));
	DrawLine_Blank_(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Blank_(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "��" : "��"));
	DrawLine_Blank_(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Blank_(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "��" : "��"));
	DrawLine_Blank_(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Blank_(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "��" : "��"));
	DrawLine_Blank_(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME);
	DrawLine_Border(&ptCur, true, "��", "��", MAX_CHARACTERS_OF_HERO_NAME, ((!isLast) ? "��" : "��"));

	y = ptCur.y;
	//// --------------------
	// ���̕`��ʒu�iY�j��ԋp
	// --------------------
	return y;
}

tPoint2D*	DisplayStatusBlank_pt(tPoint2D* ptStart, bool isLast)
{
	ptStart->y = DisplayStatusBlank(ptStart->x, ptStart->y, isLast);
	return ptStart;
}

// �y�֐����e�z
// �E�ƈꗗ��\��
// �y�����z
// pJobList	: �y�{���p�@�z�E�ƈꗗ
// x_start	: �y�{���p�@�z�`�挴�_�i����j
// y_start	: �y�{���p�@�z�`�挴�_�i����j
// x_end	: �y�ύX�Ώہz�`��I���ʒu���W�i�E���j
// y_end	: �y�ύX�Ώہz�`��I���ʒu���W�i�E���j
// �y�߂�l�z
// �Ȃ�
void	DisplayJobList(const tJob* pJobList, int x_start, int y_start, int* x_end, int* y_end)
{	// --------------------
	// ���[�J���ϐ��錾�A������
	// --------------------
	int x = x_start, y = y_start;	// �`����W
	// --------------------
	// �`��
	// --------------------
	gotoxy(x, y); printf("��������������������"); y++;
	gotoxy(x, y); printf("���R�[�h���E�@�@�Ƅ�"); y++;
	gotoxy(x, y); printf("��������������������"); y++;
	gotoxy(x, y); printf("���@�@ 1�����񂵁@��"); y++;
	gotoxy(x, y); printf("���@�@ 2���^���N�@��"); y++;
	gotoxy(x, y); printf("���@�@ 3�������Ƃ���"); y++;
	gotoxy(x, y); printf("���@�@ 4���ɂ񂶂ᄫ"); y++;
	gotoxy(x, y); printf("���@�@ 5���܂ق��@��"); y++;
	gotoxy(x, y); printf("���@�@ 6���݁@�@����"); y++;
	gotoxy(x, y); printf("��������������������"); y++;
	// --------------------
	// �`��I���ʒu���W
	// --------------------
	(*x_end) = x_start + 10 * SIZE_OF_ZENAKU_CHARACTER;	// �S�p�P�O�����E
	(*y_end) = y - 1;									// ���݈ʒu�̈��
}

// �y�֐����e�z
// ��������w�蕶�����Ń��T�C�Y
// �i�I�[�o�[������tString�𕪊����AList�ɒǉ��j
// �y�����z
// pStrLine	: �y�ύX�Ώہz���T�C�Y���镶����
// nMaxLen	: �y�Q�Ɨp�@�z�P�s�̍ő啶����
// �y�߂�l�z
// �������s��
int		ResizeStringLine(tString* pStrLine, int nMaxLen)
{
	// --------------------
	// ���[�J���ϐ��錾�A������
	// --------------------
	tString* pNewLine;						// �ǉ��s
	int nLen = strlen(pStrLine->szText);		// ���݂̕�����̒���
	int nAddedLines = 0;					// �ǉ��s��
	// --------------------
	// ����
	// --------------------
	if (nLen > nMaxLen)
	{
		// �s���C���N�������g
		nAddedLines++;
		// List�ɒǉ�
		pNewLine = StringList_Add_Blank(pStrLine, false);
		// �ǉ��s�̕�����FnLenMax+1�Ԗڂ���c�肷�ׂāinLen-nLenMax�����j���R�s�[
		Copy_String_From_Certain(pNewLine->szText, pStrLine->szText, nMaxLen + 1, nLen - nMaxLen);
		// ���݂̕�����F�ŏ�����nLenMax�������Ƀg���~���O
		Trim_And_Copy_String(pStrLine->szText, pStrLine->szText, nMaxLen);
		// �ǉ��s�̕���������T�C�Y�i�A�[�I�ɌĂяo���j
		nAddedLines += ResizeStringLine(pNewLine, nMaxLen);
	}
	// --------------------
	// �ǉ��s����ԋp
	// --------------------
	return nAddedLines;
}

// �y�֐����e�z
// �����񃊃X�g���w��T�C�Y�Ƀ��T�C�Y�i�P�s�̕������A�s���Ŏw��j
// �y�����z
// pDest	: �y�ύX�Ώہz�\���p������
// pSource	: �y�Q�Ɨp�@�z���f�[�^
// order	: �y�Q�Ɨp�@�z�O�F�ŏ�����
// nStart	: �y�Q�Ɨp�@�z��������
// nMaxLen	: �y�Q�Ɨp�@�z1�s������̕\��������
// nMaxLines: �y�Q�Ɨp�@�z�\���s��
// �y�߂�l�z
// ���T�C�Y���������񃊃X�g
tString* ResizeStringList_By_LengthAndLines(tString* pDest, tString* pSource, int order, int nStart, int nMaxLen, int nMaxLines)
{
	// --------------------
	// ���[�J���ϐ��錾
	// --------------------
	tString* pStart_S;			// �Q�ƊJ�n�s
	tString* pCur_S;			// ���ݒn�i�Q�ƕ�����j
	tString* pCur_D;			// ���ݒn�i�\��������j
	int nLines = 0;				// �s��
	int i;						// ���[�v�J�E���^
	int nAddLine = 0;			// �ǉ��s��
	// --------------------
	// ������
	// --------------------
	// �\�������񏉊���
	StringList_DeleteAll(pDest);
	pDest = StringList_New_Blank();
	pCur_D = pDest;
	// --------------------
	// �ŏ����玟��
	// --------------------
	if (order == START_FROM_FIRST)
	{
		// --------------------
		// �Q�ƊJ�n�s������
		// --------------------
		nLines = 1;								// �ړ��s��������
		pStart_S = StringList_First(pSource);	// �Q�ƊJ�n�s�������i��ԏ��߂Ɉړ��j
		while (1)
		{
			nLines++;							// �s���X�V
			// --------------------
			// ���̍s�@�L������@�i�s���A���̎Q�Ɨ���m�F�j
			// --------------------
			if (nLines <= nStart && pStart_S->next != NULL)
			{
				// --------------------
				// ���̍s����
				// --------------------
				pStart_S = pStart_S->next;		//�@�Q�ƊJ�n�s������
			}
			else
			{
				// --------------------
				// ���̍s�Ȃ�
				// --------------------
				break;
			}
		}
		// --------------------
		// �\�������񃊃X�g�̍쐬
		// --------------------
		pCur_S = pStart_S;									// ���ݒn���Q�ƊJ�n�s�ֈړ�
		nLines = 0;											// �\���s����������
		while (1)
		{
			// --------------------
			// �\���s�̃R�s�[
			// --------------------
			strcpy(pCur_D->szText, pCur_S->szText);			// ��������R�s�[�i�Q�ƍs���\��������j
			nLines += 1;									// �\��������̍s�����J�E���g
			nAddLine = ResizeStringLine(pCur_D, nMaxLen);	// �\��������̒��������T�C�Y
			for (i = 0; i < nAddLine; i++)					
			{
				pCur_D = pCur_D->next;						// �\��������̌��ݒn���A���T�C�Y���đ������s�����ړ�					
				nLines++;									// �\��������̍s�����A���T�C�Y���đ������s�����ړ�
			}
			// --------------------
			// ���̍s�@�L������@�i�s���A���̎Q�Ɨ���m�F�j
			// --------------------
			if (nLines <= nMaxLines && pCur_S->next != NULL)
			{
				// --------------------
				// ���̍s����
				// --------------------
				pCur_D = StringList_Add_Blank(pCur_D, false);		// �V�K�쐬
				pCur_S = pCur_S->next;						// ���ցi�Q�ƕ�����j
			}
			else
			{
				// --------------------
				// ���̍s�Ȃ��@�i�s�������������Ă�����Ōォ����j
				// --------------------
				pCur_D = StringList_Last(pCur_D);
				while (nLines > nMaxLines && pCur_D->prev != NULL)
				{
					pCur_D = pCur_D->prev;					// ��O�ɖ߂���
					StringList_Delete(pCur_D->next);			// �폜
					nLines--;								// �s�������炷
				}
				break;
			}
		}
	}
	// --------------------
	// �Ōォ��O��
	// --------------------
	else if (order == START_FROM_LAST)
	{
		// --------------------
		// �Q�ƊJ�n�s������
		// --------------------
		nLines = 1;								// �ړ��s��������
		pStart_S = StringList_Last(pSource);	// �Q�ƊJ�n�s�������i��ԍŌ�Ɉړ��j
		while (1)
		{
			nLines++;						// �s���X�V
			// --------------------
			// �O�̍s�@�L������@�i�s���A�O�̎Q�Ɨ���m�F�j
			// --------------------
			if (nLines <= nStart && pStart_S->prev != NULL)
			{
				// --------------------
				// �O�̍s����
				// --------------------
				pStart_S = pStart_S->prev;		//�@�Q�ƊJ�n�s���ЂƂO��
			}
			else
			{
				// --------------------
				// �O�̍s�Ȃ�
				// --------------------
				break;
			}
		}
		// --------------------
		// �\�������񃊃X�g�̍쐬
		// --------------------
		pCur_S = pStart_S;									// ���ݒn���Q�ƊJ�n�s�ֈړ�
		nLines = 0;											// �\���s����������
		while (1)
		{
			// --------------------
			// �\���s�̃R�s�[
			// --------------------
			strcpy(pCur_D->szText, pCur_S->szText);			// ��������R�s�[�i�Q�ƍs���\��������j
			nLines += 1;									// �\��������̍s�����J�E���g
			nAddLine = ResizeStringLine(pCur_D, nMaxLen);	// �\��������̒��������T�C�Y
			for (i = 0; i < nAddLine; i++)
			{
				pCur_D = pCur_D->next;						// �\��������̌��ݒn���A���T�C�Y���đ������s�����ړ�					
				nLines++;									// �\��������̍s�����A���T�C�Y���đ������s�����ړ�
			}
			// --------------------
			// ���̍s�@�L������@�i�s���A�O�̎Q�Ɨ���m�F�j
			// --------------------
			if (nLines <= nMaxLines && pCur_S->prev != NULL)
			{
				// --------------------
				// ���̍s����
				// --------------------
				pCur_D = StringList_Add_Blank(pCur_D, false);		// �V�K�쐬
				pCur_S = pCur_S->prev;						// �O�ցi�Q�ƕ�����j
			}
			else
			{
				// --------------------
				// ���̍s�Ȃ��@�i�s�������������Ă�����ŏ�������j
				// --------------------
				pCur_D = StringList_First(pCur_D);
				while (nLines > nMaxLines && pCur_D->next != NULL)
				{
					pCur_D = pCur_D->next;				// ���ɐi�߂�
					StringList_Delete(pCur_D->prev);		// �폜
					nLines--;							// �s�������炷
				}
				break;
			}
		}
		pCur_D = StringList_Reverse(pCur_D);
	}
	// --------------------
	// ���T�C�Y�����Q�ƕ����񃊃X�g��ԋp
	// --------------------
	pCur_D = StringList_First(pCur_D);
	return pCur_D;
}

tString* ResizeStringList_By_tArea(tString* pDest, tString* pSource, tArea area, int order, int nStart)
{
	int nLength = area.end.x - area.start.x + 1;
	int nLines = area.end.y - area.start.y + 1;
	return ResizeStringList_By_LengthAndLines(pDest, pSource, order, nStart, nLength, nLines);
}
