//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"

namespace SDX_TD
{
	using namespace SDX;

	namespace Land
	{
		static const int MapSize = 32;
		static const int ChipSize = 16;
		static const int 到達不可 = 99999999;
		static const double 自動床速度 = 0.5;
	}

	struct ChipData
	{
		bool is配置可能;
		bool is陸移動;
		bool is水上移動;

		void Set(bool is配置可能, bool is陸移動, bool is水上移動)
		{
			this->is配置可能 = is配置可能;
			this->is陸移動 = is陸移動;
			this->is水上移動 = is水上移動;
		}
	};

	namespace
	{
		EnumArray<ChipData, ChipType> ChipDataS;
	}

	void LoadChipS()
	{
		//配置,陸,海
		ChipDataS[ChipType::草].Set(true, true, true);
		ChipDataS[ChipType::沼].Set(true, true, true);
		ChipDataS[ChipType::森].Set(true, false, false);
		ChipDataS[ChipType::道].Set(false, true, true);
		ChipDataS[ChipType::橋].Set(false, true, true);
		ChipDataS[ChipType::↑].Set(true, true, true);
		ChipDataS[ChipType::↓].Set(true, true, true);
		ChipDataS[ChipType::←].Set(true, true, true);
		ChipDataS[ChipType::→].Set(true, true, true);
		ChipDataS[ChipType::山].Set(false, false, false);
		ChipDataS[ChipType::水].Set(false, false, true);
		ChipDataS[ChipType::穴].Set(false, true, true);
		ChipDataS[ChipType::畑].Set(false, true, true);
		ChipDataS[ChipType::高山].Set(false, false, false);
	}
}