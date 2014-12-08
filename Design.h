//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3
#pragma once
#include "Framework/Shape.h"

namespace SDX_TD
{
	using namespace SDX;

	namespace StageDraw
	{
		void Reset();

		extern Point Pスコア;
		extern Rect Fスコア;

		extern Point P敵数;
		extern Rect F敵数;

		extern Point Pゲーム速度[4];
		extern Rect Fゲーム速度[4];

		extern Point Pウィッチ;
		extern Point Pサブウィッチ;

		extern Point P体力;
		extern Point P魔力;

		extern Point P大魔法;
		extern Rect F大魔法;

		extern Rect Fメニュー;

		extern Rect F魔法一覧[12];
		extern Rect F情報;
	}

	namespace UnitDraw
	{
		void Reset();

		//名前枠と画像全体位置は共通
		extern Rect F名前;

		extern Point P画像;
		extern Point P名前;
		extern Point P詠唱数;

		extern Point P説明;
		extern Rect F説明;

		extern Point P性能アイコン[5];
		extern Point P性能[5];

		extern Rect F性能[5];//最大5

		extern Rect F強化;
		extern Point P強化;
		extern Rect F回収;
		extern Point P回収;
	}
}