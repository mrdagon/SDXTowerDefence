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

	/** α版用の難易度選択.*/
	/** @todo 仮実装*/
	class StageSelect : public IScene
	{
	public:
		StageSelect()
		{
			Director::IsDraw() = true;
		}

		void Update()
		{
			namespace UI = UI_StageSelect;

			if (!Input::mouse.Left.on) { return; }

			const Point pt = Input::mouse.GetPoint();

			for (int a = 0; a < (int)Difficulty::COUNT; ++a)
			{
				if (UI::R難易度[a].Hit(&pt))
				{
					TDSystem::難易度 = Difficulty(a);
					isEnd = true;
					SStage->Init();
				}
			}
		}

		void Draw()
		{
			namespace UI = UI_StageSelect;
			const Point def = { 17, 19 };

			//暗くステージ状況を描画
			Screen::SetBright(Color::Gray);
			SStage->Draw();
			Screen::SetBright(Color::White);

			//難易度一覧
			for (int a = 0; a < (int)Difficulty::COUNT; ++a)
			{
				const Difficulty no = (Difficulty)a;

				MSystem::フレーム[3].Draw(UI::R難易度[a]);
				MFont::ゴシック中.DrawRotate(UI::R難易度[a].GetPoint() + def ,2,0, Color::Black , DifficultyDataS[no].名前, false);
			}
		}
	};
}