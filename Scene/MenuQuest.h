//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Design.h"
#include "System/TDSystem.h"

namespace SDX_TD
{
	using namespace SDX;

	/** サブウィッチ選択ウィンドウモード*/
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

			//メイン、サブの準に選ぶ
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
			//メインメニューを背景表示

			//ウィッチ12人を表示、現在メインのウィッチは表示が違う
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

			for (int a = 0; a < StageType::COUNT; ++a)
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

			if (UI::R強化.Hit(&pt))
			{
				TDSystem::isトライアル = !TDSystem::isトライアル;
			}

			if (UI::R人数.Hit(&pt))
			{
				TDSystem::isカップル = !TDSystem::isカップル;
			}

			if (UI::R開始.Hit(&pt))
			{
				Director::AddScene(std::make_shared<Stage>());
				if (TDSystem::isカップル)
				{
					//サブ選択画面をスタック

				}
			}
		}

		void Draw()
		{
			namespace UI = UI_QuestSelect;
			//ステージ一覧
			for (int a = 0; a < (int)StageType::COUNT; ++a)
			{
				//選択中の枠は色変更
				if (a == (int)TDSystem::選択ステージ)
				{
					MSystem::フレーム[0].Draw(UI::Rステージ[a], Color::Red);
				}
				else
				{
					MSystem::フレーム[0].Draw(UI::Rステージ[a]);
				}				
				MIcon::魔導具[WitchType::トレニア].DrawRotate(UI::Rステージ[a].GetCenter(),1,0);
			}

			//モード表示
			MSystem::フレーム[0].Draw(UI::Rモード);
			MSystem::フレーム[3].Draw(UI::R強化);
			MSystem::フレーム[3].Draw(UI::R人数);
			MFont::BMP黒.DrawRotate(UI::R強化.GetCenter(), 2, 0, Color::White, { "Trial" });
			MFont::BMP黒.DrawRotate(UI::R人数.GetCenter(), 2, 0, Color::White, { "Single" });

			//ウィッチ＆スコア
			MSystem::フレーム[0].Draw(UI::Rウィッチ枠);
			for (int a = 0; a < (int)WitchType::COUNT; ++a)
			{
				auto no = UnitType(a);
				auto wNo = WitchType(a);
				const auto pt = UI::Rウィッチ[a].GetPoint();

				int score = StageDataS[a].Getスコア().スコア[wNo];
				int 銀星 = (int)StageDataS[a].Getスコア().達成度[wNo];
				int 金星 = (int)StageDataS[a].Getスコア().完勝[wNo];

				MUnit::魔女[no][1]->DrawRotate( pt , 1, 0);
				MFont::BMP黒.DrawRotate( pt + UI::Pスコア差分, 2, 0, Color::White, { score });

				for (int b = 0; b < (int)Difficulty::COUNT; ++b)
				{
					Point ptBuf = pt + UI::P星差分 + Point(b * 10, 0);
					Color 星色 = {0,0,0};
					if (金星 >= b){ 星色 = Color::Yellow; }
					else if (銀星 >= b){ 星色 = Color::Silver; }

					MFont::BMP黒.DrawRotate( ptBuf, 1, 0, 星色, "☆");
				}
			}

			//ミニマップ
			MFont::ゴシック中.Draw(UI::Pステージ名, Color::White, {123});
			MSystem::フレーム[0].Draw(UI::Rミニマップ);

			//難易度
			MSystem::フレーム[0].Draw(UI::R難易度説明);
			MFont::BMP黒.DrawRotate(UI::P難易度,2,0, Color::White, { "Easy" });
			MSystem::フレーム[3].Draw(UI::R難易度Up);
			MSystem::フレーム[3].Draw(UI::R難易度Down);

			MFont::BMP黒.DrawExtend(UI::PHP補正,1,1, Color::White, { "HP ×" ,DifficultyDataS[TDSystem::難易度].HP補正[TDSystem::isトライアル] });
			MFont::BMP黒.DrawExtend(UI::PLv補正,1,1, Color::White, { "LV ×", DifficultyDataS[TDSystem::難易度].レベル補正[TDSystem::isトライアル] });
			MFont::BMP黒.DrawExtend(UI::P雑魚数, 1, 1, Color::White, { "Enemy ×", DifficultyDataS[TDSystem::難易度].雑魚召喚数[TDSystem::isトライアル] });
			MFont::BMP黒.DrawExtend(UI::Pボス数, 1, 1, Color::White, { "Boss ×", DifficultyDataS[TDSystem::難易度].ボス召喚数[TDSystem::isトライアル] });
			MFont::BMP黒.DrawExtend(UI::PWave数, 1, 1, Color::White, { "Wave ×", DifficultyDataS[TDSystem::難易度].Wave数[TDSystem::isトライアル] });
			//開始
			MSystem::フレーム[3].Draw(UI::R開始);
			MFont::BMP黒.DrawRotate(UI::R開始.GetCenter(), 2, 0, Color::White, {"Easy"});
		}
	};

}