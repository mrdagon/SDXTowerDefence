#pragma once//☀Unicode
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
        UnitData &基礎ステ;
        int    強化回数 = 0;
        double 攻撃力;

        bool   is貫通 = false;
        bool   isSmall = true;//分割当たり判定用
        bool   is必中 = false;

        int    デバフ効果;
        double デバフ率;

        double 炸裂威力 = 0;
        double 炸裂範囲 = 0;

        /**円形弾.*/
        IShot(IShape &図形, ISprite &描画方法, double 角度, UnitData &基礎ステ) :
            IObject(図形, 描画方法,Belong::弾),
            基礎ステ(基礎ステ),
            isSmall(true)
        {
            SetAngle(角度);
            CulcPower(1.0);
        }

        virtual ~IShot() = default;

        /**攻撃力の計算.*/
        void CulcPower(double 支援補正)
        {
            //ウィッチによる補正
            攻撃力 = 基礎ステ.攻撃力[強化回数] * 支援補正 * WITCH::Main->実ステ.攻撃補正;

            //属性効果
            if (基礎ステ.デバフ種 != DebuffType::無)
            {
                デバフ効果 = int(基礎ステ.デバフ効果[強化回数] * WITCH::Main->実ステ.特殊補正[基礎ステ.デバフ種]);
            }

        }

        /**消滅判定.*/
        virtual bool RemoveCheck()
        {
            const double x = GetX();
            const double y = GetY();

            if (x < -10 || x > Land::MapSize * Land::ChipSize + 10 || y < -10 || y > Land::MapSize * Land::ChipSize + 10) isRemove = true;

            return isRemove;
        }

        /**衝突した時の処理.*/
        void Damaged(IObject* 衝突相手)
        {
            if (!is貫通)
            {
                this->isRemove = true;
            }
            React();
        }

        /**衝突した時の特殊処理.*/
        virtual void React() = 0;

        /**毎フレームの処理.*/
        virtual void Act() = 0;

    };

    /**弾のテンプレート.*/
    template <class TShape,class TSprite , class TMotion , class TReact>
    class Shot : public IShot
    {
    public:
        TShape shape;
        TSprite sprite;
        TMotion motion;
        TReact react;

        Shot(TShape &&図形, TSprite &&描画方法 , double 角度, UnitData &基礎ステ , TMotion &&移動方法 , TReact &&命中時処理):
            IShot(shape,sprite,角度,基礎ステ),
            shape(図形),
            sprite(描画方法),
            motion(移動方法),
            react(命中時処理)
        {}

        void Act() override
        {
            motion.Update(this);
        }

        void React() override
        {
            react.Update(this);
        }
    };
}