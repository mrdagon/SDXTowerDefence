//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"

namespace SDX_TD
{
	using namespace SDX;

	/**ウィッチの基礎性能.*/
	struct WitchData
	{
		WitchType 種類;
		Element 属性;

		std::string 名前;
		std::string 大魔法名;
		std::string 魔導具名;
		std::string 説明文;

		//外部に保存
		int レベル;
		int 経験値;

		double 攻撃補正 = 1.0;
		double 連射補正 = 1.0;
		double 射程補正 = 1.0;
		double 範囲補正 = 1.0;
		double 炸裂補正 = 1.0;
		double 支援補正 = 1.0;
		double 弾速補正 = 1.0;

		double MP消費 = 1.0;
		double MP獲得 = 1.0;
		double 回収率 = 0.7;
		double 回収速度 = 1.0;
		double 強化速度 = 1.0;

		double 弱点補正 = 1.1;

		EnumArray<double, DebuffType> 特殊補正;//基本は1.0

		int    大魔法時間 = 3000;
		double 獲得SP = 1.0;//溜まり易さ

		double 逆境補正 = 0.01;//ライフ-1につき1%攻撃力が上がる

		//ステージ開始時しか参照しないパラメータ
		int    追加Hp = 0;
		int    初期Mp = 50;

		double 強化回数補正 = 1.0;

		UnitType 職種[12];

		WitchData()
		{
			特殊補正[DebuffType::吹飛] = 1.0;
			特殊補正[DebuffType::防壊] = 1.0;
			特殊補正[DebuffType::麻痺] = 1.0;
			特殊補正[DebuffType::鈍足] = 1.0;
		}
	};

	EnumArray<WitchData, WitchType> WitchDataS;//基本性能

