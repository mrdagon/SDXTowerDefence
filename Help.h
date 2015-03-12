//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"

namespace SDX_TD
{
	using namespace SDX;

	//メニュー項目を配置
	class Help : public IScene
	{
	public:
		Help()
		{
		}

		void Update() override
		{
			namespace UI = UI_Help;

		}

		void Draw() override
		{
			namespace UI = UI_Help;
			//項目を選ぶとメッセージが表示される

			//下に戻るボタン
		}
	};
}