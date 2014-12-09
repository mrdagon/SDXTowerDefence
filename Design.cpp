﻿//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

#define EXT
#include "Design.h"

namespace SDX_TD
{
	namespace UnitDraw
	{
		void Reset()
		{
			//名前枠と画像全体位置は共通
			const int stY = 27;//X基準

			F名前 = { 486, stY + 215, 140, 30 };

			P画像 = { 504, stY + 227 };
			P名前 = { 530, stY + 221 };
			P詠唱数 = { 510, stY + 220 };

			P説明 = { 495, stY + 259 };
			F説明 = { 486, stY + 249, 140, 48 };

			for (int a = 0; a < 5; ++a)
			{
				F性能[a] = { 486, stY + 306 + a * 27, 140, 25 };
				P性能アイコン[a] = { 490, F性能[a].y };
				P性能[a] = { 500, F性能[a].y + 7 };
			}

			F強化 = { 486, stY + 249, 69, 48 };
			P強化 = { F強化.x + 19, F強化.y + 6 };

			//X以外は強化と同じ
			F回収 = { 557, stY + 249, 69, 48 };
			P回収 = { F回収.x + 19, F回収.y + 6 };
		}
	}

	namespace StageDraw
	{
		void Reset()
		{
			Pスコア = { 36, 13 };
			Fスコア = { 44, 4, 120, 30, 0, 0 };

			P敵数 = { 162, 13 };
			F敵数 = { 168, 4, 60, 30, 0, 0 };

			for (int a = 0; a < 4; ++a)
			{
				Pゲーム速度[a] = { 8, 10 };
				Fゲーム速度[a] = { 234 + a * 58, -6, 58, 42, 0, 0 };
			}

			Pウィッチ = { 496, 60 };
			Pサブウィッチ = { 526, 60 };

			P大魔法 = { 550, 17 + 27 };
			P体力 = { 550, 39 + 27 };
			P魔力 = { 550, 61 + 27 };

			F大魔法 = { 556 - 74, 4, 70, 36, 0, 0 };
			Fメニュー = { 556 + 4, 4, 70, 36, 0, 0 };

			for (int a = 0; a < 12; ++a)
			{
				F魔法一覧[a] = { 476 + a % 4 * 40, 112 + a / 4 * 40, 40, 40, 0, 0 };
			}

			F情報 = { 472, 205 + 27, 168, 269 - 27, 0, 0 };
		}
	}
}