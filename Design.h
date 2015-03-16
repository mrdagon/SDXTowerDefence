//©(´･@･) http://tacoika.blog87.fc2.com/
//[License] GNU Affero General Public License, version 3
#pragma once
#include "Framework/Shape.h"
#include "EnumType.h"
#include "Utility/EnumArray.h"

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

	namespace UI_Result
	{
		void Reset();

		EXT Rect R終了;
		EXT Rect Rリトライ;
	}

	namespace UI_Title
	{
		void Reset();

		EXT Point P題字;
		EXT Point P何か入力して下さい;
	}

	namespace UI_MainMenu
	{
		void Reset();
		static const int SUB_COUNT = 8;

		EXT Rect Rボタン[SUB_COUNT];
		EXT Rect R背景枠;
	}

	namespace UI_WitchSelect
	{
		void Reset();
		
		EXT EnumArray<Rect, WitchType> Rウィッチ;

	}

	namespace UI_StorySelect
	{
		void Reset();
	}

	namespace UI_QuestSelect
	{
		void Reset();
		//右にステージ一覧等

		//左に縮小ステージ

		//文字
		EXT Point Pステージ名;
		EXT Point P難易度;
		EXT Point Pモード;
		EXT Point Pステージ;
		EXT Rect Rミニマップ;
		EXT Point Pミニマップ;
		EXT Point P難易度Up;
		EXT Point P難易度Down;
		EXT Point Pウィッチ[(int)WitchType::COUNT];
		EXT Point P星差分;
		EXT Point Pスコア差分;
		//ボタン
		EXT Rect R難易度Up;
		EXT Rect R難易度Down;

		EXT Rect Rトライアル;
		EXT Rect Rカップル;

		EXT Rect Rステージ[(int)StageType::COUNT];

		EXT Rect Rウィッチ[(int)WitchType::COUNT];

		EXT Rect R開始;
	}

	namespace UI_FreeSelect
	{
		void Reset();
	}

	namespace UI_Skill
	{
		void Reset();
	}

	namespace UI_Archive
	{
		void Reset();
	}

	namespace UI_Replay
	{
		void Reset();
		//左リスト部
		EXT Rect R左ブロック;
		EXT Rect Rスクロールボックス;
		EXT Rect R再生;

		//右詳細
		EXT Rect R右ブロック;
		EXT Point Pステージ名;
		EXT Point P縮小マップ;
		EXT Point P難易度;
		EXT Point Pスコア;
		EXT Point Pモード;
		EXT Point Pメインウィッチ;
		EXT Point Pサブウィッチ;
		//スキルLvは非表示
	}

	namespace UI_Help
	{
		void Reset();
		//ボタン
		//ヘルプ項目毎に一つ
		//ボタンには文字とアイコンを付ける
		//ボタンを押すとポップアップでヘルプを表示
		EXT Rect Rボタン;
		EXT Point P文字;
	}

	namespace UI_Config
	{
		void Reset();
		//ボタン
		EXT Rect R効果音Up;
		EXT Rect R効果音Down;
		EXT Rect R音楽Up;
		EXT Rect R音楽Down;
		EXT Rect Rグリッド表示;
		EXT Rect Rライフ表示;
		EXT Rect Rエフェクト表示;
		EXT Rect Rタッチ操作;
		EXT Rect Rリプレイ保存;
		//文字
		EXT Point P効果音Up;
		EXT Point P効果音Down;
		EXT Point P音楽Up;
		EXT Point P音楽Down;
		EXT Point Pグリッド表示;
		EXT Point Pライフ表示;
		EXT Point Pエフェクト表示;
		EXT Point Pタッチ操作;
		EXT Point Pリプレイ保存;
	}

#undef EXT

	void UI_Reset();

}