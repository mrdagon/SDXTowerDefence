//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"
#include "MenuMain.h"

namespace SDX_TD
{
	using namespace SDX;

	//メニュー項目を配置
	class MenuTitle : public IScene
	{
	public:
		MenuTitle()
		{
		}

		void Update() override
		{
			namespace UI = UI_Title;
			UI::Reset();

		}

		void Draw() override
		{
			namespace UI = UI_Title;
		}
	};
}