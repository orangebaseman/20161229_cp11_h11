// --------------------
// 初期化：tJob
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

	// 1 : けんし
	pJb->nCode = 1;
	strcpy(pJb->szName, "けんし　");
	pJb->nHP = 2;
	pJb->nSP = 4;
	pJb->nAtk = 5;
	pJb->nDef = 3;
	pJb->nMAtk = 2;
	pJb->nMDef = 3;
	pJb->nSpd = 3;

	// 2 : タンク
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 2;
	strcpy(pJb->szName, "タンク　");
	pJb->nHP = 5;
	pJb->nSP = 1;
	pJb->nAtk = 2;
	pJb->nDef = 5;
	pJb->nMAtk = 1;
	pJb->nMDef = 2;
	pJb->nSpd = 1;

	// 3 : かくとう
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 3;
	strcpy(pJb->szName, "かくとう");
	pJb->nHP = 4;
	pJb->nSP = 4;
	pJb->nAtk = 4;
	pJb->nDef = 3;
	pJb->nMAtk = 2;
	pJb->nMDef = 3;
	pJb->nSpd = 4;

	// 4 : にんじゃ
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 4;
	strcpy(pJb->szName, "にんじゃ");
	pJb->nHP = 2;
	pJb->nSP = 3;
	pJb->nAtk = 3;
	pJb->nDef = 2;
	pJb->nMAtk = 3;
	pJb->nMDef = 1;
	pJb->nSpd = 5;

	// 5 : まほう
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 5;
	strcpy(pJb->szName, "まほう　");
	pJb->nHP = 1;
	pJb->nSP = 4;
	pJb->nAtk = 2;
	pJb->nDef = 1;
	pJb->nMAtk = 5;
	pJb->nMDef = 3;
	pJb->nSpd = 2;

	// 6 : みこ
	pJb = JobList_Add(pJb, true);
	pJb->nCode = 6;
	strcpy(pJb->szName, "み　　こ");
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
		printf("範囲外の職業コードへアクセスしました");
		rewind(stdin);
		getchar();
		exit(EXIT_FAILURE);
	}

	return job;
}
