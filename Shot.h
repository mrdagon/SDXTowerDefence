//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "DataType.h"
#include "Witch.h"

namespace SDX_TD
{
	using namespace SDX;
	/**通常弾.*/
	class IShot : public IObject
	{
	public:
		UnitData &st;
		double 攻撃力;
		int    デバフ効果;
		double デバフ率;

		double 炸裂威力 = 0;
		double 炸裂範囲 = 0;

		bool   is貫通 = false;
		bool   isSmall = true;//分割当たり判定用
		bool   is必中 = false;

		virtual ~IShot() = default;

		/**弾の生成.*/
		IShot(IShape &図形, ISprite &描画方法, double 角度, UnitData &st , int レベル) :
			IObject(図形, 描画方法, Belong::弾),
			st(st),
			isSmall(true)
		{
			図形.SetAngle(角度);
			描画方法.SetAngle(角度);
			CulcPower(1.0 , レベル);
		}

		/** 攻撃力の計算.*/
		/** ダメージ等は発射時に決定する*/
		void CulcPower(double 支援補正 , int レベル)
		{
			//ウィッチによる補正
			攻撃力 = st.攻撃力[レベル] * 支援補正 * WITCH::Main->攻撃補正;

			//属性効果
			if (st.デバフ種 != DebuffType::無)
			{
				デバフ効果 = int(st.デバフ効果[レベル] * WITCH::Main->特殊補正[st.デバフ種]);
			}
		}

		/**消滅判定.*/
		virtual bool RemoveCheck()
		{
			const double x = GetX();
			const double y = GetY();

			//反射系処理

			if (x < -10 || x > Land::MapSize * Land::ChipSize + 10 || y < -10 || y > Land::MapSize * Land::ChipSize + 10)
			{
				isRemove = true;
			}
			return isRemove;
		}

		/**衝突した時の処理.*/
		void Damaged(IObject* 衝突相手)
		{
			if (!is貫通)
			{
				isRemove = true;
			}
			if (炸裂範囲 > 0)
			{
				//サイズが大きくなった後、次で消滅

			}
		}

		/**毎フレームの処理.*/
		virtual void Act() = 0;
	};

	/**弾のテンプレート.*/
	template <class TShape, class TSprite, class TMotion>
	class Shot : public IShot
	{
	public:
		TShape shape;
		TSprite sprite;
		TMotion motion;

		Shot( UnitData &基礎性能 , int Lv , double 角度,  TShape &&図形, TSprite &&描画方法, TMotion &&移動方法 ) :
			IShot(shape, sprite, 角度, 基礎性能 , Lv),
			shape(図形),
			sprite(描画方法),
			motion(移動方法)
		{}

		void Act() override
		{
			motion.Update(&shape);
		}
	};
}