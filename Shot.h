#pragma once//☀Unicode
#include "Object.h"
#include "DataType.h"
#include "IShot.h"

namespace SDX_TD
{
    using namespace SDX;

    /**通常弾.*/
    template <class TShape = Circle , class TSprite = SpImage>
    class Shot : public Object<TShape,TSprite> , public IShot
    {
    public:
        ShotState 性能;

        UnitData &基礎ステ;
        int    強化回数;
        double 攻撃力;

        bool   is貫通 = false;
        bool   isSmall = false;//分割当たり判定用
        bool   is必中 = false;

        int    デバフ効果;
        double デバフ率;

        double 炸裂威力 = 0;
        double 炸裂範囲 = 0;
        
        /**Shotの作成.*/
        Shot(const TShape& 当たり判定 , const TSprite 描画ポリシー, UnitData &基礎ステ, int 強化回数, double 支援補正) :
            Object(当たり判定, 描画ポリシー , Belong::弾),
            基礎ステ(基礎ステ)
        {
            CulcPower(支援補正);
        }

        /**攻撃力の計算.*/
        void CulcPower(double 支援補正)
        {
            //ウィッチによる補正
            攻撃力 = 基礎ステ.攻撃力[強化回数] * 支援補正 * MainWitch->実ステ.攻撃補正;

            //属性効果
            if (基礎ステ.デバフ種 != DebuffType::無)
            {
                デバフ効果 = int(基礎ステ.デバフ効果[強化回数] * MainWitch->実ステ.特殊補正[基礎ステ.デバフ種]);
            }

        }

        /**消滅判定.*/
        bool RemoveCheck() override
        {
            const double x = GetX();
            const double y = GetY();

            if (x < -10 || x > Land::MapSize * Land::ChipSize + 10 || y < -10 || y > Land::MapSize * Land::ChipSize + 10) isRemove = true;

            return isRemove;
        }

        /**描画処理.*/
        void Draw() const override
        {
            shape->Draw(Color::Yellow, 255);
        }

        /**衝突した時の処理.*/
        void Damaged() override 
        {
            if (!is貫通)
            {
                this->isRemove = true;
            }
            React();
        }

        /**衝突した時の特殊処理.*/
        void React() override
        {
        };

        /**毎フレームの処理.*/
        void Act() override
        {
        }
    };

    /**ビーム弾.*/
    //class Beam : public Shot
    //{
    //    Beam(double X座標, double Y座標, double 角度, double 太さ, UnitData &基礎ステ, int レベル, double 支援補正) :
    //        Shot(new Line(X座標,Y座標,角度,100,0,太さ),基礎ステ,レベル,支援補正)
    //    {
    //        SetAngle(角度);
    //    }
    //};

    /**範囲攻撃.*/
    //class Impact : public Shot
    //{
    //    Impact(double X座標, double Y座標, double 半径 , UnitData &基礎ステ, int レベル, double 補正) :
    //        Shot(new Circle(X座標, Y座標, 半径), 基礎ステ, レベル, 補正)
    //    {
    //        
    //    }
    //};
}