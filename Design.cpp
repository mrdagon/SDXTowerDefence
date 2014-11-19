//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Design.h"

namespace SDX_TD
{
	namespace UInfo
	{
		//名前枠と画像全体位置は共通
		const int stY = 27;//X基準

		const Rect F名前(){ return{ 486, stY + 215, 140, 30, 0, 0 }; };

		const Point P画像(){ return{ 504, stY + 227 }; };
		const Point P名前(){ return{ 530, stY + 221 }; };
		const Point P詠唱数(){ return{ 510, stY + 220 }; };

		const Point P説明(){ return{ 495, stY + 259 }; };
		const Rect F説明(){ return{ 486, stY + 249, 140, 48, 0, 0 }; };

		const Point P性能アイコン(int y) { return{ 490, F性能(y).y }; };
		const Point P性能(int y) { return{ 500, F性能(y).y + 7 }; };

		const Rect F性能(int y) { return{ 486, stY + 306 + y * 27, 140, 25, 0, 0 }; };

		const Rect F強化() { return{ 486, stY + 249, 69, 48, 0, 0 }; };
		const Point P強化() { return{ F強化().x + 19, F強化().y + 6 }; };

		//X以外は強化と同じ
		const Rect F回収() { return{ 557, stY + 249, 69, 48, 0, 0 }; };
		const Point P回収() { return{ F回収().x + 19, F回収().y + 6 }; };
	}

	namespace UStage
	{
		const Point Pスコア() { return{ 36, 13 }; };
		const Rect Fスコア() { return{ 44, 4, 120, 30, 0, 0 }; };

		const Point P敵数() { return{ 162, 13 }; };
		const Rect F敵数() { return{ 168, 4, 60, 30, 0, 0 }; };

		const Point Pゲーム速度() { return{ 8, 10 }; };
		const Rect Fゲーム速度(int No) { return{ 234 + No * 58, -6, 58, 42, 0, 0 }; };

		const Point Pウィッチ() { return{ 496, 60 }; };
		const Point Pサブウィッチ() { return{ 526, 60 }; };

		const Point P大魔法(){ return{ 550, 17 + 27 }; };
		const Point P体力() { return{ 550, 39 + 27 }; };
		const Point P魔力() { return{ 550, 61 + 27 }; };

		const Rect F大魔法() { return{ 556 - 74, 4, 70, 36, 0, 0 }; };
		const Rect Fメニュー() { return{ 556 + 4, 4, 70, 36, 0, 0 }; };

		const Rect F魔法一覧(int a) { return{ 476 + a % 4 * 40, 112 + a / 4 * 40, 40, 40, 0, 0 }; };

		const Rect F情報() { return{ 472, 205 + 27, 168, 269 - 27, 0, 0 }; };
	}
}