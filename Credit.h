//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"

namespace SDX_TD
{
	using namespace SDX;

	//メニュー項目を配置
	class Credit : public IScene
	{
	public:
		Credit(){}

		void Update() override
		{
			//戻るボタンor右クリックで戻る

		}

		void Draw() override
		{
			//下に戻るボタン
			//Creditを表示
		}
	};
}