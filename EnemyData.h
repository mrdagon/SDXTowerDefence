//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "EnumType.h"

namespace SDX_TD
{
	using namespace SDX;

	/**敵の基礎性能.*/
	struct EnemyData
	{
		//stータス
		std::string 種族名;
		std::string 説明文;
		EnemyType 種族;
		MoveType 移動種;
		Element 属性;

		int スコア = 50;
		int 最大HP = 100;
		double 移動速度 = 1;
		double 防御力 = 0;
		double 再生力 = 0;
		bool is離陸 = false;//HPが減ると空をとぶフラグ
		bool is加速 = false;//直線移動が早い

		//無効 or 有効
		EnumArray<bool, DebuffType> 特殊耐性;

		void Set(MoveType 移動タイプ, Element 属性, int 最大HP, int スコア, int 移動速度)
		{
			this->移動種 = 移動タイプ;
			this->属性 = 属性;
			this->スコア = スコア;
			this->最大HP = 最大HP;
			this->移動速度 = double(移動速度) / 100;
			特殊耐性[DebuffType::鈍足] = false;
			特殊耐性[DebuffType::麻痺] = false;
			特殊耐性[DebuffType::吹飛] = false;
			特殊耐性[DebuffType::防壊] = false;
		}

		void SetInfo(const char* 種族名, const char* 説明文)
		{
			種族名 = 種族名;
			説明文 = 説明文;
		}
	};

	EnumArray<EnemyData, EnemyType> EnemyDataS;

	void LoadEnemyS()
	{
		for (int a = 0; a < (int)EnemyType::COUNT; ++a)
		{
			EnemyDataS[(EnemyType)a].種族 = (EnemyType)a;
		}

		//HP スコア 移動速度,防御,回避
		EnemyDataS[EnemyType::ゼリー].Set(MoveType::陸, Element::氷, 50, 15, 40);
		EnemyDataS[EnemyType::ゴブリン].Set(MoveType::陸, Element::樹, 80, 10, 50);
		EnemyDataS[EnemyType::オーガ].Set(MoveType::陸, Element::炎, 130, 20, 15);
		EnemyDataS[EnemyType::コボルド].Set(MoveType::陸, Element::樹, 40, 15, 70);
		EnemyDataS[EnemyType::ケットシー].Set(MoveType::陸, Element::空, 30, 15, 120);
		EnemyDataS[EnemyType::シャーマン].Set(MoveType::陸, Element::炎, 50, 20, 50);
		EnemyDataS[EnemyType::スケルトン].Set(MoveType::陸, Element::氷, 40, 15, 70);
		EnemyDataS[EnemyType::インプ].Set(MoveType::空, Element::空, 40, 15, 35);
		EnemyDataS[EnemyType::グリフィン].Set(MoveType::陸, Element::空, 90, 20, 25);
		EnemyDataS[EnemyType::ケルベロス].Set(MoveType::陸, Element::炎, 60, 20, 60);
		EnemyDataS[EnemyType::ゴーレム].Set(MoveType::陸, Element::樹, 60, 20, 20);
		EnemyDataS[EnemyType::ドラゴン].Set(MoveType::陸, Element::炎, 80, 25, 40);
		EnemyDataS[EnemyType::ゼリー王].Set(MoveType::陸, Element::氷, 30, 20, 40);
		EnemyDataS[EnemyType::マーマン].Set(MoveType::水, Element::氷, 60, 15, 50);
		EnemyDataS[EnemyType::トレント].Set(MoveType::空, Element::氷, 60, 20, 15);

		EnemyDataS[EnemyType::マーマン].防御力 = 0.5;
		EnemyDataS[EnemyType::ゴーレム].防御力 = 1;
		EnemyDataS[EnemyType::トレント].防御力 = 1;
		EnemyDataS[EnemyType::ドラゴン].防御力 = 0.5;

		EnemyDataS[EnemyType::スケルトン].再生力 = 1;
		EnemyDataS[EnemyType::トレント].再生力 = 0.5;

		EnemyDataS[EnemyType::オーガ].特殊耐性[DebuffType::吹飛] = true;
		EnemyDataS[EnemyType::ケルベロス].特殊耐性[DebuffType::鈍足] = true;
		EnemyDataS[EnemyType::トレント].特殊耐性[DebuffType::吹飛] = true;

		EnemyDataS[EnemyType::コボルド].is加速 = true;
		EnemyDataS[EnemyType::グリフィン].is離陸 = true;
	}
}