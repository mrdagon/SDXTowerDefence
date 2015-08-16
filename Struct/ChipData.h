//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../System/EnumType.h"

namespace SDX_TD
{
	using namespace SDX;

	struct ChipData
	{
		bool is配置可能;
		bool is陸移動;
		bool is水移動;
		//空不可は高山のみ
		void Set(bool is配置可能, bool is陸移動, bool is水移動)
		{
			this->is配置可能 = is配置可能;
			this->is陸移動 = is陸移動;
			this->is水移動 = is水移動;
		}
	};

	EnumArray<ChipData, ChipType> ChipDataS;

	void LoadChipS()
	{
		//配置,陸,海
		ChipDataS[ChipType::草].Set(true, true, true);
		ChipDataS[ChipType::沼].Set(true, true, true);
		ChipDataS[ChipType::森].Set(true, false, false);
		ChipDataS[ChipType::砂].Set(false, true, true);
		ChipDataS[ChipType::道].Set(true, true, true);
		ChipDataS[ChipType::山].Set(false, false, false);
		ChipDataS[ChipType::水].Set(false, false, true);
		ChipDataS[ChipType::穴].Set(false, true, true);
		ChipDataS[ChipType::畑].Set(false, true, true);
		ChipDataS[ChipType::星].Set(true, false, false);
	}
}