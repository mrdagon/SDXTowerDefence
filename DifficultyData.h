//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"
#include "Material.h"

namespace SDX_TD
{
	using namespace SDX;

	struct DifficultyData
	{
		std::string 名前;
		int Wave数;
		double レベル補正;
		double HP補正;
		int 雑魚召喚数;
		int ボス召喚数;

		void Set(int Wave数, int 雑魚召喚数, int ボス召喚数, double HP補正, double レベル補正)
		{
			this->Wave数 = Wave数;
			this->雑魚召喚数 = 雑魚召喚数;
			this->ボス召喚数 = ボス召喚数;
			this->HP補正 = HP補正;
			this->レベル補正 = レベル補正;
		}
	};

	namespace
	{
		EnumArray<DifficultyData, Difficulty> TrialDataS;
		EnumArray<DifficultyData, Difficulty> PowerDataS;
	}

	void LoadDifficultyS()
	{
		//Wave数,雑魚数,ボス数,HP補正,Lv補正
		TrialDataS[Difficulty::Easy].Set(20, 16, 2, 1.00, 1.00);
		TrialDataS[Difficulty::Normal].Set(30, 20, 2, 1.25, 1.10);
		TrialDataS[Difficulty::Hard].Set(40, 24, 2, 1.50, 1.20);
		TrialDataS[Difficulty::Maniac].Set(60, 28, 2, 1.75, 1.30);
		TrialDataS[Difficulty::Hell].Set(80, 32, 2, 2.00, 1.40);
		TrialDataS[Difficulty::DeathMarch].Set(100, 44, 2, 2.50, 1.50);

		PowerDataS[Difficulty::Easy].Set(25, 24, 3, 1.00, 1.00);
		PowerDataS[Difficulty::Normal].Set(50, 24, 3, 1.30, 1.20);
		PowerDataS[Difficulty::Hard].Set(75, 24, 3, 1.60, 1.40);
		PowerDataS[Difficulty::Maniac].Set(100, 32, 4, 2.00, 1.60);
		PowerDataS[Difficulty::Hell].Set(300, 32, 4, 3.00, 1.80);
		PowerDataS[Difficulty::DeathMarch].Set(1000, 40, 5, 5.00, 2.00);
	}
}