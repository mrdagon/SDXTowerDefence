//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
namespace SDX_TD
{
	using namespace SDX;
	/**初期配置の情報.*/
	struct Place
	{
		Point 座標;
		int Lv;
		UnitType 職種;
		Place(const Point &座標, int Lv, UnitType 職種) :
			座標(座標),
			Lv(Lv),
			職種(職種)
		{}
	};
}