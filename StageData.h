//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"

namespace SDX_TD
{
	using namespace SDX;

	struct StageData
	{
		std::string 名前;
		std::string 説明;

		int シングルのハイスコア[(int)WitchType::COUNT];

		int タッグのハイスコア[3];
		std::tuple<WitchType, WitchType> タッグの組み合わせ[3];

		Difficulty シングルの達成難易度[(int)WitchType::COUNT];
		Difficulty タッグの達成難易度[3];

		double Wave速度;

		EnemyType 敵発生リスト[100];
		ChipType  地形情報[30][30];
	};

	namespace
	{
		EnumArray<StageData, StageType> StageDataS;
	}

	void LoadStageS()
	{
		StageDataS[StageType::一面].名前 = "チュートリアル";
		StageDataS[StageType::一面].Wave速度 = 4000;//基準
		StageDataS[StageType::一面].説明 = "テスト";
	}

}