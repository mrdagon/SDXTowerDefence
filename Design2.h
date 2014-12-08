//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3
#pragma once
#include "Framework/Shape.h"

namespace SDX_TD
{
	using namespace SDX;

	namespace StageDraw
	{
		Point Pスコア;
		Rect Fスコア;

		Point P敵数;
		Rect F敵数;

		Point Pゲーム速度[4];
		Rect Fゲーム速度[4];

		Point Pウィッチ;
		Point Pサブウィッチ;

		Point P体力;
		Point P魔力;

		Point P大魔法;
		Rect F大魔法;

		Rect Fメニュー;

		Rect F魔法一覧[12];

		Rect F情報;
	}

	namespace UnitDraw
	{
		//名前枠と画像全体位置は共通
		Rect F名前;

		Point P画像;
		Point P名前;
		Point P詠唱数;

		Point P説明;
		Rect F説明;

		Point P性能アイコン[5];
		Point P性能[5];

		Rect F性能[5];//最大5

		Rect F強化;
		Point P強化;
		Rect F回収;
		Point P回収;
	}
}