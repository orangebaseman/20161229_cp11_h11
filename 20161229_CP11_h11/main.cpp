// ---------------------------
// バトルコロシアム Light
// ---------------------------
#include	"public.h"

void main(void)
{
	// ---------------------------
	// 変数宣言,初期化
	// ---------------------------
	int menu= -1;															// 選択中のメニュー
	int numOfPartyMember	= 0;											// 現在のパーティメンバー人数
	int numOfBuiltInChara	= 0;											// 現在の組み込みキャラクター人数
	// 職業一覧リスト
	tJob* pJobList = JobList_New();											// リスト作成
	InitJobs(pJobList);														// 初期化
	// 組み込みキャラクター一覧リスト
	tCharacter* pBuiltInCharaList = CharacterList_New(&numOfBuiltInChara);	// リスト作成
	InitBuiltInCharacters(pBuiltInCharaList, pJobList, &numOfBuiltInChara);	// 初期化
	// キャラクター一覧リスト
	tCharacter* pCharacterList = CharacterList_New(&numOfPartyMember);		// リスト作成
	InitMainCharacter(pCharacterList, pJobList, &numOfPartyMember);			// 初期化（主人公を作成）

	// test
	tString* sList = StringList_New();
	strcpy(sList->szText, "１ぎょうめ２ぎょうめ３ぎょう");
	sList = StringList_Add_Blank(sList, true);
	strcpy(sList->szText, "４ぎょうめ５ぎょうめ６ぎょう");
	sList= StringList_Add_Blank(sList, true);
	strcpy(sList->szText, "７ぎょうめ８ぎょうめ９ぎょう");
	tString* pTextList = StringList_New();
	

	StringList_DeleteAll(sList);
	StringList_DeleteAll(pTextList);

	// ---------------------------
	// シーン選択、実行　（０で終了）
	// ---------------------------
	while (menu != 0)
	{
		// ---------------------------
		// シーン：メニュー選択
		// ---------------------------
		Execute_MenuScene(&menu);
		switch (menu)
		{
		case 1:
			// ---------------------------
			// シーン 1：キャラクター作成
			// ---------------------------
			Execute_CreateScene(pCharacterList, pBuiltInCharaList, pJobList, &numOfPartyMember, numOfBuiltInChara);
			getchar();
			break;
		case 2:
			// ---------------------------
			// シーン 2：キャラクター更新
			// ---------------------------
			Execute_UpdateMemberScene(pCharacterList, pJobList, numOfPartyMember);
			getchar();
			break;
		case 3:
			// ---------------------------
			// シーン 3：キャラクター削除
			// ---------------------------
			Execute_DeleteMemberScene(pCharacterList, &numOfPartyMember);
			getchar();
			break;
		case 4:
			// ---------------------------
			// シーン 4：キャラクター表示
			// ---------------------------
			Execute_ShowMemberScene(pCharacterList);
			getchar();
			break;
		}
	}

	printf("\n  さようなら また　おこしくださいませ");
	
	JobList_DeleteAll(pJobList);
	CharacterList_DeleteAll(pCharacterList);
	
	// ---------------------------
	// ストッパとしての入力待ち
	// ---------------------------
	rewind(stdin);
	getchar();
}

