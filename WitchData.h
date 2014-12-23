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
		std::string 魔導具名;
		std::string 説明文;

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

		double 詠唱回数補正 = 1.0;

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
	EnumArray<WitchData, WitchType> GrowWitchDataS;//成長率

	void LoadWitchS()
	{
		//α版は暫定的にライナのみ実装
		WitchDataS[WitchType::ライナ].名前 = "ライナ";
		WitchDataS[WitchType::ライナ].属性 = Element::炎;
		WitchDataS[WitchType::ライナ].攻撃補正 = 1.05;
		WitchDataS[WitchType::ライナ].連射補正 = 1.05;
		WitchDataS[WitchType::ライナ].逆境補正 = 0.02;

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
	}

}