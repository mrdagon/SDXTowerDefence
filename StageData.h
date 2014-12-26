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

		struct Score
		{
			EnumArray<int, WitchType> シングル;
			int カップル[3];
			std::tuple<WitchType, WitchType> カップリング[3];
			Difficulty シングル達成度[(int)WitchType::COUNT];
			Difficulty カップル達成度[3];
		};

		Score トライアル;//レベル制限あり
		Score リミットレス;//レベル制限無し

		int Wave間隔;

		EnemyType 敵種類[MAX_WAVE];
		bool	  isBoss[MAX_WAVE];
		ChipType  地形情報[MAP_SIZE][MAP_SIZE];
	};

	EnumArray<StageData, StageType> StageDataS;

	void LoadStageS()
	{
		//とりあえず暫定的に
		StageDataS[StageType::一面].名前 = "チュートリアル";
		StageDataS[StageType::一面].Wave間隔 = 600;
		StageDataS[StageType::一面].説明 = "テスト";

		for (StageData &it : StageDataS)
		{
			File enemyS("File/Map/enemy_001.csv", FileMode::Read, true);
			auto data = enemyS.GetCsvToInt();

			for (int a = 0; a < MAX_WAVE; ++a)
			{
				it.敵種類[a] = EnemyType(data[a] % 20);
				it.isBoss[a] = (data[a] >= 20);
			}
		}
	}

	void SaveOrLoadScore(FileMode 保存or読込)
	{

	}

}