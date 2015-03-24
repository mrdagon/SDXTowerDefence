//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

#define EXT
#include "Design.h"

namespace SDX_TD
{
	void UI_Unit::Reset()
	{
		//名前枠と画像全体位置は共通
		const int stY = 27;//X基準

		R名前 = { 486, stY + 215, 140, 30 };

		P画像 = { 504, stY + 227 };
		P名前 = { 530, stY + 221 };
		P詠唱数 = { 510, stY + 220 };

		P説明 = { 495, stY + 259 };
		R説明 = { 486, stY + 249, 140, 48 };

		for (int a = 0; a < 5; ++a)
		{
			R性能[a] = { 486, stY + 306 + a * 27, 140, 25 };
			P性能アイコン[a] = { 490, R性能[a].y };
			P性能[a] = { 500, R性能[a].y + 7 };
		}

		R強化 = { 486, stY + 249, 69, 48 };
		P強化 = { R強化.x + 19, R強化.y + 6 };

		//X以外は強化と同じ
		R回収 = { 557, stY + 249, 69, 48 };
		P回収 = { R回収.x + 19, R回収.y + 6 };
	}

	void UI_Stage::Reset()
	{
		P差分[0] = { 10, -10 };
		Pスコア = { 36, 13 };
		Rスコア = { 44, 4, 120, 30 };

		P敵数 = { 162, 13 };
		R敵数 = { 168, 4, 60, 30 };

		P差分[6] = { 22, 17 };
		P差分[7] = { 10, 22 };
		for (int a = 0; a < 4; ++a)
		{
			Pゲーム速度[a] = { 8, 10 };
			Rゲーム速度[a] = { 234 + a * 58, -6, 58, 42, 0, 0 };
		}

		R右全体 = { 472, 0, 168, 100 + 105 + 27 };

		Pシングルウィッチ = { 511, 65 };
		Pカップルウィッチ[0] = { 496, 65 };
		Pカップルウィッチ[1] = { 526, 65 };

		Pモード名 = { 480, 90 };
		P難易度名 = { 480, 100 };

		P差分[1] = { 20, 6 };
		PＳＰ = { 550, 17 + 27 };
		P体力 = { 550, 39 + 27 };
		P魔力 = { 550, 61 + 27 };

		P差分[2] = { 10, 10 };
		R大魔法 = { 556 - 74, 4, 70, 36, 0, 0 };
		Rメニュー = { 556 + 4, 4, 70, 36, 0, 0 };

		P差分[3] = { 20, 12 };//ユニット画像位置
		P差分[4] = { 12, 20 };//残り配置回数
		P差分[5] = { 2, 24 };//×の位置
		for (int a = 0; a < 12; ++a)
		{
			R魔法一覧[a] = { 476 + a % 4 * 40, 112 + a / 4 * 40, 40, 40, 0, 0 };
		}

		R情報 = { 472, 205 + 27, 168, 269 - 27, 0, 0 };
	}

	void UI_Pause::Reset()
	{
		Rあきらめる = { 320, 160, 100, 25, 100, 25 };
		Rやり直す = { 320, 240, 100, 25, 100, 25 };
		R続ける = { 320, 320, 100, 25 ,100,25};
	}

	void UI_Result::Reset()
	{
		R終了 = {320,260,100,25,100,25};
		Rリトライ = {320,380,100,25,100,25};
	}

	void UI_MainMenu::Reset()
	{
		サブモード名 = { 126, 30 };

		R背景枠 = {60,0,640-60,480};
		for (int a = 0; a < SUB_COUNT; ++a)
		{
			Rボタン[a] = { 0, a*60 , 60, 60 };
		}
	}

	void UI_Title::Reset()
	{
	
	}

	void UI_StorySelect::Reset()
	{

	}

	void UI_QuestSelect::Reset()
	{
		//ステージ一覧
		for (int a = 0; a < (int)StageType::COUNT; ++a)
		{
			Rステージ[a] = { 66 + a%8 * 35 , 37 + a / 8*35, 35, 35 };
		}

		//タッグ/強化有無
		Rモード = { 66, 145, 280, 40 };
		R人数 = { 66+2    , 147, 138, 36 };
		R強化 = { 66+2+138, 147, 138, 36 };

		//ウィッチ/スコア/星
		Rウィッチ枠 = { 66, 189, 280, 286 };
		for (int a = 0; a < (int)WitchType::COUNT; ++a)
		{
			Rウィッチ[a] = { 66, 189 + a * 20 , 280,20};
		}
		P星差分 = { 40, 0 };
		Pスコア差分 = { 80, 0 };

		//ミニマップ
		Pステージ名 = { 348, 37+280 };
		Rミニマップ = { 348, 37, 280, 300 };

		//難易度
		P難易度 = { 348+140, 364 };
		R難易度Up = { 348, 340, 40, 40 };
		R難易度Down = { 348+240, 340, 40, 40 };
		R難易度説明 = { 348,340,280,90};

		PWave数 = { 348, 381 };
		Pボス数 = { 388, 381 };
		P雑魚数 = { 428, 381 };
		PHP補正 = { 348, 411 };
		PLv補正 = { 388, 411 };

		//開始
		R開始 = {348,435,280,40};
	}

	void UI_FreeSelect::Reset()
	{

	}

	void UI_Skill::Reset()
	{

	}

	void UI_Archive::Reset()
	{

	}

	void UI_Replay::Reset()
	{

	}

	void UI_Help::Reset()
	{

	}

	void UI_Config::Reset()
	{

	}

	/**全てのUIの位置を更新する.*/
	void UI_Reset()
	{
		UI_Stage::Reset();
		UI_Unit::Reset();
		UI_Pause::Reset();
		UI_Result::Reset();
		UI_Title::Reset();
		UI_MainMenu::Reset();
		UI_StorySelect::Reset();
		UI_QuestSelect::Reset();
		UI_FreeSelect::Reset();
		UI_Skill::Reset();
		UI_Archive::Reset();
		UI_Replay::Reset();
		UI_Help::Reset();
		UI_Config::Reset();
	}
}