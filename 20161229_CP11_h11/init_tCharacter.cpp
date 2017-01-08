// --------------------
// 初期化:tCharacter
// --------------------
#include	"public.h"

void	InitMainCharacter(tCharacter* pCharacterList, const tJob* pJobList, int* npNum)
{
	tCharacter* pCh = pCharacterList;
	strcpy(pCh->szName, "ゆうしゃ");
	pCh->job.nCode = 1;									// けんし（コード:1）
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// 職業構造体取得
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// こうげき
	pCh->nDef_Base = 7;									// ぼうぎょ
	pCh->nMAtk_Base = 7;								// まほこう
	pCh->nMDef_Base = 7;								// まほぼう
	pCh->nSpd_Base = 7;									// すばやさ
	CalculateCharacterStatus(pCh);						// ステータスを算出
}
void	InitBuiltInCharacters(tCharacter* pBuiltInCharaList, const tJob* pJobList, int* npNum)
{
	tCharacter* pCh = pBuiltInCharaList;

	strcpy(pCh->szName, "クラウド");
	pCh->job.nCode = 1;									// けんし（コード:1）
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// 職業構造体取得
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// こうげき
	pCh->nDef_Base = 7;									// ぼうぎょ
	pCh->nMAtk_Base = 7;								// まほこう
	pCh->nMDef_Base = 7;								// まほぼう
	pCh->nSpd_Base = 7;									// すばやさ
	CalculateCharacterStatus(pCh);						// ステータスを算出

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "アイアス");
	pCh->job.nCode = 2;									// タンク（コード:2）
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// 職業構造体取得
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// こうげき
	pCh->nDef_Base = 7;									// ぼうぎょ
	pCh->nMAtk_Base = 7;								// まほこう
	pCh->nMDef_Base = 7;								// まほぼう
	pCh->nSpd_Base = 7;									// すばやさ
	CalculateCharacterStatus(pCh);						// ステータスを算出

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "リュウ　");
	pCh->job.nCode = 3;									// かくとう（コード:3）
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// 職業構造体取得
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// こうげき
	pCh->nDef_Base = 7;									// ぼうぎょ
	pCh->nMAtk_Base = 7;								// まほこう
	pCh->nMDef_Base = 7;								// まほぼう
	pCh->nSpd_Base = 7;									// すばやさ
	CalculateCharacterStatus(pCh);						// ステータスを算出

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "ハヤテ　");
	pCh->job.nCode = 4;									// にんじゃ（コード:4）
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// 職業構造体取得
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// こうげき
	pCh->nDef_Base = 7;									// ぼうぎょ
	pCh->nMAtk_Base = 7;								// まほこう
	pCh->nMDef_Base = 7;								// まほぼう
	pCh->nSpd_Base = 7;									// すばやさ
	CalculateCharacterStatus(pCh);						// ステータスを算出

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "ポップ　");
	pCh->job.nCode = 5;									// まほう（コード:5）
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// 職業構造体取得
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// こうげき
	pCh->nDef_Base = 7;									// ぼうぎょ
	pCh->nMAtk_Base = 7;								// まほこう
	pCh->nMDef_Base = 7;								// まほぼう
	pCh->nSpd_Base = 7;									// すばやさ
	CalculateCharacterStatus(pCh);						// ステータスを算出

	pCh = CharacterList_Add_Blank(pCh, npNum, true);
	strcpy(pCh->szName, "ナコルル");
	pCh->job.nCode = 6;									// みこ（コード:6）
	pCh->job = getJobByCode(pCh->job.nCode, pJobList);	// 職業構造体取得
	pCh->nHP_Base = 7;									// HP
	pCh->nSP_Base = 7;									// SP
	pCh->nAtk_Base = 7;									// こうげき
	pCh->nDef_Base = 7;									// ぼうぎょ
	pCh->nMAtk_Base = 7;								// まほこう
	pCh->nMDef_Base = 7;								// まほぼう
	pCh->nSpd_Base = 7;									// すばやさ
	CalculateCharacterStatus(pCh);						// ステータスを算出
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