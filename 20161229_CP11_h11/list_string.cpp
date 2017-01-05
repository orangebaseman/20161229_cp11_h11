// --------------------
// リスト構造：文字リスト
// --------------------
#include	"public.h"

tString*	StringList_New(const char* pChar)
{
	tString* firstString = StringList_New_Blank();
	strcpy(firstString->szText, pChar);
	return firstString;
}

tString*	StringList_New_Blank()
{
	tString* firstString = (tString*)malloc(sizeof(tString));
	if (firstString == NULL)
	{
		printf("メモリ確保失敗(malloc error on StringList_New_Blank)");
		rewind(stdin);
		getchar();
		exit(EXIT_FAILURE);
	}
	firstString->prev = NULL;
	firstString->next = NULL;
	return firstString;
}
tString*	StringList_Add(tString* pStr, const char* pChar, bool isAddToLast)
{
	tString *pNewStr = StringList_Add_Blank(pStr, isAddToLast);
	strcpy(pNewStr->szText, pChar);
	return pNewStr;
}
tString*	StringList_Add_Blank(tString* pStr, bool isAddToLast)
{
	tString* newStr;
	if (isAddToLast)
	{
		pStr = StringList_Last(pStr);
	}
	newStr = (tString*)malloc(sizeof(tString));
	if (newStr == NULL)
	{
		printf("メモリ確保失敗(malloc error on StringList_Add_Blank)");
		rewind(stdin);
		getchar();
		exit(EXIT_FAILURE);
	}
	if (pStr->next != NULL)
	{
		pStr->next->prev = newStr;
		newStr->next = pStr->next;
	}
	else
	{
		newStr->next = NULL;
	}
	pStr->next = newStr;
	newStr->prev = pStr;

	return newStr;
}
void	StringList_Delete(tString* pStr)
{
	if (pStr == NULL) return;
	if (pStr->prev != NULL)
	{
		pStr->prev->next = pStr->next;
	}
	if (pStr->next != NULL)
	{
		pStr->next->prev = pStr->prev;
	}
	free(pStr);
	pStr = NULL;
}
void	StringList_DeleteAll(tString* pStringList)
{
	tString* pStr = pStringList;
	tString* pNext;
	while (pStr != NULL)
	{
		pNext = pStr->next;
		StringList_Delete(pStr);
		pStr = pNext;
	}
}
tString*	StringList_First(tString* pStr)
{
	while (pStr->prev != NULL)
	{
		pStr = pStr->prev;
	}
	return pStr;
}
tString*	StringList_Last(tString* pStr)
{
	while (pStr->next != NULL)
	{
		pStr = pStr->next;
	}
	return pStr;
}