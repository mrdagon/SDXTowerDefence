//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"
#include "MenuArchive.h"
#include "MenuConfig.h"
#include "MenuHelp.h"
#include "MenuSkill.h"
#include "MenuReplay.h"
#include "MenuFree.h"
#include "MenuStory.h"
#include "MenuQuest.h"

namespace SDX_TD
{
	using namespace SDX;

	/** メインメニュー.*/
	class MenuMain : public IScene
	{
	public:
		IScene *サブメニュー[UI_MainMenu::SUB_COUNT];
		int subIndex = -1;

		MenuMain()
		{
			サブメニュー[0] = new MenuStory();
			サブメニュー[1] = new MenuQuest();
			サブメニュー[2] = new MenuFree();
			サブメニュー[3] = new MenuSkill();
			サブメニュー[4] = new MenuArchive();
			サブメニュー[5] = new MenuReplay();
			サブメニュー[6] = new MenuHelp();
			サブメニュー[7] = new MenuConfig();
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

			MSystem::フレーム[5].Draw(UI::R背景枠);
			Point 差分 = { 30, 30 };

			//枠、アイコン、文字の描画
			for (int a = 0; a < UI::SUB_COUNT; ++a)
			{
				if (a == subIndex)
				{
					//選択中のは大きく表示
					MSystem::フレーム[5].Draw(UI::Rボタン[a]);
					MIcon::ターゲット[0]->DrawRotate(UI::Rボタン[a].GetPoint() + 差分, 2, 0);
				}
				else
				{
					MSystem::フレーム[5].Draw(UI::Rボタン[a]);
					MIcon::ターゲット[0]->DrawRotate(UI::Rボタン[a].GetPoint() + 差分, 1, 0);
				}
				MFont::BMP黒.DrawRotate(UI::Rボタン[a].GetPoint() + Point(35, 50), 1, 0, Color::White, "Story");
			}

			if ( subIndex >= 0 )
			{
				サブメニュー[subIndex]->Draw();
			}
		}
	};
}