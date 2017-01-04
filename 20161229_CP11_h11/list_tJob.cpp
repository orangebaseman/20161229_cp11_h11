// --------------------
// リスト構造：tJob
// --------------------
#include	"public.h"


tJob*	JobList_New()
{
	tJob* firstJob = (tJob*)malloc(sizeof(tJob));
	if (firstJob == NULL)
	{
		printf("メモリ確保失敗(malloc error on JobList_New)");
		rewind(stdin);
		getchar();
		exit(EXIT_FAILURE);
	}
	firstJob->prev = NULL;
	firstJob->next = NULL;
	return firstJob;
}
tJob*	JobList_Add(tJob* pJb, bool isAddToLast)
{
	tJob* newJob;
	if (isAddToLast)
	{
		while (pJb->next != NULL)
		{
			pJb = pJb->next;
		}
	}
	newJob = (tJob*)malloc(sizeof(tJob));
	if (newJob == NULL)
	{
		printf("メモリ確保失敗(malloc error on JobList_Add)");
		rewind(stdin);
		getchar();
		exit(EXIT_FAILURE);
	}
	if (pJb->next != NULL)
	{
		pJb->next->prev = newJob;
		newJob->next = pJb->next;
	}
	else
	{
		newJob->next = NULL;
	}
	pJb->next = newJob;
	newJob->prev = pJb;

	return newJob;
}
void	JobList_Delete(tJob* pJb)
{
	if (pJb == NULL) return;
	if (pJb->prev != NULL)
	{
		pJb->prev->next = pJb->next;
	}
	if (pJb->next != NULL)
	{
		pJb->next->prev = pJb->prev;
	}
	free(pJb);
	pJb = NULL;
}
void	JobList_DeleteAll(tJob* pJobList)
{
	tJob* pJb = pJobList;
	tJob* pNext;
	while (pJb != NULL)
	{
		pNext = pJb->next;
		JobList_Delete(pJb);
		pJb = pNext;
	}
}
