// --------------------
// �������FtJob
// --------------------
#include	"public.h"

void	InitJobs(tJob* pJobList)
{
	tJob* pJb;
	pJb = pJobList;

	if (pJb == NULL)
	{
		pJb = JobList_New();
	}

	// 1 : ����
	pJb->nCode = 1;
	strcpy(pJb->szName, "���񂵁@");
	pJb->nHP = 2;
	pJb->nSP = 4;
	pJb->nAtk = 5;
	pJb->nDef = 3;
	pJb->nMAtk = 2;
	pJb->nMDef = 3;
	pJb->nSpd = 3;

	// 2 : �^���N
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 2;
	strcpy(pJb->szName, "�^���N�@");
	pJb->nHP = 5;
	pJb->nSP = 1;
	pJb->nAtk = 2;
	pJb->nDef = 5;
	pJb->nMAtk = 1;
	pJb->nMDef = 2;
	pJb->nSpd = 1;

	// 3 : �����Ƃ�
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 3;
	strcpy(pJb->szName, "�����Ƃ�");
	pJb->nHP = 4;
	pJb->nSP = 4;
	pJb->nAtk = 4;
	pJb->nDef = 3;
	pJb->nMAtk = 2;
	pJb->nMDef = 3;
	pJb->nSpd = 4;

	// 4 : �ɂ񂶂�
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 4;
	strcpy(pJb->szName, "�ɂ񂶂�");
	pJb->nHP = 2;
	pJb->nSP = 3;
	pJb->nAtk = 3;
	pJb->nDef = 2;
	pJb->nMAtk = 3;
	pJb->nMDef = 1;
	pJb->nSpd = 5;

	// 5 : �܂ق�
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 5;
	strcpy(pJb->szName, "�܂ق��@");
	pJb->nHP = 1;
	pJb->nSP = 4;
	pJb->nAtk = 2;
	pJb->nDef = 1;
	pJb->nMAtk = 5;
	pJb->nMDef = 3;
	pJb->nSpd = 2;

	// 6 : �݂�
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 6;
	strcpy(pJb->szName, "�݁@�@��");
	pJb->nHP = 4;
	pJb->nSP = 5;
	pJb->nAtk = 1;
	pJb->nDef = 2;
	pJb->nMAtk = 3;
	pJb->nMDef = 5;
	pJb->nSpd = 2;
}
tJob	getJobByCode(int nCode, const tJob* pJobList)
{
	tJob job;
	job.nCode = -1;
	const tJob* pJb = pJobList;
	while (pJb != NULL)
	{
		if (nCode == pJb->nCode)
		{
			job = (*pJb);
			break;
		}
		pJb = pJb->next;
	}

	if (job.nCode == -1)
	{
		printf("�͈͊O�̐E�ƃR�[�h�փA�N�Z�X���܂���");
		rewind(stdin);
		getchar();
		exit(EXIT_FAILURE);
	}

	return job;
}
