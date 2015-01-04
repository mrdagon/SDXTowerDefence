//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "Design.h"
#include "StageSelect.h"

namespace SDX_TD
{
	using namespace SDX;

	/** サブメニュー用オブジェクト、ミッション中にメニュー開いて一時停止.*/
	/** @todo 仮実装*/
	/** 位置情報はほぼ無駄*/
	class Result : public IScene
	{
	public:
		Result()
		{
			Director::IsDraw() = true;
		}

		void Update()
		{
			namespace UI = UI_Result;

			if (!Input::mouse.Left.on) { return; }

			const Point pt = Input::mouse.GetPoint();

			if (UI::Rリトライ.Hit(&pt))
			{
				SStage->Init();
				isEnd = true;
			}
			if (UI::R終了.Hit(&pt))
			{
				//暫定的に難易度選択から
				Director::AddScene(std::make_shared<StageSelect>());
				isEnd = true;
			}
		}

		void Draw()
		{
			namespace UI = UI_Result;
			//暗くステージ状況を描画
			Screen::SetBright(Color::Gray);
			SStage->Draw();
			Screen::SetBright(Color::White);

			//成果等を表示

			//勝ち負け

			//スコア

			//リトライとかのボタン

			Point def = { 17, 19 };
			MSystem::フレーム[3].Draw(UI::Rリトライ);
			MFont::ゴシック中.DrawRotate(UI::Rリトライ.GetPoint() + def, 2, 0, Color::Black, false, { "リトライ" });

			//続ける
			MSystem::フレーム[3].Draw(UI::R終了);
			MFont::ゴシック中.DrawRotate(UI::R終了.GetPoint() + def, 2, 0, Color::Black, false, { "終了" });
		}
	};
}