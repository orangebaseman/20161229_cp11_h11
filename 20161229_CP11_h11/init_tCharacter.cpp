// --------------------
// ������:tCharacter
// --------------------
#include	"public.h"

void	InitMainCharacter(tCharacter* pCharacterList, const tJob* pJobList, int* npNum)
{
	tCharacter* pCh = pCharacterList;
	strcpy(pCh->szName, "�䂤����");
	pCh->job.nCode = 1;									// ���񂵁i�R�[�h:1�j
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// �E�ƍ\���̎擾
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// ��������
	pCh->nDef_Base = 7;									// �ڂ�����
	pCh->nMAtk_Base = 7;								// �܂ق���
	pCh->nMDef_Base = 7;								// �܂قڂ�
	pCh->nSpd_Base = 7;									// ���΂₳
	CalculateCharacterStatus(pCh);						// �X�e�[�^�X���Z�o
}
void	InitBuiltInCharacters(tCharacter* pBuiltInCharaList, const tJob* pJobList, int* npNum)
{
	tCharacter* pCh = pBuiltInCharaList;

	strcpy(pCh->szName, "�N���E�h");
	pCh->job.nCode = 1;									// ���񂵁i�R�[�h:1�j
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// �E�ƍ\���̎擾
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// ��������
	pCh->nDef_Base = 7;									// �ڂ�����
	pCh->nMAtk_Base = 7;								// �܂ق���
	pCh->nMDef_Base = 7;								// �܂قڂ�
	pCh->nSpd_Base = 7;									// ���΂₳
	CalculateCharacterStatus(pCh);						// �X�e�[�^�X���Z�o

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "�A�C�A�X");
	pCh->job.nCode = 2;									// �^���N�i�R�[�h:2�j
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// �E�ƍ\���̎擾
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// ��������
	pCh->nDef_Base = 7;									// �ڂ�����
	pCh->nMAtk_Base = 7;								// �܂ق���
	pCh->nMDef_Base = 7;								// �܂قڂ�
	pCh->nSpd_Base = 7;									// ���΂₳
	CalculateCharacterStatus(pCh);						// �X�e�[�^�X���Z�o

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "�����E�@");
	pCh->job.nCode = 3;									// �����Ƃ��i�R�[�h:3�j
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// �E�ƍ\���̎擾
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// ��������
	pCh->nDef_Base = 7;									// �ڂ�����
	pCh->nMAtk_Base = 7;								// �܂ق���
	pCh->nMDef_Base = 7;								// �܂قڂ�
	pCh->nSpd_Base = 7;									// ���΂₳
	CalculateCharacterStatus(pCh);						// �X�e�[�^�X���Z�o

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "�n���e�@");
	pCh->job.nCode = 4;									// �ɂ񂶂�i�R�[�h:4�j
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// �E�ƍ\���̎擾
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// ��������
	pCh->nDef_Base = 7;									// �ڂ�����
	pCh->nMAtk_Base = 7;								// �܂ق���
	pCh->nMDef_Base = 7;								// �܂قڂ�
	pCh->nSpd_Base = 7;									// ���΂₳
	CalculateCharacterStatus(pCh);						// �X�e�[�^�X���Z�o

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "�|�b�v�@");
	pCh->job.nCode = 5;									// �܂ق��i�R�[�h:5�j
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// �E�ƍ\���̎擾
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// ��������
	pCh->nDef_Base = 7;									// �ڂ�����
	pCh->nMAtk_Base = 7;								// �܂ق���
	pCh->nMDef_Base = 7;								// �܂قڂ�
	pCh->nSpd_Base = 7;									// ���΂₳
	CalculateCharacterStatus(pCh);						// �X�e�[�^�X���Z�o

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "�i�R����");
	pCh->job.nCode = 6;									// �݂��i�R�[�h:6�j
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// �E�ƍ\���̎擾
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// ��������
	pCh->nDef_Base = 7;									// �ڂ�����
	pCh->nMAtk_Base = 7;								// �܂ق���
	pCh->nMDef_Base = 7;								// �܂قڂ�
	pCh->nSpd_Base = 7;									// ���΂₳
	CalculateCharacterStatus(pCh);						// �X�e�[�^�X���Z�o
}

void	CalculateCharacterStatus(tCharacter* pCh)
{
	pCh->nHP = CalculateIndivisualStatus(pCh->nHP_Base, pCh->job.nHP, 10);
	pCh->nSP = CalculateIndivisualStatus(pCh->nSP_Base, pCh->job.nSP, 10);
	pCh->nAtk = CalculateIndivisualStatus(pCh->nAtk_Base, pCh->job.nAtk, 3);
	pCh->nDef = CalculateIndivisualStatus(pCh->nDef_Base, pCh->job.nDef, 3);
	pCh->nMAtk = CalculateIndivisualStatus(pCh->nMAtk_Base, pCh->job.nMAtk, 3);
	pCh->nMDef = CalculateIndivisualStatus(pCh->nMDef_Base, pCh->job.nMDef, 3);
	pCh->nSpd = CalculateIndivisualStatus(pCh->nSpd_Base, pCh->job.nSpd, 3);
}
int		CalculateIndivisualStatus(int nCBase, int nJBase, int nScale)
{
	int nStatus = 0;
	nStatus = nCBase * nJBase * nScale;
	return nStatus;
}