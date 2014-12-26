//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "DataS.h"
#include "Witch.h"

namespace SDX_TD
{
	using namespace SDX;
	/**通常弾.*/
	class IShot : public IObject
	{
	public:
		UnitData *st;
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
		IShot(IShape &図形, ISprite &描画方法, double 角度, UnitData *st, int レベル , double 支援補正) :
			IObject(図形, 描画方法),
			st(st),
			isSmall(true)
		{
			//支援補正
			攻撃力 = st->攻撃力[レベル] * 支援補正;

			//属性効果			
			デバフ効果 = st->デバフ効果[レベル];
			デバフ率 = st->デバフ率[レベル];
		}

		/**消滅判定.*/
		virtual bool RemoveCheck()
		{
			const double x = GetX();
			const double y = GetY();

			//反射系処理

			if (x < -10 || x > MAP_SIZE * CHIP_SIZE + 10 || y < -10 || y > MAP_SIZE * CHIP_SIZE + 10)
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

		Shot(TSprite &&描画方法, TMotion &&移動方法 , TShape &&図形, UnitData *基礎性能, int Lv, double 角度 , double 支援補正) :
			IShot(shape, sprite, 角度, 基礎性能 , Lv , 支援補正),
			shape(図形),
			sprite(描画方法),
			motion(移動方法)
		{
			SetAngle(角度);
		}

		void Act() override
		{
			motion.Update( this );
		}
	};
}