//Copyright © 2014 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "Object.h"
#include "Struct/DataS.h"
#include "Witch.h"

namespace SDX_TD
{
	using namespace SDX;
	/**通常弾.*/
	class IShot : public IObject
	{
	public:
		UnitData *st;
		int Lv;
		double 支援補正;
		double 攻撃力;
		int    デバフ効果;
		double デバフ率;

		double 炸裂半径 = 0;

		bool   is貫通 = false;//命中時、消滅するかどうか
		bool   isHitCheck = true;//当たり判定を行うかどうか
		bool   isArea = false;//範囲攻撃フラグ
		int	   反射回数 = 0;

		virtual ~IShot() = default;

		/**弾の生成.*/
		IShot(IShape &図形, ISprite &描画方法, double 角度, UnitData *st, int レベル , double 支援補正 ) :
			IObject(図形, 描画方法),
			st(st),
			Lv(レベル),
			支援補正(支援補正)
		{
			//支援補正
			攻撃力 = st->攻撃力[レベル] * 支援補正;

			//属性効果			
			デバフ効果 = st->デバフ効果[レベル];
			デバフ率 = st->デバフ率[レベル];

			炸裂半径 = st->炸裂範囲[レベル];
		}

	};

	class Bomm : public IShot
	{
	public:
		Circle circle;
		SpNull spNull;

		Bomm(const Circle &範囲 , UnitData* st , int Lv , double 支援補正):
			IShot( circle , spNull , 0 , st , Lv , 支援補正),
			circle(範囲)
		{
			isArea = true;
			is貫通 = true;
		}

		void Draw() const override
		{
			circle.Draw({ 255, 0, 0, 255 - timer * 5 });
		}

		void Act() override
		{
			//発生フレームのみ判定がある
			if (timer != 1)
			{
				isHitCheck = false;
			}
			if (timer >= 50)
			{
				isRemove = true;
			}
		}


	};

	class Beam : public IShot
	{
	public:
		Line line;
		SpNull spNull;
		int ヒット数;
		int 透明度 = 255;

		Beam(const Line &範囲, UnitData* st, int Lv, double 支援補正 , int ヒット数) :
			IShot(line, spNull, 0, st, Lv, 支援補正),
			line(範囲),
			ヒット数(ヒット数 - 1)
		{
			isArea = true;
			is貫通 = true;
		}

		void Draw() const override
		{
			line.Draw({ 255, 0, 0, 透明度 });
		}

		void Act() override
		{
			//発生フレームのみ判定がある
			//1秒に6回判定がある
			if (timer % 10 == 0 && ヒット数 > 0)
			{
				--ヒット数;
				isHitCheck = true;
			}
			else
			{
				isHitCheck = false;
			}

			if (ヒット数 <= 0)
			{
				透明度 -= 10;
			}

			if (透明度 <= 0)
			{
				isRemove = true;
			}
		}

	};

	/**弾のテンプレート.*/
	template <class TShape, class TSprite, class TMotion>
	class Shot : public IShot
	{
	public:
		TShape shape;
		TSprite sprite;
		TMotion motion;

		/** α版は弾画像一種類.*/
		Shot(TSprite &&描画方法, TMotion &&移動方法 , TShape &&図形, UnitData *基礎性能, int Lv, double 角度 , double 支援補正) :
			IShot(shape, sprite, 角度, 基礎性能 , Lv , 支援補正),
			shape(図形),
			sprite(描画方法),
			motion(移動方法)
		{
			SetAngle(角度);
			sprite.SetZoom(10.0 / 32, 10.0 / 32);
		}

		void Act() override
		{
			motion.Update( this );
		}

		/**消滅判定.*/
		virtual bool RemoveCheck()
		{
			const double x = GetX();
			const double y = GetY();

			if (x < -10 || x > MAP_SIZE * CHIP_SIZE + 10 || y < -10 || y > MAP_SIZE * CHIP_SIZE + 10)
			{
				isRemove = true;
			}
			return isRemove;
		}

		/**衝突した時の処理.*/
		void Damaged(IObject* 衝突相手) override
		{
			//Hpの減少等はEnemy側で処理
			if (!is貫通)
			{
				isRemove = true;
			}

			if (炸裂半径 > 0 && !isArea)
			{
				SStage->Add(new Bomm({ GetX(), GetY(), 炸裂半径 }, st, Lv, 支援補正));
			}
		}
	};
}