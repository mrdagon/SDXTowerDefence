//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Menu.h"

namespace SDX_TD
{
	using namespace SDX;

	/** スキルポイント割り振り画面画面*/
	/** @todo .*/
	class SkillMenu : public Menu
	{
	public:
		EnumArray<int, SkillType> 限界Lv;

		SkillMenu()
		{
			//初期化時に最大スキルレベルを計算
			//合算=ライナ/ナツメ/トレニア
			//合算=ディアネラ/バロゥ/ロチエ
			//合算=ルコウ/ミナエ/フィオナ
			//合算=ミルラ/ナズナ/委員長
			限界Lv[SkillType::攻撃] = WitchDataS[WitchType::ライナ].Lv + WitchDataS[WitchType::ナツメ].Lv + WitchDataS[WitchType::トレニア].Lv;
			限界Lv[SkillType::連射] = WitchDataS[WitchType::ディアネラ].Lv + WitchDataS[WitchType::バロゥ].Lv + WitchDataS[WitchType::ロチエ].Lv;
			限界Lv[SkillType::射程] = WitchDataS[WitchType::ルコウ].Lv + WitchDataS[WitchType::ミナエ].Lv + WitchDataS[WitchType::フィオナ].Lv;
			限界Lv[SkillType::支援] = WitchDataS[WitchType::ミルラ].Lv + WitchDataS[WitchType::ナズナ].Lv + WitchDataS[WitchType::委員長].Lv;

			限界Lv[SkillType::拡散] = WitchDataS[WitchType::トレニア].Lv;//
			限界Lv[SkillType::麻痺] = WitchDataS[WitchType::ロチエ].Lv;//
			限界Lv[SkillType::鈍足] = WitchDataS[WitchType::ロチエ].Lv;//
			限界Lv[SkillType::吹飛] = WitchDataS[WitchType::ミナエ].Lv;//
			限界Lv[SkillType::防壊] = WitchDataS[WitchType::ナツメ].Lv;//
			限界Lv[SkillType::回収] = WitchDataS[WitchType::ディアネラ].Lv;//
			限界Lv[SkillType::強化] = WitchDataS[WitchType::委員長].Lv;//
			限界Lv[SkillType::逆境] = WitchDataS[WitchType::ライナ].Lv;//
			限界Lv[SkillType::節約] = WitchDataS[WitchType::ディアネラ].Lv;//
			限界Lv[SkillType::体力] = WitchDataS[WitchType::フィオナ].Lv;//
			限界Lv[SkillType::魔力] = WitchDataS[WitchType::ナズナ].Lv;//
			限界Lv[SkillType::必殺] = WitchDataS[WitchType::バロゥ].Lv;//
			限界Lv[SkillType::対竜] = WitchDataS[WitchType::ルコウ].Lv;//
			限界Lv[SkillType::対獣] = WitchDataS[WitchType::ナツメ].Lv;//
			限界Lv[SkillType::対人] = WitchDataS[WitchType::バロゥ].Lv;//
			限界Lv[SkillType::対闇] = WitchDataS[WitchType::フィオナ].Lv;//
			限界Lv[SkillType::対水] = WitchDataS[WitchType::委員長].Lv;//
			限界Lv[SkillType::対樹] = WitchDataS[WitchType::ミナエ].Lv;//
			限界Lv[SkillType::幸運] = WitchDataS[WitchType::ナズナ].Lv;//
			限界Lv[SkillType::試練] = WitchDataS[WitchType::ルコウ].Lv;//

			//Lvは最大で1万まで
			for (auto &it : 限界Lv)
			{
				if (it > 10000){ it = 10000; }
			}

			Director::IsDraw() = true;
		}

		void Update()
		{

		}

		void Draw()
		{
			//際右にタブメニュー

			//右にスキルアイコンと限界大レベル、現在レベルを表示
			//左に説明を表示

			//合計ポイントと使用ポイントを隅に表示
			//戻るボタンを隅に表示
		}

	};
}