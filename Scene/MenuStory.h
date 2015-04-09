//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Design.h"
#include "System/TDSystem.h"

namespace SDX_TD
{
	using namespace SDX;

	/** 難易度,ステージの選択.*/
	/** @todo 1.03 非実装*/
	class MenuStory : public IScene
	{
		void Update() override
		{
			namespace UI = UI_StorySelect;
		}

		void Draw() override
		{
			namespace UI = UI_StorySelect;

			//未実装的なメッセージを仮に表示
			MFont::ゴシック中.Draw({ 260, 240 }, Color::White, {"・・・Storyモード実装中・・・"});
		}
	};



}