#pragma once//☀Unicode
#include "Unit.h"

namespace SDX_TD
{
    using namespace SDX;

    class 兵士 : public Unit
    {
    public:
        class MyShot:public Shot
        {
        public:
            //using Shot::Shot;したいがVC++2013には継承コンストラクタがない
            MyShot(double X座標, double Y座標, double 角度, UnitData &基礎ステ, int 強化回数, double 支援補正) :
                Shot(X座標,Y座標,角度,基礎ステ,強化回数,支援補正)
            {}
        
            MyShot(Shape* 当たり判定, UnitData &基礎ステ, int 強化回数, double 支援補正) :
                Shot(当たり判定, 基礎ステ, 強化回数, 支援補正)
            {}

            void React() override
            {            
            }

            void Act() override
            {
            }            
        };
    
        void Shoot(double 角度)
        {
            //シンプルな直進弾の場合ShotでOK
            MakeShot<MyShot>(角度);
        }
    };


}