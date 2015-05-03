//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../System/EnumType.h"
#include "../System/Material.h"

namespace SDX_TD
{
	using namespace SDX;

	struct DifficultyData
	{
		std::string 名前;
		int Wave数[2];
		double レベル補正[2];
		double HP補正[2];
		int 雑魚召喚数[2];
		int ボス召喚数[2];

		void Set(int Wave数, int 雑魚召喚数, int ボス召喚数, double HP補正, double レベル補正, bool isトライアル)
		{
			int no = isトライアル;
			this->Wave数[no] = Wave数;
			this->雑魚召喚数[no] = 雑魚召喚数;
			this->ボス召喚数[no]= ボス召喚数;
			this->HP補正[no] = HP補正;
			this->レベル補正[no] = レベル補正;
		}
	};

	EnumArray<DifficultyData, Difficulty> DifficultyDataS;

	void LoadDifficultyS()
	{
		//外部テキスト化する意味は薄め
		DifficultyDataS[Difficulty::Easy].名前 = "Easy";
		DifficultyDataS[Difficulty::Normal].名前 = "Normal";
		DifficultyDataS[Difficulty::Hard].名前 = "Hard";
		DifficultyDataS[Difficulty::Maniac].名前 = "Maniac";
		DifficultyDataS[Difficulty::Hell].名前 = "Hell";
		DifficultyDataS[Difficulty::DeathMarch].名前 = "D-March";

		//Wave数,雑魚数,ボス数,HP補正,Lv補正
		DifficultyDataS[Difficulty::Easy].Set(20, 16, 2, 1.00, 1.00,true);
		DifficultyDataS[Difficulty::Normal].Set(30, 20, 2, 1.25, 1.10, true);
		DifficultyDataS[Difficulty::Hard].Set(40, 24, 2, 1.50, 1.20, true);
		DifficultyDataS[Difficulty::Maniac].Set(60, 28, 2, 1.75, 1.30, true);
		DifficultyDataS[Difficulty::Hell].Set(80, 32, 2, 2.00, 1.40, true);
		DifficultyDataS[Difficulty::DeathMarch].Set(100, 44, 2, 2.50, 1.50, true);

		DifficultyDataS[Difficulty::Easy].Set(25, 24, 3, 1.00, 1.00, false);
		DifficultyDataS[Difficulty::Normal].Set(50, 24, 3, 1.30, 1.20, false);
		DifficultyDataS[Difficulty::Hard].Set(75, 24, 3, 1.60, 1.40, false);
		DifficultyDataS[Difficulty::Maniac].Set(100, 32, 4, 2.00, 1.60, false);
		DifficultyDataS[Difficulty::Hell].Set(300, 32, 4, 3.00, 1.80, false);
		DifficultyDataS[Difficulty::DeathMarch].Set(1000, 40, 5, 5.00, 2.00, false);
	}
}