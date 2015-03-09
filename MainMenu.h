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

	/**メインメニュー.*/
	class MainMenu : public Menu
	{
	public:
		MainMenu()
		{
		}

		
		void Update() override
		{
			//各ボタンの押下判定
			//Story～ストーリー～未実装
			//Quest～クエスト
			//FreePlay～自作マップのフリープレイ
			//Skill～スキルの変更
			//Archive～実績や合計スコアの表示等
			//Replay～リプレイを見る
			//Config～設定の変更
			//Help～操作説明等
			//Credit～作者情報などの表示
			//Quit～ソフトの終了

		}

		void Draw() override
		{
			//各項目を表示

		}
	};
}