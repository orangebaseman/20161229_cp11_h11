#ifndef __PUBLIC_H
#define __PUBLIC_H
// --------------------
// �W�����C�u����
// --------------------
#include	<stdio.h>
#include	<math.h>
#include	<stdlib.h>
#include	<string.h>
#pragma warning(disable:4996)
// --------------------
// �}�N����`
// --------------------
#define MAX_NUMBER_OF_JOBS			(6)		// �E�Ƃ̐�
#define MAX_NUMBER_OF_CHARACTERS	(4)		// �L�����N�^�[�l��
#define MAX_CHARACTERS_OF_JOB_NAME	(4 * 2)	// �E�ƍő啶����(�S�p�S�����j
#define MAX_CHARACTERS_OF_HERO_NAME	(4 * 2)	// �L�����ő啶����(�S�p�S�����j
#define SIZE_OF_BORDER				(2)		// �r���̑傫��
#define	SIZE_OF_NULL				(1)		// �k�������̑傫��
#define	SIZE_OF_HANKAKU_CHARACTER	(1)		// ���p�����̑傫��
#define	SIZE_OF_ZENAKU_CHARACTER	(2)		// �S�p�����̑傫��
#define MAX_WIDTH_OF_WINDOW			(80)	// �E�C���h�E��
#define MAX_HEIGHT_OF_WINDOW		(25)	// �E�C���h�E����
#define START_FROM_FIRST			(1)		// ���ԁi�ŏ�����j
#define START_FROM_LAST				(-1)	// ���ԁi�Ōォ��j
// --------------------
// �\���̒�`
// --------------------
typedef struct _tPoint2D	// �Q�������W�\����
{
	int	x;					// X���W
	int	y;					// Y���W
} tPoint2D;
typedef struct _tArea		// �̈�\����
{
	tPoint2D start;			// �̈�J�n�ʒu�i����j
	tPoint2D end;			// �̈�I���ʒu�i�E���j
} tArea;

typedef struct _tString						// �����񃊃X�g
{
	// --------------------
	// ��{���
	// --------------------
	char	szText[MAX_WIDTH_OF_WINDOW
					+ SIZE_OF_NULL];		// ������
	// --------------------
	// ���X�g�\��
	// --------------------
	struct _tString*	prev;				// �O��tString
	struct _tString*	next;				// ����tString

} tString;

typedef struct _tJob							// �E�ƍ\����
{
	// --------------------
	// ��{���
	// --------------------
	int		nCode;								// �E�Ǝ��ʃR�[�h
	char	szName[MAX_CHARACTERS_OF_JOB_NAME
					+ SIZE_OF_NULL];			// �E�Ɩ�
	// --------------------
	// �p�����[�^�␳ (1 �` 5)
	// --------------------
	int		nHP;								// HP�␳
	int		nSP;								// SP�␳
	int		nAtk;								// ���������␳
	int		nDef;								// �ڂ�����␳
	int		nMAtk;								// �܂ق����␳
	int		nMDef;								// �܂قڂ��␳
	int		nSpd;								// ���΂₳�␳
	// --------------------
	// ���X�g�\��
	// --------------------
	struct _tJob* prev;							// �O��tJob
	struct _tJob* next;							// ����tJob
} tJob;

typedef struct _tCharacter							// �L�����N�^�[�\����
{
	// --------------------
	// ��{���
	// --------------------
	char		szName[MAX_CHARACTERS_OF_HERO_NAME
						+ SIZE_OF_NULL];			// ���O
	tJob		job;								// �E��
	// --------------------
	// �X�e�[�^�X��l�i�p�����[�^�ӂ�j
	// --------------------
	int		nHP_Base;								// HP
	int		nSP_Base;								// SP
	int		nAtk_Base;								// ��������
	int		nDef_Base;								// �ڂ�����
	int		nMAtk_Base;								// �܂ق���
	int		nMDef_Base;								// �܂قڂ�
	int		nSpd_Base;								// ���΂₳
	// --------------------
	// �X�e�[�^�X�����l
	// --------------------
	int		nHP;									// HP
	int		nSP;									// SP
	int		nAtk;									// ��������
	int		nDef;									// �ڂ�����
	int		nMAtk;									// �܂ق���
	int		nMDef;									// �܂قڂ�
	int		nSpd;									// ���΂₳
	// --------------------
	// ���X�g�\��
	// --------------------
	struct _tCharacter* prev;						// �O��tCharacter
	struct _tCharacter* next;						// ����tCharacter
} tCharacter;

// ---------------------------
// �v���g�^�C�v�֐��錾
// ---------------------------
// �������FtJob
// init_tJob.cpp
void	InitJobs(tJob*);												// �E�Ə���������
tJob	getJobByCode(int, const tJob*);									// �E�Ǝ��ʃR�[�h����A�E�Ə����擾

