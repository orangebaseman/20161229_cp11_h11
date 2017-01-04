// --------------------
// ���͕⏕
// -------------------
#include	"conioex.h"
#include	"public.h"
#include	<stdlib.h>

#ifndef MAX_CHARACTERS_OF_STR_FUNCTION
#define MAX_CHARACTERS_OF_STR_FUNCTION	(50)	// �����񑀍�֐��@�ő啶����
#endif // MAX_CHARACTERS_OF_STR_FUNCTION

// �y�֐����e�z
// �X�e�[�^�X�w�b�_�̕\��
// �y�����z
// x_start	: �y�Q�Ɨp�@�z�`�挴�_�i����j
// y_start	: �y�Q�Ɨp�@�z�`�挴�_�i����j
// �y�߂�l�z
// ���̕`��ʒu�iY���W)
int		InputInteger(int* pInput, unsigned int min, unsigned int max, int x_start, int y_start, bool isMinMaxShowed)
{
	int x = x_start, y = y_start;
	int i;							// ���[�v�ϐ�
	int len;						// ����
	if (max == 0)
	{
		len = 1;
	}
	else
	{
		len = (int)log10((double)max) + 1;
	}
	while (1)
	{
		gotoxy(x, y);
		printf("[");
		for (i = 0; i < len; i++)
		{
			printf(" ");
		}
		printf("]");
		if (isMinMaxShowed)
		{
			printf("[%2d - %2d ]", min, max);
		}

		gotoxy(x + 1, y);
		rewind(stdin);
		scanf("%d", pInput);
		if ((*pInput) >= min && (*pInput) <= max)
		{
			return y++;
		}
		else
		{
			gotoxy(x + len + 2, y);
			printf("[���ē���]");
		}
	}
}
void	InputString(char pInput[], int nMaxLen, int x_start, int y_start)
{
	int i;
	int x = x_start, y = y_start;
	int nLen;
	char cYN;
	char strStyle[6];
	sprintf(strStyle, "%%%ds", nMaxLen);

	while (1)
	{
		gotoxy(x, y);
		printf("[");
		for (i = 0; i < nMaxLen; i++)
		{
			printf(" ");
		}
		printf("]");

		gotoxy(x + 1, y);
		rewind(stdin);
		scanf(strStyle, pInput);
		nLen = strlen(pInput);
		for (i = nLen; i < nMaxLen; i++)
		{
			strcat(pInput, " ");
		}

		gotoxy(x + nMaxLen + 1, y);
		printf("]OK?(Y/N)");
		for (i = x + nMaxLen + 12; i <= MAX_WIDTH_OF_WINDOW; i++)
		{
			printf(" ");
		}
		gotoxy(x + nMaxLen + 12, y);
		rewind(stdin);
		scanf("%c", &cYN);
		gotoxy(x + nMaxLen + 2, y);
		for (i = x + nMaxLen + 2; i <= MAX_WIDTH_OF_WINDOW; i++)
		{
			printf(" ");
		}
		if (cYN == 'Y' || cYN == 'y')
		{
			return;
		}
	}
}
void	InputJob(tCharacter* pCh, const tJob* pJobList, int x_start, int y_start)
{
	int x = x_start, y = y_start;
	gotoxy(x, y);
	InputInteger(&(pCh->job.nCode), 1, 6, x, y, false);
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);
	gotoxy(x + 3, y);
	printf("[%s]", pCh->job.szName);
}

// �y�֐����e�z
// ��������g���~���O���ăR�s�[�i�ŏ�����nLen�������j
// �y�����z
// pDest	: �y�ύX�Ώہz�R�s�[�敶����
// pSource	: �y�Q�Ɨp�@�z�R�s�[��������
// nLen		: �y�Q�Ɨp�@�z��������
// �y�߂�l�z
// �Ȃ�
void	Trim_And_Copy_String(char* pDest,const char* pSource, int nLen)
{
	strncpy(pDest, pSource, nLen);	// nLen�����R�s�[
	*(pDest + nLen) = '\0';			// �R�s�[��̏I�[�Ƀk���������
}

// �y�֐����e�z
// ��������R�s�[�inStart�Ԗڂ���nLen�������j
// �y�����z
// pDest	: �y�ύX�Ώہz�R�s�[�敶����
// pSource	: �y�Q�Ɨp�@�z�R�s�[��������
// nStart	: �y�Q�Ɨp�@�z���Ԗڂ���
// nLen		: �y�Q�Ɨp�@�z��������
// �y�߂�l�z
// �Ȃ�
void Copy_String_From_Certain(char* pDest, const char* pSource, int nStart, int nLen)
{
	// --------------------
	// ���[�J���ϐ��錾
	// --------------------
	int cnt;													// ���[�v�J�E���^
	// --------------------
	// �R�s�[
	// --------------------
	for (cnt = 0; cnt < nLen; cnt++)							// nLen�����R�s�[������I��
	{
		(*(pDest + cnt)) = (*(pSource + (nStart - 1) + cnt));	// �R�s�[
		if (*(pDest + cnt) == '\0') return;						// �R�s�[���Ƀk����������������I��
	}
	(*(pDest + nLen)) = '\0';									// �R�s�[��̍Ō�Ƀk���������
}