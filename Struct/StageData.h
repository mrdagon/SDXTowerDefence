//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Struct/EnumType.h"
#include "PlaceData.h"
#include "System/TDSystem.h"

namespace SDX_TD
{
	using namespace SDX;

	/**ステージの情報.*/
	struct StageData
	{
		std::string 名前;
		std::string 説明;

		struct Score
		{
			EnumArray<int, WitchType> スコア;
			EnumArray<Difficulty, WitchType> 達成度;
			EnumArray<Difficulty, WitchType> 完勝;
		};

		//全体の最高スコア
		//[isトライアル][isカップル]
		Score ハイスコア[2][2];//レベル制限あり

		int Wave間隔;

		EnemyType 敵種類[MAX_WAVE];
		bool	  isBoss[MAX_WAVE];
		ChipType  地形[MAP_SIZE][MAP_SIZE];

		Score& Getスコア()
		{
			return ハイスコア[TDSystem::isトライアル][TDSystem::isカップル];
		}

		//メインウィッチ種、トライアルorパワー
		std::vector<Place> 初期配置[(int)WitchType::COUNT][2];

		void DrawMinimap()
		{

		}

	};

	std::array<StageData,StageType::COUNT> StageDataS;//標準ステージ
	//追加ステージデータ

	void LoadStageS()
	{
		//ソフト起動時のみ行う
		//とりあえず暫定的に
		StageDataS[0].名前 = "チュートリアル";
		StageDataS[0].説明 = "テスト";
		StageDataS[0].Wave間隔 = 1000;

		for (StageData &it : StageDataS)
		{
			File enemyS("file/map/enemy_001.csv", FileMode::Read, true);
			auto data = enemyS.GetCsvToInt();

			//敵情報読み込み
			for (int a = 0; a < MAX_WAVE; ++a)
			{
				it.敵種類[a] = EnemyType(data[a] % 20);
				it.isBoss[a] = (data[a] >= 20);
			}

			File landS("file/map/map_001.csv", FileMode::Read, true);

			auto landData = landS.GetCsvToInt();

			for (int a = 0; a < MAP_SIZE * MAP_SIZE;++a)
			{
				it.地形[a % MAP_SIZE][a / MAP_SIZE] = ChipType(landData[a]);
			}
		}
	}

}