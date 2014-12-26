//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "Design.h"

namespace SDX_TD
{
	using namespace SDX;

	/** サブメニュー用オブジェクト、ミッション中にメニュー開いて一時停止.*/
	/** @todo 仮実装*/
	/** 位置情報はほぼ無駄*/
	class Pause : IScene
	{
	public:
		Pause()
		{}

		void Update()
		{
			namespace UI = UI_Pause;

			if (!Input::mouse.Left.on) { return; }

			const Point pt = Input::mouse.GetPoint();

			if (UI::Rあきらめる.Hit(&pt))
			{
				isEnd = true;
			}
			if (UI::Rやり直す.Hit(&pt))
			{
				isEnd = true;
			}
			if (UI::R続ける.Hit(&pt))
			{
				isEnd = true;
			}
		}

		void Draw()
		{
			namespace UI = UI_Pause;
			//暗くステージ状況を描画
			Screen::SetBright(Color::Gray);
			Director::GetScene(-1)->Draw();
			Screen::SetBright(Color::White);

			//リスタート
			MSystem::フレーム[0].Draw(UI::Rやり直す);
			//リタイア
			MSystem::フレーム[0].Draw(UI::Rあきらめる);
			//続ける
			MSystem::フレーム[0].Draw(UI::R続ける);
		}
	};
}