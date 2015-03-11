//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"
#include "Archive.h"
#include "Config.h"
#include "Help.h"
#include "ReplaySelect.h"
#include "Tutorial.h"


namespace SDX_TD
{
	using namespace SDX;

	enum class SubMenuType
	{
		Main,
		Story,
		Quest,
		Free,
		Skill,
		Archive,
		Help,
		Replay,
		Config,
		//Quitは無し
	};

	/** メインメニュー.*/
	class MainMenu : public Menu
	{
	public:
		IScene* サブ;//std::uniqueptrにして毎回newしても良い感じはある
		QuestSelect questSelect;

		MainMenu()
		{
		}

		void Update() override
		{
			//画面切り替えは一瞬+効果音
			namespace UI = UI_MainMenu;
			UI_Reset();

			//各ボタンの押下判定
			//Story～ストーリー～未実装
			//Quest～クエスト
			//FreePlay～自作マップのフリープレイ
			//Skill～スキルの変更
			//Archive～実績や合計スコアの表示等
			//Replay～リプレイを見る
			//Config～設定の変更
			//Help～操作説明、及びCredit
			//Quit～ソフトの終了
			if (true)
			{
				サブ = &questSelect;
			}
			
			if (サブ)
			{
				サブ->Update();
			}

		}

		void Draw() override
		{
			namespace UI = UI_MainMenu;

			if (サブ)
			{
				サブ->Draw();
			}
		}
	};
}