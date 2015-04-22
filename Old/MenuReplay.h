//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"

namespace SDX_TD
{
	using namespace SDX;

	//メニュー項目を配置
	class MenuReplay : public IScene
	{
	public:
		void Update() override
		{
			namespace UI = UI_Replay;

		}

		void Draw() override
		{
			namespace UI = UI_Replay;
			//左にリスト、右に詳細
			
		}
	};
}