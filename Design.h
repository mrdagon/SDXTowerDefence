//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3
#pragma once
#include "Framework/Shape.h"

namespace SDX_TD
{
	using namespace SDX;

	//Design.cpp以外から呼ぶ時はexternを付ける
#ifndef EXT
#define EXT extern
#endif

	namespace StageDraw
	{
		void Reset();

		EXT Point Pスコア;
		EXT Rect Fスコア;

		EXT Point P敵数;
		EXT Rect F敵数;

		EXT Point Pゲーム速度[4];
		EXT Rect Fゲーム速度[4];

		EXT Point Pウィッチ;
		EXT Point Pサブウィッチ;

		EXT Point P体力;
		EXT Point P魔力;

		EXT Point P大魔法;
		EXT Rect F大魔法;

		EXT Rect Fメニュー;

		EXT Rect F魔法一覧[12];
		EXT Rect F情報;
	}

	namespace UnitDraw
	{
		void Reset();

		EXT Rect F名前;

		EXT Point P画像;
		EXT Point P名前;
		EXT Point P詠唱数;

		EXT Point P説明;
		EXT Rect F説明;

		EXT Point P性能アイコン[5];
		EXT Point P性能[5];

		EXT Rect F性能[5];

		EXT Rect F強化;
		EXT Point P強化;
		EXT Rect F回収;
		EXT Point P回収;
	}

}