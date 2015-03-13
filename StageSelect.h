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
	/** @todo 仮実装*/
	class QuestMenu : public IScene
	{
	public:
		QuestMenu()
		{

		}

		void Update()
		{
			namespace UI = UI_QuestSelect;
			UI::Reset();

			if (!Input::mouse.Left.on) { return; }

			const Point pt = Input::mouse.GetPoint();
			/*
			for (int a = 0; a < (int)Difficulty::COUNT; ++a)
			{
				if (UI::R難易度[a].Hit(&pt))
				{
					TDSystem::難易度 = Difficulty(a);
					isEnd = true;
					//Director::AddScene(std::make_shared<Stage>());
				}
			}
			*/
		}

		void Draw()
		{
			namespace UI = UI_QuestSelect;
			//ショートカットタブ
			MSystem::フレーム[0].Draw({ 0, 0, 60, 60 });
			MSystem::フレーム[0].Draw({ 0, 60, 60, 60 });
			MSystem::フレーム[0].Draw({ 0, 120, 60, 60 });
			MSystem::フレーム[0].Draw({ 0, 180, 60, 60 });
			MSystem::フレーム[0].Draw({ 0, 240, 60, 60 });
			MSystem::フレーム[0].Draw({ 0, 300, 60, 60 });
			MSystem::フレーム[0].Draw({ 0, 360, 60, 60 });
			MSystem::フレーム[0].Draw({ 0, 420, 60, 60 });

			//難易度
			MFont::ゴシック小.Draw({ 100, 60 }, Color::White, { (int)TDSystem::難易度 });

			//モード
			MFont::ゴシック小.Draw({ 100, 120 }, Color::White, { TDSystem::isトライアル });
			MFont::ゴシック小.Draw({ 100, 180 }, Color::White, { TDSystem::isカップル });

			//ステージアイコン
			for (int a = 0; a < (int)StageType::COUNT; ++a)
			{
				//選択中の枠は色変更
				MSystem::フレーム[0].Draw({ 200, 200, 50, 50 });
				MIcon::魔導具[WitchType::トレニア].Draw({ 200, 200 });
			}

			//ウィッチ＆スコア
			MUnit::魔女[UnitType::ディアネラ][1]->Draw({ 300, 300 });

		}
	};

	/** 難易度,モード,ステージ,使用ウィッチの選択選択.*/
	/** QuestSelectとレイアウトを似せる*/
	/** @todo 仮実装*/
	class FreeMenu : public IScene
	{
		void Update() override
		{
			namespace UI = UI_FreeSelect;
		}

		void Draw() override
		{
			namespace UI = UI_FreeSelect;
		}
	};

	/** 難易度,ステージの選択.*/
	/** @todo 1.03 非実装*/
	class StoryMenu : public IScene
	{
		void Update() override
		{
			namespace UI = UI_StorySelect;
		}

		void Draw() override
		{
			namespace UI = UI_StorySelect;
		}
	};



}