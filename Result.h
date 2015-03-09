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
	private:
		bool is勝利;
		bool isリプレイ保存済み = false;
	public:
		Result(bool is勝利):
			is勝利(is勝利),
			isリプレイ保存済み(!SStage->isReplay)//リプレイ再生時は保存出来ない
		{
			Director::IsDraw() = true;
		}

		void Update()
		{
			namespace UI = UI_Result;

			if (!Input::mouse.Left.on) { return; }

			const Point pt = Input::mouse.GetPoint();

			//リプレイ保存ボタン、1回だけ保存出来る
			if ( !isリプレイ保存済み )
			{
				SStage->SaveReplay();
			}

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
}