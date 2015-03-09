//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"

namespace SDX_TD
{
	using namespace SDX;

	/** スキルポイント割り振り画面画面*/
	/** @todo .*/
	class SkillMenu : public Menu
	{
	public:
		EnumArray<int, SkillType> 最大Lv;

		SkillMenu()
		{
			//初期化時に最大スキルレベルを計算

			Director::IsDraw() = true;
		}

		void Update()
		{

		}

		void Draw()
		{
			//上にセットアイコンを表示
			//右にスキルアイコンを表示
			//左に説明を表示

			//合計ポイントと使用ポイントを隅に表示
			//戻るボタンを隅に表示
		}

	};
}