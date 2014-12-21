﻿//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"
#include "Material.h"

namespace SDX_TD
{
	using namespace SDX;

	/**魔法の基礎性能.*/
	struct UnitData
	{
		static const int 最大強化 = 6;

		std::string 名前;
		std::string 説明文;

		UnitType 魔法種;
		RangeType 射程種;
		Element 属性;

		int コスト[最大強化];
		int 攻撃力[最大強化];
		int 連射[最大強化];
		int 射程[最大強化];
		double 弾速[最大強化];

		double 支援効果[最大強化];

		int 炸裂範囲[最大強化];
		double 炸裂威力[最大強化];

		DebuffType デバフ種;
		EnemyType 特攻種族;
		int    デバフ効果[最大強化];
		double デバフ率[最大強化];

		int  Hit数[最大強化];

		double 半径 = 10;//当たり判定の大きさ

		bool is対空 = true;//空の敵に当たるかどうか
		bool is対地 = true;//地上の敵に当たるかどうか
		bool is使い捨て = false;

		bool isウィッチ = false;//指揮官魔法、詠唱回数の管理が違う
		int  基礎詠唱回数;

		//static EnumArray<UnitData, UnitType> data;
	};

	namespace
	{
		EnumArray<UnitData, UnitType> UnitDataS;
	}

	void LoadUnitS()
	{
		File UnitFile("File/Data/unit_data.dat", FileMode::Read, true);
		int count = 0;

		for (auto &it : UnitDataS)
		{
			it.魔法種 = UnitType(count);
			if (it.魔法種 <= UnitType::ミルラ){ it.isウィッチ = true; }

			++count;

			UnitFile.Read(it.名前);
			UnitFile.Read(it.説明文);

			UnitFile.Read(it.属性);
			UnitFile.Read(it.射程種);

			int param;
			UnitFile.Read(param);
			if (param == 1){it.is対空 = false;}
			if (param == 2){it.is対地 = false;}
			if (param == 3){it.is使い捨て = true;}

			UnitFile.Read(it.基礎詠唱回数);
			UnitFile.Read(it.デバフ種);
			UnitFile.Read(it.特攻種族);

			UnitFile.Read(it.コスト, 6);
			UnitFile.Read(it.攻撃力, 6);
			UnitFile.Read(it.射程, 6);
			UnitFile.Read(it.連射, 6);
			UnitFile.Read<int>(it.弾速, 6, 100);

			UnitFile.Read<int>(it.支援効果, 6, 100);
			UnitFile.Read<int>(it.支援効果, 6, 100);
			UnitFile.Read<int>(it.炸裂威力, 6, 100);
			UnitFile.Read(it.炸裂範囲, 6);

			UnitFile.Read(it.デバフ効果, 6);
			UnitFile.Read<int>(it.デバフ率, 6, 100);
			UnitFile.Read(it.Hit数, 6);
		}

		UnitDataS[UnitType::給仕].is使い捨て = true;


	}

}