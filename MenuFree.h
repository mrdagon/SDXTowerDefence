//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "IStage.h"
#include "Object.h"
#include "Design.h"
#include "TDSystem.h"

namespace SDX_TD
{
	using namespace SDX;

	/** 難易度,モード,ステージ,使用ウィッチの選択選択.*/
	/** QuestSelectとレイアウトを似せる*/
	/** @todo 仮実装*/
	class MenuFree : public IScene
	{
		void Update() override
		{
			namespace UI = UI_FreeSelect;
		}

		void Draw() override
		{
			namespace UI = UI_FreeSelect;
			MFont::ゴシック中.Draw({ 260, 240 }, Color::White, { "・・・Freeモード実装中・・・" });
		}
	};
}