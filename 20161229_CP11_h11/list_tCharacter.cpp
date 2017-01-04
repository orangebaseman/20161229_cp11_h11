// --------------------
// リスト構造：tCharacter
// --------------------
#include	"public.h"

tCharacter*	CharacterList_New(int* pNum)
{
	tCharacter* firstCh = (tCharacter*)malloc(sizeof(tCharacter));
	if (firstCh == NULL)
	{
		printf("メモリ確保失敗(malloc error on CharacterList_New)");
		rewind(stdin);
		getchar();
		exit(EXIT_FAILURE);
	}
	firstCh->prev = NULL;
	firstCh->next = NULL;

	(*pNum)++;
	return firstCh;
}
tCharacter*	CharacterList_Add(tCharacter* pCh, int* pNum, bool isAddToLast)
{
	if (isAddToLast)
	{
		while (pCh->next != NULL)
		{
			pCh = pCh->next;
		}
	}
	tCharacter* newCh = (tCharacter*)malloc(sizeof(tCharacter));
	if (newCh == NULL)
	{
		printf("メモリ確保失敗(malloc error)");
		rewind(stdin);
		getchar();
		exit(EXIT_FAILURE);
	}
	if (pCh->next != NULL)
	{
		pCh->next->prev = newCh;
		newCh->next = pCh->next;
	}
	else
	{
		newCh->next = NULL;
	}
	pCh->next = newCh;
	newCh->prev = pCh;

	(*pNum)++;

	return newCh;
}
void		CharacterList_Delete(tCharacter* pCh)
{
	if (pCh == NULL) return;
	if (pCh->prev != NULL)
	{
		pCh->prev->next = pCh->next;
	}
	if (pCh->next != NULL)
	{
		pCh->next->prev = pCh->prev;
	}
	free(pCh);
	pCh = NULL;
}
void		CharacterList_DeleteAll(tCharacter* pCharacterList)
{
	tCharacter* pCh = pCharacterList;
	tCharacter* pNext;
	while (pCh != NULL)
	{
		pNext = pCh->next;
		CharacterList_Delete(pCh);
		pCh = pNext;
	}
}