	void LoadWitchS()
	{
		//数も少ないので直接入力
		for (int a = 0; a < 12; ++a)
		{
			WitchDataS[WitchType(a)].種類 = WitchType(a);
		}

		WitchDataS[WitchType::ライナ].名前 = "ライナ";
		WitchDataS[WitchType::ライナ].大魔法名 = "フォルドアーカレイト";
		WitchDataS[WitchType::ライナ].魔導具名 = "トルネルージュ";
		WitchDataS[WitchType::ライナ].説明文 = "";

		WitchDataS[WitchType::ライナ].属性 = Element::炎;
		WitchDataS[WitchType::ライナ].攻撃補正 = 1.05;
		WitchDataS[WitchType::ライナ].連射補正 = 1.05;
		WitchDataS[WitchType::ライナ].逆境補正 = 0.03;//通常の三倍

		WitchDataS[WitchType::ライナ].職種[0] = UnitType::ライナ;
		WitchDataS[WitchType::ライナ].職種[1] = UnitType::兵士;
		WitchDataS[WitchType::ライナ].職種[2] = UnitType::技師;
		WitchDataS[WitchType::ライナ].職種[3] = UnitType::剣士;
		WitchDataS[WitchType::ライナ].職種[4] = UnitType::槍士;
		WitchDataS[WitchType::ライナ].職種[5] = UnitType::斧士;
		WitchDataS[WitchType::ライナ].職種[6] = UnitType::武闘家;
		WitchDataS[WitchType::ライナ].職種[7] = UnitType::狩人;
		WitchDataS[WitchType::ライナ].職種[8] = UnitType::術士;
		WitchDataS[WitchType::ライナ].職種[9] = UnitType::盗賊;
		WitchDataS[WitchType::ライナ].職種[10] = UnitType::踊り子;
		WitchDataS[WitchType::ライナ].職種[11] = UnitType::執事;

		WitchDataS[WitchType::ナツメ].名前 = "ナツメ";
		WitchDataS[WitchType::ナツメ].大魔法名 = "グリンブルスティ";
		WitchDataS[WitchType::ナツメ].魔導具名 = "ジャガーノート";
		WitchDataS[WitchType::ナツメ].説明文 = "";

		WitchDataS[WitchType::ナツメ].属性 = Element::炎;
		WitchDataS[WitchType::ナツメ].攻撃補正 = 1.2;
		WitchDataS[WitchType::ナツメ].特殊補正[DebuffType::防壊] = 1.5;
		WitchDataS[WitchType::ナツメ].射程補正 = 0.8;
		WitchDataS[WitchType::ナツメ].範囲補正 = 0.8;

		WitchDataS[WitchType::ナツメ].職種[0] = UnitType::ナツメ;
		WitchDataS[WitchType::ナツメ].職種[1] = UnitType::傭兵;
		WitchDataS[WitchType::ナツメ].職種[2] = UnitType::槍士;
		WitchDataS[WitchType::ナツメ].職種[3] = UnitType::闘士;
		WitchDataS[WitchType::ナツメ].職種[4] = UnitType::武闘家;
		WitchDataS[WitchType::ナツメ].職種[5] = UnitType::師範;
		WitchDataS[WitchType::ナツメ].職種[6] = UnitType::僧侶;
		WitchDataS[WitchType::ナツメ].職種[7] = UnitType::プリンス;
		WitchDataS[WitchType::ナツメ].職種[8] = UnitType::術士;
		WitchDataS[WitchType::ナツメ].職種[9] = UnitType::踊り子;
		WitchDataS[WitchType::ナツメ].職種[10] = UnitType::執事;
		WitchDataS[WitchType::ナツメ].職種[11] = UnitType::料理人;

		//
		WitchDataS[WitchType::ルコウ].名前 = "ルコウ";
		WitchDataS[WitchType::ルコウ].大魔法名 = "御津之比良坂流『氷天攻華』";
		WitchDataS[WitchType::ルコウ].魔導具名 = "雪風/空魂";
		WitchDataS[WitchType::ルコウ].説明文 = "";

		WitchDataS[WitchType::ルコウ].属性 = Element::炎;
		WitchDataS[WitchType::ルコウ].攻撃補正 = 1.50;
		WitchDataS[WitchType::ルコウ].回収率 = 0;
		WitchDataS[WitchType::ルコウ].MP消費 = 1.33;
		WitchDataS[WitchType::ルコウ].回収速度 = 1.5;
		WitchDataS[WitchType::ルコウ].強化速度 = 1.5;

		WitchDataS[WitchType::ルコウ].職種[0] = UnitType::ルコウ;
		WitchDataS[WitchType::ルコウ].職種[1] = UnitType::足軽;
		WitchDataS[WitchType::ルコウ].職種[2] = UnitType::剣士;
		WitchDataS[WitchType::ルコウ].職種[3] = UnitType::剣豪;
		WitchDataS[WitchType::ルコウ].職種[4] = UnitType::槍士;
		WitchDataS[WitchType::ルコウ].職種[5] = UnitType::闘士;
		WitchDataS[WitchType::ルコウ].職種[6] = UnitType::射手;
		WitchDataS[WitchType::ルコウ].職種[7] = UnitType::司祭;
		WitchDataS[WitchType::ルコウ].職種[8] = UnitType::プリンス;
		WitchDataS[WitchType::ルコウ].職種[9] = UnitType::賢者;
		WitchDataS[WitchType::ルコウ].職種[10] = UnitType::軍師;
		WitchDataS[WitchType::ルコウ].職種[11] = UnitType::忍者;

		//
		WitchDataS[WitchType::ディアネラ].名前 = "ディアネラ";
		WitchDataS[WitchType::ディアネラ].大魔法名 = "レインマニエール";
		WitchDataS[WitchType::ディアネラ].魔導具名 = "皇剣シルヴァウス";
		WitchDataS[WitchType::ディアネラ].説明文 = "";

		WitchDataS[WitchType::ディアネラ].属性 = Element::炎;
		WitchDataS[WitchType::ディアネラ].MP消費 = 0.9;
		WitchDataS[WitchType::ディアネラ].回収速度 = 0.5;

		WitchDataS[WitchType::ディアネラ].職種[0] = UnitType::ディアネラ;
		WitchDataS[WitchType::ディアネラ].職種[1] = UnitType::足軽;
		WitchDataS[WitchType::ディアネラ].職種[2] = UnitType::勇者;
		WitchDataS[WitchType::ディアネラ].職種[3] = UnitType::剣士;
		WitchDataS[WitchType::ディアネラ].職種[4] = UnitType::斧士;
		WitchDataS[WitchType::ディアネラ].職種[5] = UnitType::武闘家;
		WitchDataS[WitchType::ディアネラ].職種[6] = UnitType::狩人;
		WitchDataS[WitchType::ディアネラ].職種[7] = UnitType::プリンス;
		WitchDataS[WitchType::ディアネラ].職種[8] = UnitType::プリンセス;
		WitchDataS[WitchType::ディアネラ].職種[9] = UnitType::将軍;
		WitchDataS[WitchType::ディアネラ].職種[10] = UnitType::給仕;
		WitchDataS[WitchType::ディアネラ].職種[11] = UnitType::忍者;

		//
		WitchDataS[WitchType::ミナエ].名前 = "ミナエ";
		WitchDataS[WitchType::ミナエ].大魔法名 = "スーパーノヴァ";
		WitchDataS[WitchType::ミナエ].魔導具名 = "カランコエ";
		WitchDataS[WitchType::ミナエ].説明文 = "";

		WitchDataS[WitchType::ミナエ].属性 = Element::炎;
		WitchDataS[WitchType::ミナエ].攻撃補正 = 1.2;
		WitchDataS[WitchType::ミナエ].連射補正 = 0.8;
		WitchDataS[WitchType::ミナエ].射程補正 = 1.2;

		WitchDataS[WitchType::ミナエ].職種[0] = UnitType::ミナエ;
		WitchDataS[WitchType::ミナエ].職種[1] = UnitType::兵士;
		WitchDataS[WitchType::ミナエ].職種[2] = UnitType::騎士;
		WitchDataS[WitchType::ミナエ].職種[3] = UnitType::斧士;
		WitchDataS[WitchType::ミナエ].職種[4] = UnitType::師範;
		WitchDataS[WitchType::ミナエ].職種[5] = UnitType::司祭;
		WitchDataS[WitchType::ミナエ].職種[6] = UnitType::プリンセス;
		WitchDataS[WitchType::ミナエ].職種[7] = UnitType::術士;
		WitchDataS[WitchType::ミナエ].職種[8] = UnitType::賢者;
		WitchDataS[WitchType::ミナエ].職種[9] = UnitType::踊り子;
		WitchDataS[WitchType::ミナエ].職種[10] = UnitType::料理人;
		WitchDataS[WitchType::ミナエ].職種[11] = UnitType::くノ一;

		//
		WitchDataS[WitchType::トレニア].名前 = "トレニア";
		WitchDataS[WitchType::トレニア].大魔法名 = "超口径激滅レーザー";
		WitchDataS[WitchType::トレニア].魔導具名 = "フォトンルーメン";
		WitchDataS[WitchType::トレニア].説明文 = "";

		WitchDataS[WitchType::トレニア].属性 = Element::炎;
		WitchDataS[WitchType::トレニア].範囲補正 = 1.2;
		WitchDataS[WitchType::トレニア].強化速度 = 0.5;

		WitchDataS[WitchType::トレニア].職種[0] = UnitType::トレニア;
		WitchDataS[WitchType::トレニア].職種[1] = UnitType::傭兵;
		WitchDataS[WitchType::トレニア].職種[2] = UnitType::技師;
		WitchDataS[WitchType::トレニア].職種[3] = UnitType::剣豪;
		WitchDataS[WitchType::トレニア].職種[4] = UnitType::闘士;
		WitchDataS[WitchType::トレニア].職種[5] = UnitType::武闘家;
		WitchDataS[WitchType::トレニア].職種[6] = UnitType::僧侶;
		WitchDataS[WitchType::トレニア].職種[7] = UnitType::司祭;
		WitchDataS[WitchType::トレニア].職種[8] = UnitType::術士;
		WitchDataS[WitchType::トレニア].職種[9] = UnitType::踊り子;
		WitchDataS[WitchType::トレニア].職種[10] = UnitType::料理人;
		WitchDataS[WitchType::トレニア].職種[11] = UnitType::くノ一;

		//
		WitchDataS[WitchType::ロチエ].名前 = "ロチエ";
		WitchDataS[WitchType::ロチエ].大魔法名 = "花曇流忍法『大山鳴動』";
		WitchDataS[WitchType::ロチエ].魔導具名 = "紅蜂";
		WitchDataS[WitchType::ロチエ].説明文 = "";

		WitchDataS[WitchType::ロチエ].属性 = Element::炎;
		WitchDataS[WitchType::ロチエ].特殊補正[DebuffType::鈍足] = 1.5;
		WitchDataS[WitchType::ロチエ].特殊補正[DebuffType::麻痺] = 1.5;

		WitchDataS[WitchType::ロチエ].職種[0] = UnitType::ロチエ;
		WitchDataS[WitchType::ロチエ].職種[1] = UnitType::足軽;
		WitchDataS[WitchType::ロチエ].職種[2] = UnitType::技師;
		WitchDataS[WitchType::ロチエ].職種[3] = UnitType::勇者;
		WitchDataS[WitchType::ロチエ].職種[4] = UnitType::剣豪;
		WitchDataS[WitchType::ロチエ].職種[5] = UnitType::師範;
		WitchDataS[WitchType::ロチエ].職種[6] = UnitType::射手;
		WitchDataS[WitchType::ロチエ].職種[7] = UnitType::僧侶;
		WitchDataS[WitchType::ロチエ].職種[8] = UnitType::プリンス;
		WitchDataS[WitchType::ロチエ].職種[9] = UnitType::給仕;
		WitchDataS[WitchType::ロチエ].職種[10] = UnitType::忍者;
		WitchDataS[WitchType::ロチエ].職種[11] = UnitType::くノ一;

		//
		WitchDataS[WitchType::バロゥ].名前 = "バロゥ";
		WitchDataS[WitchType::バロゥ].大魔法名 = "バラーダ・イェブ";
		WitchDataS[WitchType::バロゥ].魔導具名 = "クレメンス";
		WitchDataS[WitchType::バロゥ].説明文 = "";

		WitchDataS[WitchType::バロゥ].属性 = Element::炎;
		WitchDataS[WitchType::バロゥ].攻撃補正 = 0.7;
		WitchDataS[WitchType::バロゥ].連射補正 = 1.5;

		WitchDataS[WitchType::バロゥ].職種[0] = UnitType::バロゥ;
		WitchDataS[WitchType::バロゥ].職種[1] = UnitType::足軽;
		WitchDataS[WitchType::バロゥ].職種[2] = UnitType::技師;
		WitchDataS[WitchType::バロゥ].職種[3] = UnitType::剣士;
		WitchDataS[WitchType::バロゥ].職種[4] = UnitType::騎士;
		WitchDataS[WitchType::バロゥ].職種[5] = UnitType::師範;
		WitchDataS[WitchType::バロゥ].職種[6] = UnitType::狩人;
		WitchDataS[WitchType::バロゥ].職種[7] = UnitType::射手;
		WitchDataS[WitchType::バロゥ].職種[8] = UnitType::賢者;
		WitchDataS[WitchType::バロゥ].職種[9] = UnitType::将軍;
		WitchDataS[WitchType::バロゥ].職種[10] = UnitType::執事;
		WitchDataS[WitchType::バロゥ].職種[11] = UnitType::盗賊;

		//
		WitchDataS[WitchType::フィオナ].名前 = "フィオナ";
		WitchDataS[WitchType::フィオナ].大魔法名 = "セイオーヌ・ディエーヴ";
		WitchDataS[WitchType::フィオナ].魔導具名 = "スヴァーズ";
		WitchDataS[WitchType::フィオナ].説明文 = "";

		WitchDataS[WitchType::フィオナ].属性 = Element::炎;
		WitchDataS[WitchType::フィオナ].射程補正 = 1.1;
		WitchDataS[WitchType::フィオナ].特殊補正[DebuffType::吹飛] = 1.5;
		WitchDataS[WitchType::フィオナ].特殊補正[DebuffType::鈍足] = 0.5;
		WitchDataS[WitchType::フィオナ].逆境補正 = 0;//通常の三倍

		WitchDataS[WitchType::フィオナ].職種[0] = UnitType::フィオナ;
		WitchDataS[WitchType::フィオナ].職種[1] = UnitType::兵士;
		WitchDataS[WitchType::フィオナ].職種[2] = UnitType::騎士;
		WitchDataS[WitchType::フィオナ].職種[3] = UnitType::斧士;
		WitchDataS[WitchType::フィオナ].職種[4] = UnitType::武闘家;
		WitchDataS[WitchType::フィオナ].職種[5] = UnitType::狩人;
		WitchDataS[WitchType::フィオナ].職種[6] = UnitType::司祭;
		WitchDataS[WitchType::フィオナ].職種[7] = UnitType::プリンセス;
		WitchDataS[WitchType::フィオナ].職種[8] = UnitType::術士;
		WitchDataS[WitchType::フィオナ].職種[9] = UnitType::将軍;
		WitchDataS[WitchType::フィオナ].職種[10] = UnitType::執事;
		WitchDataS[WitchType::フィオナ].職種[11] = UnitType::料理人;

		//
		WitchDataS[WitchType::ナズナ].名前 = "ナズナ";
		WitchDataS[WitchType::ナズナ].大魔法名 = "さんくちゅあり";
		WitchDataS[WitchType::ナズナ].魔導具名 = "プリティワンド";
		WitchDataS[WitchType::ナズナ].説明文 = "";

		WitchDataS[WitchType::ナズナ].属性 = Element::炎;
		WitchDataS[WitchType::ナズナ].攻撃補正 = 0.8;
		WitchDataS[WitchType::ナズナ].MP消費 = 0.8;

		WitchDataS[WitchType::ナズナ].職種[0] = UnitType::ナズナ;
		WitchDataS[WitchType::ナズナ].職種[1] = UnitType::兵士;
		WitchDataS[WitchType::ナズナ].職種[2] = UnitType::勇者;
		WitchDataS[WitchType::ナズナ].職種[3] = UnitType::斧士;
		WitchDataS[WitchType::ナズナ].職種[4] = UnitType::闘士;
		WitchDataS[WitchType::ナズナ].職種[5] = UnitType::狩人;
		WitchDataS[WitchType::ナズナ].職種[6] = UnitType::司祭;
		WitchDataS[WitchType::ナズナ].職種[7] = UnitType::プリンセス;
		WitchDataS[WitchType::ナズナ].職種[8] = UnitType::賢者;
		WitchDataS[WitchType::ナズナ].職種[9] = UnitType::踊り子;
		WitchDataS[WitchType::ナズナ].職種[10] = UnitType::給仕;
		WitchDataS[WitchType::ナズナ].職種[11] = UnitType::くノ一;

		//
		WitchDataS[WitchType::委員長].名前 = "委員長";
		WitchDataS[WitchType::委員長].大魔法名 = "ローゼンクランツ";
		WitchDataS[WitchType::委員長].魔導具名 = "チューベローズ";
		WitchDataS[WitchType::委員長].説明文 = "";

		WitchDataS[WitchType::委員長].属性 = Element::炎;
		WitchDataS[WitchType::委員長].弱点補正 = 2.0;
		WitchDataS[WitchType::委員長].回収率 = 0.75;
		WitchDataS[WitchType::委員長].回収速度 = 0.5;
		WitchDataS[WitchType::委員長].強化速度 = 0.5;

		WitchDataS[WitchType::委員長].職種[0] = UnitType::委員長;
		WitchDataS[WitchType::委員長].職種[1] = UnitType::傭兵;
		WitchDataS[WitchType::委員長].職種[2] = UnitType::勇者;
		WitchDataS[WitchType::委員長].職種[3] = UnitType::槍士;
		WitchDataS[WitchType::委員長].職種[4] = UnitType::騎士;
		WitchDataS[WitchType::委員長].職種[5] = UnitType::闘士;
		WitchDataS[WitchType::委員長].職種[6] = UnitType::射手;
		WitchDataS[WitchType::委員長].職種[7] = UnitType::僧侶;
		WitchDataS[WitchType::委員長].職種[8] = UnitType::プリンセス;
		WitchDataS[WitchType::委員長].職種[9] = UnitType::軍師;
		WitchDataS[WitchType::委員長].職種[10] = UnitType::執事;
		WitchDataS[WitchType::委員長].職種[11] = UnitType::盗賊;

		//
		WitchDataS[WitchType::ミルラ].名前 = "ミルラ";
		WitchDataS[WitchType::ミルラ].大魔法名 = "リーダーオンロート";
		WitchDataS[WitchType::ミルラ].魔導具名 = "フィソステギア";
		WitchDataS[WitchType::ミルラ].説明文 = "";

		WitchDataS[WitchType::ミルラ].属性 = Element::炎;
		WitchDataS[WitchType::ミルラ].支援補正 = 1.2;

		WitchDataS[WitchType::ミルラ].職種[0] = UnitType::ミルラ;
		WitchDataS[WitchType::ミルラ].職種[1] = UnitType::傭兵;
		WitchDataS[WitchType::ミルラ].職種[2] = UnitType::剣豪;
		WitchDataS[WitchType::ミルラ].職種[3] = UnitType::師範;
		WitchDataS[WitchType::ミルラ].職種[4] = UnitType::射手;
		WitchDataS[WitchType::ミルラ].職種[5] = UnitType::僧侶;
		WitchDataS[WitchType::ミルラ].職種[6] = UnitType::プリンス;
		WitchDataS[WitchType::ミルラ].職種[7] = UnitType::賢者;
		WitchDataS[WitchType::ミルラ].職種[8] = UnitType::軍師;
		WitchDataS[WitchType::ミルラ].職種[9] = UnitType::将軍;
		WitchDataS[WitchType::ミルラ].職種[10] = UnitType::給仕;
		WitchDataS[WitchType::ミルラ].職種[11] = UnitType::盗賊;
	}

}