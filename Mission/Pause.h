//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "Design.h"
#include "IStage.h"
#include "StageSelect.h"

namespace SDX_TD
{
	using namespace SDX;

	/** サブメニュー用オブジェクト、ミッション中にメニュー開いて一時停止.*/
	/** @todo 仮実装*/
	/** 位置情報はほぼ無駄*/
	class Pause : public IScene
	{
	public:
		Pause()
		{
			Director::IsDraw() = true;
		}

		void Update()
		{
			namespace UI = UI_Pause;
			UI_Reset();

			if (!Input::mouse.Left.on) { return; }

			const Point pt = Input::mouse.GetPoint();

			if (UI::Rあきらめる.Hit(&pt))
			{
				//難易度選択から
				Director::AddScene(std::make_shared<StageSelect>());
				isEnd = true;
			}
			if (UI::Rやり直す.Hit(&pt))
			{
				SStage->Init();
				isEnd = true;
			}
			if (UI::R続ける.Hit(&pt))
			{
				//何もしない
				isEnd = true;
			}
		}

		void Draw()
		{
			namespace UI = UI_Pause;

			//暗くステージ状況を描画
			Screen::SetBright(Color::Gray);
			SStage->Draw();
			Screen::SetBright(Color::White);

			Point def = { 17, 19 };

			//リタイア
			MSystem::フレーム[3].Draw(UI::Rあきらめる);
			MFont::ゴシック中.DrawRotate(UI::Rあきらめる.GetPoint() + def , 2, 0, Color::Black,{ "あきらめる" });

			//リスタート
			MSystem::フレーム[3].Draw(UI::Rやり直す);
			MFont::ゴシック中.DrawRotate(UI::Rやり直す.GetPoint() + def , 2, 0, Color::Black,{ "やり直す" });

			//続ける
			MSystem::フレーム[3].Draw(UI::R続ける);
			MFont::ゴシック中.DrawRotate(UI::R続ける.GetPoint() + def , 2, 0, Color::Black,{ "続ける" });

		}
	};
}