// ������:tCharacter
// init_tCharacter.cpp
void	InitMainCharacter(tCharacter*, const tJob*, int*);				// ��l������������
void	InitBuiltInCharacters(tCharacter*, const tJob*, int*);			// �g�ݍ��݃L������������
void	CalculateCharacterStatus(tCharacter*);							// �X�e�[�^�X���v�Z
int		CalculateIndivisualStatus(int, int, int);						// �e�X�e�[�^�X���v�Z

// ���X�g�\���FtJob
// list_tJob.cpp
tJob*	JobList_New();													// JobList��V�K�쐬
tJob*	JobList_Add(tJob*, bool);										// JobList�ɒǉ��itrue:�Ō���ɒǉ� false:����ɒǉ�)
void	JobList_Delete(tJob*);											// JobList�ꌏ�폜
void	JobList_DeleteAll(tJob*);										// JobList�S�폜

// ���X�g�\���FtCharacter
// list_tCharacter.cpp
tCharacter*	CharacterList_New(int*);									// CharacterList��V�K�쐬
tCharacter*	CharacterList_Add(tCharacter*, int*, bool);					// CharacterList�ɒǉ��itrue:�Ō���ɒǉ� false:����ɒǉ�)
void		CharacterList_Delete(tCharacter*);							// CharacterList�ꌏ�폜
void		CharacterList_DeleteAll(tCharacter*);						// CharacterList�S�폜

// ���X�g�\���FtString
// list_tString.cpp
tString*	StringList_New_Blank();
tString*	StringList_New(const char* pChar);
tString*	StringList_Add_Blank(tString*, bool);
tString*	StringList_Add(tString* pStr, const char* pChar, bool isAddToLast);
void		StringList_Delete(tString*);
void		StringList_DeleteAll(tString*);
tString*	StringList_First(tString*);
tString*	StringList_Last(tString*);
tString*	StringList_Reverse(tString* pStr);


// ���͕⏕
// helper_input.cpp
int		InputInteger(int*, unsigned int, unsigned int, int, int, bool);	// ������ϐ��ɓ���
int		InputInteger_pt(unsigned int min, unsigned int max, tPoint2D* ptStart, bool isMinMaxShowed);
void	InputString(char[], int, int, int);								// �������ϐ��ɓ���
void	InputJob(tCharacter*, const tJob*, int, int);					// �E�Ƃ�I�����A�ϐ��ɓ���
void	Trim_And_Copy_String(char*, const char*, int);
void	Copy_String_From_Certain(char*, const char*, int, int);


// �\���⏕
// helper_display.cpp
void	gotoxy_pt(tPoint2D point);
void	ClearArea(const tArea*);
tArea	DrawBorderWindow(tPoint2D*, bool, const size_t, const size_t);	//
tArea	Area_Inside_BorderWindow(const tArea*);
void DrawTextList_Plain(tArea AreaDisp, tString* pTextList, tPoint2D* ptCur_Draw);
int		DisplayStatusHeader(int, int);							
tPoint2D*	DisplayStatusHeader_PT(tPoint2D* ptStart);					//
int		DisplayStatusBlank(int, int, bool);								//
tPoint2D*	DisplayStatusBlank_pt(tPoint2D* ptStart, bool isLast);
void	DisplayJobList(const tJob*, int, int, int*, int*);				// 
int		ResizeStringLine(tString* pStrLine, int nMaxLen);
tString* ResizeStringList(tString* , tString* , int, int , int, int);
tString* ResizeStringList_By_tArea(tString* pDest, tString* pSource, tArea area, int order, int nStart);
void ShowTextinWindow(tString* pMessageList, tArea area);

// ���j���[�V�[��
// scene0_menu.cpp
void	Execute_MenuScene(int*);										// ���j���[�V�[��_�V�[�����s

// �L�����N�^�[�쐬�V�[��
// scene1_create.cpp
void	Execute_CreateScene(tCharacter*, const tCharacter*,
							const tJob*, int*, int);					// �L�����N�^�[�쐬�V�[��_�V�[�����s

// �L�����N�^�[�X�V�V�[��
// scene2_update_member.cpp
void	Execute_UpdateMemberScene(tCharacter*, const tJob*, int);

// �L�����N�^�[�폜�V�[��
// scene3_delete_member.cpp
void	Execute_DeleteMemberScene(tCharacter*, int*);

// �L�����N�^�[�\���V�[��
// scene4_display_member.cpp
void	Execute_ShowMemberScene(const tCharacter*);


#endif	//__PUBLIC_H