//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"
#include "Archive.h"
#include "Config.h"
#include "Help.h"
#include "SkillMenu.h"
#include "ReplaySelect.h"

namespace SDX_TD
{
	using namespace SDX;

	/** メインメニュー.*/
	class MainMenu : public IScene
	{
	public:
		IScene *サブメニュー[UI_MainMenu::SUB_COUNT];
		int subIndex = -1;

		MainMenu()
		{

		}

		void Update() override
		{
			//画面切り替えは一瞬+効果音
			namespace UI = UI_MainMenu;
			UI_Reset();
			auto pt = Input::mouse.GetPoint();

			//各ボタンの押下判定
			for (int a = 0; a < UI::SUB_COUNT; ++a)
			{
				if ( UI::Rボタン[a].Hit(&Input::mouse.GetPoint()) && Input::mouse.Left.on )
				{
					subIndex = a;
				}
			}
			//サブメニューの処理
			if ( subIndex >= 0 )
			{
				サブメニュー[subIndex]->Update();
			}

		}

		void Draw() override
		{
			namespace UI = UI_MainMenu;

			MSystem::フレーム[0].Draw(UI::R背景枠);

			//枠、アイコン、文字の描画
			for (int a = 0; a < UI::SUB_COUNT; ++a)
			{
				if (a == subIndex)
				{
					//選択中

				}
				else
				{
					MSystem::フレーム[0].Draw(UI::Rボタン[a]);
					MIcon::ターゲット[0]->Draw(UI::Rボタン[a].GetPoint());
				}
			}

			if ( subIndex >= 0 )
			{
				サブメニュー[subIndex]->Draw();
			}
		}
	};
}