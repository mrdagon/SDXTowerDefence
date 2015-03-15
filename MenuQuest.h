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

	/** ウィッチ選択ウィンドウモード*/
	class WitchSelect : public IScene
	{
	private:
		bool isメイン;
	public:
		WitchSelect(bool isメイン):
			isメイン(isメイン)
		{

		}

		void Update()
		{
			namespace UI = UI_Result;

			if (!Input::mouse.Left.on) { return; }

			const Point pt = Input::mouse.GetPoint();

			//リプレイ保存ボタン、1回だけ保存出来る
			if (UI::Rリトライ.Hit(&pt))
			{
				SStage->Init();
				isEnd = true;
			}
			if (UI::R終了.Hit(&pt))
			{
				//ステージ選択画面に戻る
				isEnd = true;
				SStage->isEnd = true;
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

			//スコア更新等の表示

			//レベルアップの表示

			//ボタン類
			Point def = { 17, 19 };
			//リトライ
			MSystem::フレーム[3].Draw(UI::Rリトライ);
			MFont::ゴシック中.DrawRotate(UI::Rリトライ.GetPoint() + def, 2, 0, Color::Black, { "リトライ" });

			//終了
			MSystem::フレーム[3].Draw(UI::R終了);
			MFont::ゴシック中.DrawRotate(UI::R終了.GetPoint() + def, 2, 0, Color::Black, { "終了" });

			//リプレイ保存ボタン～保存済みだと済マーク付ける			
		}

	};

	/** 難易度,モード,ステージ,使用ウィッチの選択選択.*/
	/** @todo 仮実装*/
	class MenuQuest : public IScene
	{
	public:
		void Update()
		{
			namespace UI = UI_QuestSelect;
			UI::Reset();

			if (!Input::mouse.Left.on) { return; }
			const Point pt = Input::mouse.GetPoint();

			for (int a = 0; a < 20; ++a)
			{
				if (UI::Rステージ[a].Hit(&pt))
				{
					TDSystem::選択ステージ = a;
				}
			}

			if (UI::R難易度Up.Hit(&pt))
			{
				int no = (int)TDSystem::難易度 + 1;
				if (no > (int)TDSystem::限界難易度){ no = 0; }
				TDSystem::難易度 = Difficulty(no);
			}

			if (UI::R難易度Down.Hit(&pt))
			{
				int no = (int)TDSystem::難易度 -1;
				if (no < 0 ){ no = (int)TDSystem::限界難易度; }
				TDSystem::難易度 = Difficulty(no);
			}

			if (UI::Rトライアル.Hit(&pt))
			{
				TDSystem::isトライアル = !TDSystem::isトライアル;
			}

			if (UI::Rカップル.Hit(&pt))
			{
				TDSystem::isカップル = !TDSystem::isカップル;
			}

			if (UI::R開始.Hit(&pt))
			{
				Director::AddScene(std::make_shared<Stage>());
			}
		}

		void Draw()
		{
			namespace UI = UI_QuestSelect;

			//難易度
			MFont::BMP黒.Draw( UI::P難易度 , Color::White, { "Easy" });
			MIcon::UI[IconType::マナ].Draw( UI::P難易度Up );
			MIcon::UI[IconType::マナ].Draw( UI::P難易度Down );
			MSystem::フレーム[3].Draw(UI::R難易度Up);
			MSystem::フレーム[3].Draw(UI::R難易度Down);

			//トライアルボタン
			MFont::BMP黒.Draw( UI::Pモード , Color::White, { "Trial" });
			MSystem::フレーム[3].Draw(UI::Rトライアル);

			//カップルボタン
			MFont::BMP黒.Draw(UI::Pモード, Color::White, { "Single" });
			MSystem::フレーム[3].Draw(UI::Rカップル);

			//ステージアイコン
			for (int a = 0; a < (int)StageType::COUNT; ++a)
			{
				//選択中の枠は色変更
				MSystem::フレーム[0].Draw(UI::Rステージ[a]);
				MIcon::魔導具[WitchType::トレニア].Draw(UI::Rステージ[a].GetPoint());
			}

			//ウィッチ＆スコア
			for (int a = 0; a < (int)WitchType::COUNT; ++a)
			{
				auto no = UnitType(a);
				auto wNo = WitchType(a);

				int score = StageDataS[a].Getスコア().スコア[wNo];
				int 銀星 = (int)StageDataS[a].Getスコア().達成度[wNo];
				int 金星 = (int)StageDataS[a].Getスコア().完勝[wNo];

				MUnit::魔女[no][1]->DrawRotate( UI::Pウィッチ[a], 2, 0);
				MFont::BMP黒.DrawRotate(UI::Pウィッチ[a], 2, 0, Color::White, { score });

				for (int b = 0; b < (int)Difficulty::COUNT; ++b)
				{
					Color 星色 = {0,0,0};
					if (金星 >= b){ 星色 = Color::Yellow; }
					else if (銀星 >= b){ 星色 = Color::Silver; }

					MFont::BMP黒.DrawRotate(UI::Pウィッチ[a] + UI::P星差分, 1, 0, 星色, "☆");
				}
			}

			//ミニマップ
			MSystem::フレーム[0].Draw(UI::Rミニマップ);

		}
	};

}