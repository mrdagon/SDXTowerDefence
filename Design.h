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
	//UI用の定数
	//エディットコンティニュ時のコンパイル時間削減のためcppファイルを分離
	namespace UI_Stage
	{
		void Reset();
		EXT Point P差分[8];

		EXT Rect Rスコア;
		EXT Point Pスコア;

		EXT Rect R敵数;
		EXT Point P敵数;

		EXT Rect R右全体;

		EXT Point Pゲーム速度[4];
		EXT Rect Rゲーム速度[4];

		EXT Point Pシングルウィッチ;//シングル時
		EXT Point Pカップルウィッチ[2];//カップル時

		EXT Point Pモード名;
		EXT Point P難易度名;

		EXT Point PＳＰ;
		EXT Point P体力;
		EXT Point P魔力;

		EXT Rect R大魔法;
		EXT Rect Rメニュー;

		EXT Rect R魔法一覧[12];
		EXT Rect R情報;
	}

	namespace UI_Unit
	{
		void Reset();

		EXT Rect R名前;

		EXT Point P画像;
		EXT Point P名前;
		EXT Point P詠唱数;

		EXT Point P説明;
		EXT Rect R説明;

		EXT Point P性能アイコン[5];
		EXT Point P性能[5];

		EXT Rect R性能[5];

		EXT Rect R強化;
		EXT Point P強化;
		EXT Rect R回収;
		EXT Point P回収;
	}

	namespace UI_Pause
	{
		void Reset();

		EXT Rect R続ける;
		EXT Rect Rやり直す;
		EXT Rect Rあきらめる;
	}

	void UI_Reset();

}