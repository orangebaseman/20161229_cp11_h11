// ---------------------------
// �o�g���R���V�A�� Light
// ---------------------------
#include	"public.h"

void main(void)
{
	// ---------------------------
	// �ϐ��錾,������
	// ---------------------------
	int menu= -1;															// �I�𒆂̃��j���[
	int numOfPartyMember	= 0;											// ���݂̃p�[�e�B�����o�[�l��
	int numOfBuiltInChara	= 0;											// ���݂̑g�ݍ��݃L�����N�^�[�l��
	// �E�ƈꗗ���X�g
	tJob* pJobList = JobList_New();											// ���X�g�쐬
	InitJobs(pJobList);														// ������
	// �g�ݍ��݃L�����N�^�[�ꗗ���X�g
	tCharacter* pBuiltInCharaList = CharacterList_New(&numOfBuiltInChara);	// ���X�g�쐬
	InitBuiltInCharacters(pBuiltInCharaList, pJobList, &numOfBuiltInChara);	// ������
	// �L�����N�^�[�ꗗ���X�g
	tCharacter* pCharacterList = CharacterList_New(&numOfPartyMember);		// ���X�g�쐬
	InitMainCharacter(pCharacterList, pJobList, &numOfPartyMember);			// �������i��l�����쐬�j

	// test
	tString* sList = StringList_New();
	strcpy(sList->szText, "�P���傤�߂Q���傤�߂R���傤");
	sList = StringList_Add_Blank(sList, true);
	strcpy(sList->szText, "�S���傤�߂T���傤�߂U���傤");
	sList= StringList_Add_Blank(sList, true);
	strcpy(sList->szText, "�V���傤�߂W���傤�߂X���傤");
	tString* pTextList = StringList_New();
	

	StringList_DeleteAll(sList);
	StringList_DeleteAll(pTextList);

	// ---------------------------
	// �V�[���I���A���s�@�i�O�ŏI���j
	// ---------------------------
	while (menu != 0)
	{
		// ---------------------------
		// �V�[���F���j���[�I��
		// ---------------------------
		Execute_MenuScene(&menu);
		switch (menu)
		{
		case 1:
			// ---------------------------
			// �V�[�� 1�F�L�����N�^�[�쐬
			// ---------------------------
			Execute_CreateScene(pCharacterList, pBuiltInCharaList, pJobList, &numOfPartyMember, numOfBuiltInChara);
			getchar();
			break;
		case 2:
			// ---------------------------
			// �V�[�� 2�F�L�����N�^�[�X�V
			// ---------------------------
			Execute_UpdateMemberScene(pCharacterList, pJobList, numOfPartyMember);
			getchar();
			break;
		case 3:
			// ---------------------------
			// �V�[�� 3�F�L�����N�^�[�폜
			// ---------------------------
			Execute_DeleteMemberScene(pCharacterList, &numOfPartyMember);
			getchar();
			break;
		case 4:
			// ---------------------------
			// �V�[�� 4�F�L�����N�^�[�\��
			// ---------------------------
			Execute_ShowMemberScene(pCharacterList);
			getchar();
			break;
		}
	}

	printf("\n  ���悤�Ȃ� �܂��@���������������܂�");
	
	JobList_DeleteAll(pJobList);
	CharacterList_DeleteAll(pCharacterList);
	
	// ---------------------------
	// �X�g�b�p�Ƃ��Ă̓��͑҂�
	// ---------------------------
	rewind(stdin);
	getchar();
}

